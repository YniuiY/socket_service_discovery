#ifndef UDP_CLIENT_H_
#define UDP_CLIENT_H_

/**
 * socket()
 * |
 * sendto() <---|
 * |            |
 * recvform() ->|
 * |
 * close()
 */

#include "common/headers.h"
#include "common/packet.h"

namespace udp {

class UdpClient {
 public:
  UdpClient();
  UdpClient(std::string const& server_ip, int const& port);
  ~UdpClient();

  void Socket(bool is_boradcast);
  void Start();

  int Send(Packet* data);
  int Recv(Packet* data);

 private:
  void send_pack();
  void recv_pack();

  sockaddr_in server_addr_;
  int socket_fd_;
  bool is_multicast_;
  uint8_t recv_buffer[MAX_UDP_DATA_SIZE];
  uint8_t send_buffer[MAX_UDP_DATA_SIZE];
};
} // namespace udp

#endif