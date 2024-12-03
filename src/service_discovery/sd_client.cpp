#include "service_discovery/sd_client.h"
#include "common/packet.h"
#include "service_discovery/sd_package/sd_package.h"
#include "unix_socket/stream/client.h"
#include <cstdint>
#include <cstring>
#include <memory>

namespace sd {

SDClient::SDClient(std::string master_link_info, uint32_t needed_service_id)
    : master_link_info_(master_link_info),
      needed_service_id_(needed_service_id) {
  uds_client_ = std::make_shared<unix_domain::stream::Client>(master_link_info_);
  if (uds_client_ == nullptr) {
    std::cerr << "Failed to create unix domain client" << std::endl;
    throw std::runtime_error("Failed to create unix domain client");
  }
}

void SDClient::Init() {
  uds_client_->Socket();
  uds_client_->Connect();
}

void SDClient::Run() {
  // TODO: 发送FindService请求，接收服务链接信息
  Packet* pack = reinterpret_cast<Packet*>(send_buffer_);
  pack->header.type = PacketType::SERVICE_DISCOVERY;
  pack->header.data_size = sizeof(SDPackage);

  SDPackage* sd_pack = reinterpret_cast<SDPackage*>(pack->data);
  sd_pack->type = SDPackageType::SD_PACKAGE_TYPE_LOC_FIND_SERVICE;
  sd_pack->find_service->service_id = needed_service_id_;
  uds_client_->Send(pack);

  Packet* recv_pack = reinterpret_cast<Packet*>(recv_buffer_);
  uds_client_->Recv(recv_pack);

  SDPackage* recv_sd_pack = reinterpret_cast<SDPackage*>(recv_pack->data);
  if (recv_sd_pack->type == SDPackageType::SD_PACKAGE_TYPE_LOC_OFFER_SERVICE) {
    if (recv_sd_pack->offer_service->is_local) {
      local_service_link_info_ = reinterpret_cast<char*>(recv_sd_pack->offer_service->loc_service_addr);
      std::cout << "Service id: " << needed_service_id_
                << " founded, local service link info: "
                << local_service_link_info_ << std::endl;
    } else {
      in_addr addr;
      addr.s_addr = recv_sd_pack->offer_service->service_ip;
      remote_service_ip_ = inet_ntoa(addr);
      remote_service_port_ = recv_sd_pack->offer_service->service_port;
      std::cout << "Service id: " << needed_service_id_
                << " founded, remote service ip:port "
                << remote_service_ip_ << ":" << remote_service_port_
                << std::endl;
    }
  }
}

} // namespace sd