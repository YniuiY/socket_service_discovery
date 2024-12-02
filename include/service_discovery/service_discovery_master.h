#ifndef SERVICE_DISCOVERY_MASTER_H
#define SERVICE_DISCOVERY_MASTER_H

#include <cstdint>
#include <memory>
#include <sys/socket.h> // socket相关，如socket、bind、listen、accept
#include <sys/epoll.h>  // epoll 相关，如epoll_create、epoll_ctl、epoll_wait
#include <sys/un.h>     // unix socket相关
#include <netinet/in.h> // ip地址相关，如sockaddr_in、ip_mreq
#include <arpa/inet.h>  // inet相关，如inet_pton、inet_ntop
#include <cstring>
#include <string>
#include <iostream>
#include <map>
#include <unistd.h>

#include "common/packet.h"
#include "udp/udp_client.h" // udp客户端
#include "unix_socket/stream/server.h" // unix socket服务端
#include "sd_package/sd_package.h" // 服务发现协议包

namespace sd {

class ServiceDiscoveryMaster {
 public:
  static constexpr int MAX_BUFFER_SIZE{65535}; // UDS缓冲区大小
  ServiceDiscoveryMaster(std::string domain_server_sd_addr, std::string multicast_sd_ip, uint16_t multicast_sd_port);
  ~ServiceDiscoveryMaster();

  void Init();
  void Start();
  void Stop();
  void Destroy();

 private:
  /// @brief: 从UDS接收本地FindService报文，在service_map_中查找对应的服务信息，如果有则返回服务信息
  /// @brief: 没有则调用find_service()向ServiceSD发送获取服务列表请求
  void process_local_find_service(SDMessage* sd_msg);

  /// @brief: 收到本地FindService报文并且本地服务列表中没有对应服务时，通过UDP组播向ServiceSD发送获取服务列表请求
  /// @brief: 获取到服务列表后，将服务列表保存到service_map_中
  void remote_find_service(uint32_t service_id, uint32_t instance_id);

  /// @brief: 返回服务信息，本地服务返回UDS的{/tmp/xxx.sock}，远程服务返回{ip:prot}
  void notify_local_service_info(std::string service_link_info);
  void notify_remote_service_info(uint32_t service_ip, uint16_t service_port);

 private:
  uint8_t send_buffer_[MAX_BUFFER_SIZE]; // 发送缓冲区
  uint8_t recv_buffer_[MAX_BUFFER_SIZE]; // 接收缓冲区

  /// @brief: UDP组播客户端
  std::shared_ptr<udp::UdpClient> udp_client_;
  /// @brief: unix socket服务端
  std::shared_ptr<unix_domain::stream::Server> unix_domain_server_;

  /// @brief: 远程服务列表 <service_id, <service_ip, service_port>>
  std::map<uint32_t, std::pair<std::string, std::uint16_t>> remote_service_map_;
  /// @brief: 本地服务列表 <service_id, service_link_info>
  std::map<uint32_t, std::string> local_service_map_;
};

} // namespace sd


#endif // SERVICE_DISCOVERY_MASTER_H