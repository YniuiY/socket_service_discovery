# UDP多播收发

## 1. 整体流程

### 1.1 发送者

	1. 创建套接字 socket( )
	2. 填充组播信息结构体 sockaddr_in
	3. 发送数据 sendto( )

### 1.2 接收者

	1.创建套接字 scoket( )
	2.填充组播信息结构体 sockaddr_in
	3.将套接字与组播信息结构体绑定 bind( )
	------------------------------------
	4.设置为加入多播组 setsockopt( )
	------------------------------------
	5.接收数据 recvfrom( )

----

## 2. 发送多播数据包

​	仅发送多播数据包不需要加入多播组，将目的地址设置为对应的多播地址即可，在Linux中，如果不设置发送对应多播地址使用的网卡，则会使用系统会使用路由表自动选择默认网卡进行发送（如果存在默认路由）。但通常多播数据包可能不是需要发送到默认路由，因此我们需要指定发送多播数据包使用的网卡，有以下三种方式：

1. 使用setsockopt通过IP_MULTICAST_IF选项设置发送数据包到特定多播地址时使用的对应网络接口地址。

```C++
struct ip_mreq mreq;
// 设置多播地址
mreq.imr_multiaddr.s_addr = inet_addr("226.1.11.111");
// 设置使用该多播地址发送数据时使用的网卡ip
mreq.imr_interface.s_addr = inet_addr("192.168.1.2");
// 调用setsockopt
ret = setsockopt(socks[i], IPPROTO_IP, IP_MULTICAST_IF, &mreq,sizeof(mreq));
if ( ret < 0) {
    LOG_ERROR("Fail to join udp group, err: %s", strerror(errno));
    goto out;
}
```

2. **使用setsockopt设置SO_BINDTODEVICE将该socket绑定到对应的网卡，此后通过该socket接收和发送的数据均只能通过绑定的网卡（需要root权限）。**

```C++
char* interface = "eth0";
ret = setsockopt(socks[i], SOL_SOCKET,SO_BINDTODEVICE, interface, strlen(interface));
if ( ret < 0 ) {
    LOG_ERROR("Fail to bind to interface, err: %s", strerror(errno));
    goto out;
}
```

3. 在路由表中指定对应多播地址使用的网卡地址（即将多播地址当作一个普通网段的地址，为该网段增加一个路由表项）。

```shell
route add -net 226.1.11.0 netmask 255.255.255.0 dev eth0
```

## 3. 接收多播数据包
接收多播数据包需要加入多播组（IPV4和IPV6都兼容的方式）

```C++
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

// 设置禁止自己发送的多播数据包被自己接收
// 0:禁止，1:允许
u_char flag = 0;
if (setsockopt(server_socket_, IPPROTO_IP, IP_MULTICAST_LOOP, &flag, sizeof(flag)) < 0) {
    std::cerr << "Set multicast loop failed, " << strerror(errno) << std::endl;
    throw std::runtime_error("Set multicast loop failed");
}
```

接收多播数据包需要使用IP_ADD_MEMBERSHIP加入一个多播组（IPV4版本）。

```C++
// 加入组播
struct ip_mreq mreq;
// 设置需要接收的多播地址
mreq.imr_multiaddr.s_addr = inet_addr("226.1.11.111");
// 设置接收该多播地址数据的网卡ip
mreq.imr_interface.s_addr = inet_addr("192.168.1.2");
// 调用setsockopt
ret = setsockopt(socks[i], IPPROTO_IP, IP_ADD_MEMBERSHIP , &mreq,sizeof (mreq));
if ( ret < 0) {
    LOG_ERROR("Fail to join udp group, err: %s", strerror(errno));
    goto out;
}
```

如果需要一个socket仅接收特定网卡的多播数据包，在Linux中目前我找到的最好的办法就是设置SO_BINDTODEVICE选项将该socket绑定到指定网卡，如上一小节所述。

![image-20241203181921473](/home/yangdi/.config/Typora/typora-user-images/image-20241203181921473.png)

![image-20241203180935219](/home/yangdi/.config/Typora/typora-user-images/image-20241203180935219.png)

## 头文件

```C++
#include <sys/socket.h>  // socket 相关
#include <sys/un.h> // unix domain socket
#include <arpa/inet.h> // inet_pton
#include <netinet/in.h> // sockaddr_in ip地址相关
#include <sys/epoll.h> // epoll
```



## UDP与MTU

### IP分片的概念

- 在TCP/IP分层中，数据链路层用MTU（Maximum Transmission Unit，最大传输单元）来限制所能传输的数据包大小，MTU是指一次传送的数据最大长度，不包括数据链路层数据帧的帧头，如以太网的MTU为1500字节，实际上数据帧的最大长度为1514字节，其中以太网数据帧的帧头为14字节
- 当发送的IP数据包的大小超过了MTU时，IP层就需要对数据进行分片，否则数据将无法发送成功
- IP层是没有超时重传机制的，如果IP层对一个数据包进行了分片，只要有一个分片丢失了，只能依赖于传输层进行重传，结果是所有的分片都要重传一遍，这个代价有点大；公网传输，需要经过多个网络设备，IP分片容易造成丢包
- 由此可见，IP分片会大大降低传输层传送数据的成功率，所以我们要避免IP分片

### UDP与MTU的关系

MTU是指通信协议的链路层上面所能通过的最大数据包大小
单个UDP传输的最大内容1472字节，但由于不同的网络中转设备设置的MTU值并不相同：

- Internet环境下：标准MTU值为576字节，UDP的数据长度应该控制在548字节（576-8-20）以内
- 局域网环境下：UDP的数据长度控制在1472个字节以内

![img](https://i-blog.csdnimg.cn/blog_migrate/38675c42d67d14a433c3102d4aff5474.png)
