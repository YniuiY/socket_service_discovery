#ifndef SD_SERVER_H
#define SD_SERVER_H

#include "common/headers.h"
#include "unix_socket/stream/client.h"
#include <memory>

namespace sd {

class SDServer {
 public:
  static const int MAX_BUFFER_SIZE = 65535;
  static const std::string local_service_path;;
  SDServer(std::string master_link_info, uint32_t service_id);
  ~SDServer();
  void Run();

 private:
  std::string master_link_info_;
  uint32_t service_id_;
  std::shared_ptr<unix_domain::stream::Client> uds_client_;
  uint8_t send_buffer_[MAX_BUFFER_SIZE]; // 发送缓冲区
  uint8_t recv_buffer_[MAX_BUFFER_SIZE]; // 接收缓冲区
};

} // namespace sd

#endif // SD_SERVER_H