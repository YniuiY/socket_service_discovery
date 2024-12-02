#ifndef CLIENT_H
#define CLIENT_H

#include <cstdint>
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
#include "unix_socket/stream/client.h" // unix socket服务端

namespace sd {

class Client {
 public:
  Client();
  ~Client();

  /// @brief: 初始化，创建UDS客户端
  void Init(std::string domain_sd_addr);
  /// @brief: 连接到本地SD的UDS服务端, 向UDS发送FindService报文，获取服务信息
  void Start();
  void Stop();
  void Destroy();

 private:
  /// @brief: 向本地SD的UDS服务端发送FindService报文，获取服务信息
  void find_service();

 private:
  uint8_t send_buffer_[MAX_UDP_DATA_SIZE]; // 发送缓冲区
  uint8_t recv_buffer_[MAX_UDP_DATA_SIZE]; // 接收缓冲区

  /// @brief: unix socket服务端
  unix_domain::stream::Client unix_domain_client_;
  std::string local_service_addr_; // 本地服务地址 /tmp/local_service_addr.sock
  std::pair<std::string, std::uint32_t> remont_service_addr_;  // 远程服务地址 ip:port
};

} // namespace sd
#endif // CLIENT_SD_H