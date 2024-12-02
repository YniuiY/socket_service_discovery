#ifndef HEADERS_H_
#define HEADERS_H_

#include <cstdint>
#include <sys/socket.h> // socket相关，如socket、bind、listen、accept
#include <sys/epoll.h>  // epoll 相关，如epoll_create、epoll_ctl、epoll_wait
#include <sys/un.h>     // unix socket相关
#include <netinet/in.h> // ip相关，如sockaddr_in、ip_mreq
#include <arpa/inet.h>  // inet相关，如inet_pton、inet_ntop
#include <iostream>
#include <string>
#include <thread>
#include <unistd.h>
#include <cstring>
#include <functional>

#include "common/packet.h"
#include "common/transfer.h"

using ReadCallback = std::function<void(SDMessage*)>;

#endif //HEADERS_H_