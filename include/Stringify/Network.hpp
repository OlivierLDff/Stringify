#ifndef __STRINGIFY_NETWORK_HPP__
#define __STRINGIFY_NETWORK_HPP__

#include <string>
#include <cstdint>

namespace stringify {
namespace net {

namespace ipv4 {

std::string toString(const std::uint32_t address);
constexpr std::uint32_t make(std::uint8_t a, std::uint8_t b, std::uint8_t c, std::uint8_t d)
{
    return std::uint32_t(a) << 24 | std::uint32_t(b) << 16 | std::uint32_t(c) << 8 |
           std::uint32_t(d);
}
bool get(const std::string& subject, std::uint32_t& address);
bool isValid(const std::string& subject);
std::uint8_t toMask(const std::uint32_t ip);

}

namespace ipv6 {

std::string toString(const std::uint8_t* address);
bool isValid(const std::string& subject);
bool get(const std::string& subject, std::uint8_t* address);
std::uint8_t toMask(const std::uint8_t* ip);

}

namespace mac {

bool get(const std::string& subject, std::uint8_t* mac);
bool isValid(const std::string& subject);
std::string toString(const std::uint8_t* mac);

}

}
}

#endif
