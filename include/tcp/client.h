#ifndef TCP_CLIENT_H_
#define TCP_CLIENT_H_

#include "common/headers.h"
#include "common/packet.h"

namespace tcp {

class Client {
 public:
  Client();
  Client(std::string const& ip, int const& port);
  ~Client();

  void Socket();
  void Connect();
  void Send(Packet*);
  void Recv(Packet*);
  void SendMsg();
  void RecvMsg();

 private:
  int socket_;
  sockaddr_in server_addr_; // 服务器地址
  Packet* packet_;
};

}
#endif // TCP_CLIENT_H_