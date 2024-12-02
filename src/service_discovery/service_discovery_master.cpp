#include "service_discovery/service_discovery_master.h"
#include "common/packet.h"
#include "service_discovery/sd_package/sd_package.h"
#include "udp/udp_client.h"
#include "unix_socket/stream/server.h"
#include <cstdint>
#include <cstring>
#include <memory>

namespace sd {

ServiceDiscoveryMaster::ServiceDiscoveryMaster(
    std::string domain_server_sd_addr,
    std::string multicast_sd_ip,
    uint16_t multicast_sd_port) : udp_client_(nullptr), unix_domain_server_(nullptr) {
  udp_client_ = std::make_shared<udp::UdpClient>(multicast_sd_ip, multicast_sd_port);
  if (udp_client_ ==  nullptr) {
    std::cerr << "Error creating udp client" << std::endl;
    throw std::runtime_error("Error creating udp client");
  }

  unix_domain_server_ = std::make_shared<unix_domain::stream::Server>(domain_server_sd_addr);
  if (unix_domain_server_ == nullptr) {
    std::cerr << "Error creating unix domain server" << std::endl;
    throw std::runtime_error("Error creating unix domain server");
  }
}

ServiceDiscoveryMaster::~ServiceDiscoveryMaster() {}

void ServiceDiscoveryMaster::Init() {
  std::cout << "ServiceDiscoveryMaster::Init()\n";
  udp_client_->Socket(false);
  unix_domain_server_->Socket();
  unix_domain_server_->Bind();
  unix_domain_server_->Listen();
  unix_domain_server_->BlockRead(
      std::bind(&ServiceDiscoveryMaster::process_local_find_service, this,
                std::placeholders::_1));
  std::cout << "ServiceDiscoveryMaster::Init() Over\n";
}

void ServiceDiscoveryMaster::Start() {
  unix_domain_server_->Start();
}

void ServiceDiscoveryMaster::Stop() {
  unix_domain_server_->Stop();
}

void ServiceDiscoveryMaster::Destroy() {

}

void ServiceDiscoveryMaster::process_local_find_service(SDMessage* msg) {
  // 收到本地客户端的查询服务请求
  if (msg->header.type == PacketType::SERVICE_DISCOVERY) {
    std::cout << "ServiceDiscoveryMaster::process_local_find_service()\n";
    SDPackage* sd_pack = reinterpret_cast<SDPackage*>(msg->payload);
    if (sd_pack->type == SDPackageType::SD_PACKAGE_TYPE_LOC_FIND_SERVICE) {
      std::cout << "recv local find service msg\n";
      uint32_t service_id = sd_pack->find_service->service_id;
      uint32_t instance_id = sd_pack->find_service->instance_id;
      std::cout << "service id: " << service_id << ", instance id: " << instance_id << std::endl;

      if (local_service_map_.find(service_id) != local_service_map_.end()) {
        std::cout << "find service in local service map\n";
        std::string service_addr = local_service_map_.at(service_id);
        notify_local_service_info(service_addr);
      } else {
        remote_find_service(service_id, instance_id);
      }
    }
  }
}

void ServiceDiscoveryMaster::notify_local_service_info(std::string service_addr) {
  std::cout << "ServiceDiscoveryMaster::notify_local_service_info()\n";
  Packet* pack = reinterpret_cast<Packet*>(send_buffer_);
  pack->header.type = PacketType::SERVICE_DISCOVERY;
  SDPackage* sd_pack = reinterpret_cast<SDPackage*>(pack->data);
  sd_pack->type = SDPackageType::SD_PACKAGE_TYPE_LOC_OFFER_SERVICE;
  strcpy(reinterpret_cast<char *>(sd_pack->offer_service->loc_service_addr_), service_addr.c_str());
  unix_domain_server_->Send(pack);
}

void ServiceDiscoveryMaster::remote_find_service(uint32_t service_id, uint32_t instance_id) {
  std::cout << "ServiceDiscoveryMaster::remont_find_service()\n";
  // 向远程服务发现节点发送查询服务请求
  Packet* pack = reinterpret_cast<Packet*>(send_buffer_);
  pack->header.type = PacketType::SERVICE_DISCOVERY;
  SDPackage* sd_pack = reinterpret_cast<SDPackage*>(pack->data);
  sd_pack->type = SDPackageType::SD_PACKAGE_TYPE_FIND_SERVICE;
  sd_pack->find_service->service_id = service_id;
  sd_pack->find_service->instance_id = instance_id;
  udp_client_->Send(pack);
}



} // namespace sd