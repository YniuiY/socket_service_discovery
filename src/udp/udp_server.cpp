/**
 * 通常情况下tcp服务器是并发的，UDP服务器是迭代的
 * 所以一般来说UDP服务器不需要使用epoll这类I/O多路复用的方法。
 * 具体来看就是，UDP接收，发送数据始终用的同一个socket描述符，
 * 不存在TCP在accept后返回新链接socket描述符，使用新描述符通信的机制。
 */

#include "udp/udp_server.h"
#include "common/headers.h"
#include "common/packet.h"
#include <net/if.h>
#include <netinet/in.h>
#include <sys/types.h>

namespace udp {

UpdServer::UpdServer():server_socket_{-1} {
  memset(&server_addr_, 0, sizeof(server_addr_));
  server_addr_.sin_family = AF_INET;
  server_addr_.sin_port = htons(51016);
  server_addr_.sin_addr.s_addr = htonl(INADDR_ANY);
}

UpdServer::UpdServer(int const& port):server_socket_{-1} {
  memset(&server_addr_, 0, sizeof(server_addr_));
  server_addr_.sin_family = AF_INET;
  server_addr_.sin_port = htons(port);
  server_addr_.sin_addr.s_addr = htonl(INADDR_ANY);
}

UpdServer::UpdServer(std::string const& multi_cast_ip, int const& port):server_socket_{-1} {
  memset(&server_addr_, 0, sizeof(server_addr_));
  server_addr_.sin_family = AF_INET;
  server_addr_.sin_port = htons(port);
  server_addr_.sin_addr.s_addr = htonl(INADDR_ANY);

  multi_cast_ip_ = multi_cast_ip;
}

UpdServer::~UpdServer() {
  close(server_socket_);
}

void UpdServer::Socket(bool is_multi_cast) {
  server_socket_ = socket(AF_INET, SOCK_DGRAM, 0);
  if (server_socket_ == -1) {
    std::cerr << "Create udp socket failed\n";
    exit(1);
  } else {
    std::cout << "Create udp server socket success\n";
  }
  if (is_multi_cast && !multi_cast_ip_.empty()) {
    // IPV4加入多播组的方式
    // ip_mreq mreq;
    // mreq.imr_interface.s_addr = htonl(INADDR_ANY);
    // inet_pton(AF_INET, multi_cast_ip_.c_str(), &mreq.imr_multiaddr.s_addr);
    // if (setsockopt(server_socket_, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) < 0) {
    //   std::cerr << "Add to multicast group failed, " << strerror(errno) << std::endl;
    //   exit(1);
    // }

    // 兼容IPV6和IPV4的加入多播组方式
    group_req req;
    // 设置本地接收多播数据的网卡IP
    // 设置成0表示让内核自动选择网卡
    // req.gr_interface = 0;
    // 通过网卡名称获取网卡索引
    req.gr_interface = if_nametoindex("enp2s0");
    sockaddr_in* addr = reinterpret_cast<sockaddr_in*>(&req.gr_group);
    addr->sin_family = AF_INET;
    // 设置多播组IP
    inet_pton(AF_INET, multi_cast_ip_.c_str(), &addr->sin_addr.s_addr);
    if (setsockopt(server_socket_, IPPROTO_IP, MCAST_JOIN_GROUP, &req, sizeof(req)) < 0) {
      std::cerr << "Add to multicast group failed, " << strerror(errno) << std::endl;
      throw std::runtime_error("Add to multicast group failed");
    }

    // 设置禁止自己发送的多播数据包被接收
    // 0:禁止，1:允许
    u_char flag = 0;
    if (setsockopt(server_socket_, IPPROTO_IP, IP_MULTICAST_LOOP, &flag, sizeof(flag)) < 0) {
      std::cerr << "Set multicast loop failed, " << strerror(errno) << std::endl;
      throw std::runtime_error("Set multicast loop failed");
    }

    std::cout << "Access multicast group, ip: " << multi_cast_ip_ << std::endl;
  }
}

void UpdServer::Bind() {
  int ret = bind(server_socket_, (sockaddr*)&server_addr_, sizeof(server_addr_));
  std::cout << "Upd server bind, ret: " << ret << std::endl;
}

void UpdServer::Start() {
  std::cout << "Udp server start\n";
  std::thread(&UpdServer::run, this).join();
}

void UpdServer::BlockRead(ReadCallback callback) {
  read_callback_ = callback;
}

void UpdServer::run() {

  // // One by One的处理数据报
  // while (true) {
  //   recv_data();
  //   send_data();
  // }
}

void UpdServer::recv_data() {
  memset(recv_buffer, 0, sizeof(recv_buffer));
  Packet* pack = reinterpret_cast<Packet*>(recv_buffer);

  socklen_t addr_len = sizeof(client_addr_);
  // 接收Packet的header部分
  ssize_t recv_data_size = recvfrom(server_socket_, pack, MAX_UDP_DATA_SIZE, 0, (sockaddr*)&client_addr_, &addr_len);
  if (recv_data_size < 0) {
    std::cerr << "Recv data failed, " << strerror(errno) << std::endl;
    throw std::runtime_error("Recv data failed");
  } else {
    if (recv_data_size != (ssize_t)(sizeof(Packet) + pack->header.data_size)) {
      std::cerr << "Recv data failed, real recv data size: " << recv_data_size
                << ", need recv size: "
                << sizeof(Packet) + pack->header.data_size << std::endl;
      throw std::runtime_error("Recv data failed, size not match");
    } else if (read_callback_) {
      read_callback_(pack);
    }
  }
}

void UpdServer::Send(Packet* pack) {
  memset(send_buffer, 0, MAX_UDP_DATA_SIZE);
  int total_packs_size{0};
  int pack_header_size = sizeof(Packet::header);
  total_packs_size = pack_header_size + pack->header.data_size;

  int send_data_size = sendto(server_socket_, pack, total_packs_size, 0,
                              (sockaddr*)&client_addr_, sizeof(client_addr_));
  if (send_data_size != total_packs_size) {
    std::cerr << "Send response to client error, real send data size: "
              << send_data_size << ", need send size: " << total_packs_size
              << std::endl;
    return;
  } else {
    std::cout << "Send response to client: " << std::endl; 
  }
}

}