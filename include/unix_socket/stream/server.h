#ifndef UNIX_DOMAIN_SERVER_H_
#define UNIX_DOMAIN_SERVER_H_

#include "common/headers.h"
#include "common/packet.h"
#include <functional>

namespace unix_domain {
namespace stream {

class Server {
 public:
  static constexpr int MAX_BUFFER_SIZE{65535};

  Server();
  explicit Server(std::string const& link_info);
  ~Server();

  void Socket();
  void Bind();
  void Listen();
  int Accept();
  void Start();
  void Stop();
  void Send(Packet* pack);
  void BlockRead(ReadCallback callback);

 private:
  void run();
  int in_epoll_recvmsg(int sockfd);
  void in_epoll_sendmsg(int sockfd);

  ReadCallback read_callback_;
  int sockfd_;
  int epollfd_;
  sockaddr_un server_addr_;
  std::string link_info_;
  uint8_t recv_buffer[MAX_BUFFER_SIZE];
  uint8_t send_buffer[MAX_BUFFER_SIZE];
  Packet* pack_;
};

} // namespace stream
} // namespace unix_domain

#endif //UNIX_DOMAIN_SERVER_H_