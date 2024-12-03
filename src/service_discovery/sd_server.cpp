#include "common/packet.h"
#include "service_discovery/sd_package/sd_package.h"
#include "service_discovery/sd_service.h"
#include "unix_socket/stream/client.h"
#include <cstdint>
#include <cstring>
#include <memory>

namespace sd {

const std::string SDServer::local_service_path{"/tmp/service_1.sock"};

SDServer::SDServer(std::string master_link_info, uint32_t service_id)
    : master_link_info_(master_link_info),
      service_id_(service_id) {
  uds_client_ = std::make_shared<unix_domain::stream::Client>(master_link_info_);
}

void SDServer::Init() {
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
  sd_pack->offer_service->service_ip = inet_addr("10.1.2.147");
  sd_pack->offer_service->service_port = 51015;
  strncpy(reinterpret_cast<char *>(sd_pack->offer_service->loc_service_addr),
          local_service_path.c_str(), local_service_path.size());
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