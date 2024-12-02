#include "common/packet.h"
#include "service_discovery/sd_package/sd_package.h"
#include "service_discovery/sd_service.h"
#include "unix_socket/stream/client.h"
#include <cstdint>
#include <memory>

namespace sd {

SDServer::SDServer(std::string master_link_info, uint32_t service_id)
    : master_link_info_(master_link_info), service_id_(service_id) {
  uds_client_ =
      std::make_shared<unix_domain::stream::Client>(master_link_info_);
  uds_client_->Socket();
  uds_client_->Connect();
}

void SDServer::Run() {
  Packet* packet = reinterpret_cast<Packet*>(send_buffer_);
  packet->header.type = PacketType::SERVICE_DISCOVERY;
  SDPackage* sd_pack = reinterpret_cast<SDPackage*>(packet->data);
  sd_pack->type = SDPackageType::SD_PACKAGE_TYPE_LOC_OFFER_SERVICE;
  sd_pack->find_service->service_id = service_id_;
  sd_pack->find_service->instance_id = 0;
  packet->header.data_size = sizeof(SDPackage);
  uds_client_->Send(packet);
  packet = reinterpret_cast<Packet*>(recv_buffer_);
  uds_client_->Recv(packet);
  if (packet->header.type == PacketType::SERVICE_DISCOVERY) {
    std::cout << "Register service success\n";
  } else {
    std::cout << "Register service failed\n";
  }
}

} // namespace sd