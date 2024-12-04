#include "service_discovery/service_discovery_master.h"
#include "common/packet.h"
#include "service_discovery/sd_package/sd_package.h"
#include "udp/udp_client.h"
#include "udp/udp_server.h"
#include "unix_socket/stream/server.h"
#include <arpa/inet.h>
#include <cstdint>
#include <cstring>
#include <memory>
#include <netinet/in.h>

namespace sd {

ServiceDiscoveryMaster::ServiceDiscoveryMaster(
    std::string domain_server_sd_addr,
    std::string multicast_sd_ip,
    uint16_t multicast_sd_port)
    : udp_multicast_client_(nullptr),
      udp_multicast_server_(nullptr),
      unix_domain_server_(nullptr) {
  udp_multicast_client_ = std::make_shared<udp::UdpClient>(multicast_sd_ip, multicast_sd_port);
  if (udp_multicast_client_ ==  nullptr) {
    std::cerr << "Error creating udp client" << std::endl;
    throw std::runtime_error("Error creating udp client");
  }

  unix_domain_server_ = std::make_shared<unix_domain::stream::Server>(domain_server_sd_addr);
  if (unix_domain_server_ == nullptr) {
    std::cerr << "Error creating unix domain server" << std::endl;
    throw std::runtime_error("Error creating unix domain server");
  }

  udp_multicast_server_ = std::make_shared<udp::UpdServer>(multicast_sd_ip, multicast_sd_port);
  if (udp_multicast_server_ == nullptr) {
    std::cerr << "Error creating udp server" << std::endl;
    throw std::runtime_error("Error creating udp server");
  }
}

ServiceDiscoveryMaster::~ServiceDiscoveryMaster() {}

void ServiceDiscoveryMaster::Init() {
  std::cout << "ServiceDiscoveryMaster::Init()\n";
  udp_multicast_client_->Socket(false);
  unix_domain_server_->Socket();
  unix_domain_server_->Bind();
  unix_domain_server_->Listen();
  unix_domain_server_->BlockRead(
      std::bind(&ServiceDiscoveryMaster::process_local_find_service, this,
                std::placeholders::_1));
  udp_multicast_server_->Socket(true);
  udp_multicast_server_->Bind();
  udp_multicast_server_->BlockRead(
      std::bind(&ServiceDiscoveryMaster::process_remote_find_service, this,
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

void ServiceDiscoveryMaster::process_local_find_service(Packet* msg) {
  // 收到本地客户端的查询服务请求
  if (msg->header.type == PacketType::SERVICE_DISCOVERY) {
    std::cout << "ServiceDiscoveryMaster::process_local_find_service()\n";
    SDPackage* sd_pack = reinterpret_cast<SDPackage*>(msg->data);
    uint32_t service_id = sd_pack->find_service->service_id;
    uint32_t instance_id = sd_pack->find_service->instance_id;
    if (sd_pack->type == SDPackageType::SD_PACKAGE_TYPE_LOC_FIND_SERVICE) {
      std::cout << "recv local find service msg\n";
      std::cout << "service id: " << service_id << ", instance id: " << instance_id << std::endl;

      if (local_service_map_.find(service_id) != local_service_map_.end()) {
        std::cout << "find service in local service map\n";
        std::string service_addr = std::get<0>(local_service_map_.at(service_id));
        notify_local_service_info(service_addr);
      } else {
        remote_find_service(service_id, instance_id);
      }
    } else if (sd_pack->type == SDPackageType::SD_PACKAGE_TYPE_LOC_OFFER_SERVICE) {
      std::string service_addr{reinterpret_cast<char*>(sd_pack->offer_service->loc_service_addr)};
      uint32_t service_ip = sd_pack->offer_service->service_ip;
      uint16_t service_port = sd_pack->offer_service->service_port;
      local_service_map_[service_id] = std::make_tuple(service_addr, service_ip, service_port);
      std::cout << "recv local offer service msg, service id: " << service_id
                << ", service addr: " << service_addr << std::endl;
    }
  }
}

void ServiceDiscoveryMaster::notify_local_service_info(std::string service_addr) {
  std::cout << "ServiceDiscoveryMaster::notify_local_service_info()\n";
  Packet* pack = reinterpret_cast<Packet*>(send_buffer_);
  pack->header.type = PacketType::SERVICE_DISCOVERY;
  SDPackage* sd_pack = reinterpret_cast<SDPackage*>(pack->data);
  sd_pack->type = SDPackageType::SD_PACKAGE_TYPE_LOC_OFFER_SERVICE;
  sd_pack->offer_service->is_local = true;
  strcpy(reinterpret_cast<char *>(sd_pack->offer_service->loc_service_addr), service_addr.c_str());
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
  udp_multicast_client_->Send(pack);

  pack = reinterpret_cast<Packet*>(recv_buffer_);
  udp_multicast_client_->Recv(pack);
  if (pack->header.type == PacketType::SERVICE_DISCOVERY) {
    sd_pack = reinterpret_cast<SDPackage*>(pack->data);
    if (sd_pack->type == SDPackageType::SD_PACKAGE_TYPE_OFFER_SERVICE) {
      std::uint32_t service_ip = sd_pack->offer_service->service_ip;
      std::uint16_t service_port = sd_pack->offer_service->service_port;
      // sockaddr_in
      in_addr addr;
      addr.s_addr = service_ip;
      std::string ip{inet_ntoa(addr)}; // 将ip地址转换为字符串
      std::cout << "remote service info: " << ip << ":" << service_port << std::endl;
      notify_remote_service_info(service_ip, service_port);
    }
  }
}

void ServiceDiscoveryMaster::notify_remote_service_info(uint32_t service_ip, uint16_t service_port) {
  std::cout << "ServiceDiscoveryMaster::notify_local_service_info()\n";
  Packet* pack = reinterpret_cast<Packet*>(send_buffer_);
  pack->header.type = PacketType::SERVICE_DISCOVERY;
  SDPackage* sd_pack = reinterpret_cast<SDPackage*>(pack->data);
  sd_pack->type = SDPackageType::SD_PACKAGE_TYPE_LOC_OFFER_SERVICE;
  sd_pack->offer_service->is_local = false;
  sd_pack->offer_service->service_ip = service_ip;
  sd_pack->offer_service->service_port = service_port;
  unix_domain_server_->Send(pack);
}

void ServiceDiscoveryMaster::process_remote_find_service(Packet* pack) {
  pack->header.type = PacketType::SERVICE_DISCOVERY;
  SDPackage* sd_pack = reinterpret_cast<SDPackage*>(pack->data);
  if (sd_pack->type == SDPackageType::SD_PACKAGE_TYPE_FIND_SERVICE) {
    std::cout << "ServiceDiscoveryMaster::process_remote_find_service()\n";
    // 查询本地服务
    // TODO: 查询本地服务并返回结果
    uint32_t service_id = sd_pack->find_service->service_id;
    uint32_t service_ip;
    uint16_t service_port;
    if (local_service_map_.find(service_id) != local_service_map_.end()) {
      service_ip = std::get<1>(local_service_map_.at(service_id));
      service_port = std::get<2>(local_service_map_.at(service_id));
      // 返回结果
      Packet* offer_pack = reinterpret_cast<Packet*>(send_buffer_);
      offer_pack->header.type = PacketType::SERVICE_DISCOVERY;
      offer_pack->header.data_size = sizeof(SDPackage);

      SDPackage* offer_sd_pack = reinterpret_cast<SDPackage*>(pack->data);
      offer_sd_pack->type = SDPackageType::SD_PACKAGE_TYPE_OFFER_SERVICE;
      offer_sd_pack->offer_service->service_ip = service_ip;
      offer_sd_pack->offer_service->service_port = service_port;

      udp_multicast_server_->Send(pack);
    }
  }
}

} // namespace sd