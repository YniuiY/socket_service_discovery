#ifndef UDP_SERVER_H_
#define UDP_SERVER_H_
/**
 * socket()
 * |
 * bind()
 * |
 * recvfrom() <-|
 * |            |
 * sendto()     |
 * |----------->|
 * close()
 */

#include "common/headers.h"
#include "common/packet.h"

namespace udp {

class UpdServer {
 public:
  UpdServer();
  explicit UpdServer(int const& port);
  UpdServer(std::string const& ip, int const& port);
  ~UpdServer();

  void Socket(bool is_multi_cast);
  void Bind();
  void Start();
  void BlockRead(ReadCallback callback);
  void Send(Packet* pack);
 
 private:
  void run();
  void recv_data();
  

  int server_socket_;
  std::string multi_cast_ip_;
  sockaddr_in server_addr_;
  sockaddr_in client_addr_;
  sockaddr_in multi_cast_addr_;
  ReadCallback read_callback_;
  uint8_t recv_buffer[MAX_UDP_DATA_SIZE];
  uint8_t send_buffer[MAX_UDP_DATA_SIZE];
};

} // namespace udp

#endif // UDP_SERVER_H_