#ifndef SD_CLIENT_H
#define SD_CLIENT_H

#include "common/headers.h"
#include "unix_socket/stream/client.h"
#include <memory>

namespace sd {

class SDClient {
 public:
  static const int MAX_BUFFER_SIZE = 65535;
  SDClient(std::string master_link_info, uint32_t need_service_id);
  ~SDClient() = default;
  void Init();
  void Run();

 private:
  std::string master_link_info_;
  std::shared_ptr<unix_domain::stream::Client> uds_client_;
  uint8_t send_buffer_[MAX_BUFFER_SIZE]; // 发送缓冲区
  uint8_t recv_buffer_[MAX_BUFFER_SIZE]; // 接收缓冲区
  uint32_t needed_service_id_;           // 需要的服务的id
  std::string local_service_link_info_;  // 本地服务的链接信息
  std::string remote_service_ip_;        // 远程服务的ip
  uint16_t remote_service_port_;         // 远程服务的端口
};

} // namespace sd

#endif // SD_SERVER_H