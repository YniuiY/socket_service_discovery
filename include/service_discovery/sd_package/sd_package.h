#ifndef SD_PACKAGE_H
#define SD_PACKAGE_H

#include <cstdint>

enum class SDPackageType : uint8_t {
  SD_PACKAGE_TYPE_INVALID = 0,
  SD_PACKAGE_TYPE_FIND_SERVICE = 1,
  SD_PACKAGE_TYPE_OFFER_SERVICE = 2,
  SD_PACKAGE_TYPE_LOC_FIND_SERVICE = 3,
  SD_PACKAGE_TYPE_LOC_OFFER_SERVICE = 4
};

struct alignas(8) FindServicePackage {
  uint32_t service_id;
  uint32_t instance_id;
};

struct alignas(8) OfferServicePackage {
  bool is_local;
  uint32_t service_ip; // IPv4 address
  uint16_t service_port;
  uint8_t addr_size;
  uint8_t  loc_service_addr[64];
};

struct alignas(8) SDPackage {
  SDPackageType type;
  FindServicePackage find_service[0];
  OfferServicePackage offer_service[0];
};

#endif // SD_PACKAGE_H