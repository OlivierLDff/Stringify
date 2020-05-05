#include <gtest/gtest.h>

#include <Stringify/Stringify.hpp>

using namespace stringify::net;

TEST(ipv4, get)
{
    std::uint32_t ip;

    const std::string ip1 = "192.168.12.1";
    constexpr auto ip1Res = ipv4::make(192, 168, 12, 1);
    ASSERT_TRUE(ipv4::get(ip1, ip));
    ASSERT_EQ(ip, ip1Res);

    const std::string ip2 = "0.0.0.0";
    constexpr auto ip2Res = 0;
    ASSERT_TRUE(ipv4::get(ip2, ip));
    ASSERT_EQ(ip, ip2Res);

    const std::string ip3 = "255.255.255.255";
    constexpr auto ip3Res = ipv4::make(255, 255, 255, 255);
    ASSERT_TRUE(ipv4::get(ip3, ip));
    ASSERT_EQ(ip, ip3Res);

    ASSERT_FALSE(ipv4::get("", ip));
    ASSERT_FALSE(ipv4::get("1239172BYDH12", ip));
    ASSERT_FALSE(ipv4::get("123.123.12", ip));
    ASSERT_FALSE(ipv4::get("NBYUA AZULDHAZOIMDK ZAD", ip));
    ASSERT_FALSE(ipv4::get("123 12K3J 1231 2 ", ip));
    ASSERT_FALSE(ipv4::get("NBYUA AZULDHAZOIMDK ZAD", ip));
    ASSERT_FALSE(ipv4::get("256.121.2.21", ip));
    ASSERT_FALSE(ipv4::get("0.0.0.89976543", ip));
    ASSERT_FALSE(ipv4::get("0.0.123123.0", ip));
    ASSERT_FALSE(ipv4::get("0.123124.1RFAZ.0", ip));
    ASSERT_FALSE(ipv4::get("qouhsc!..&e12D&", ip));
    ASSERT_FALSE(ipv4::get("192407817OFOI1ED081Y9ODP102N DH12ED:;m^%M%/", ip));
    ASSERT_FALSE(ipv4::get("^(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.", ip));
    ASSERT_FALSE(ipv4::get(".123.123.3.4", ip));
    ASSERT_FALSE(ipv4::get("a.c.c.d", ip));
}

TEST(ipv4, toString)
{
    ASSERT_EQ(ipv4::toString(ipv4::make(192, 168, 12, 1)), "192.168.12.1");
    ASSERT_EQ(ipv4::toString(ipv4::make(0, 0, 0, 0)), "0.0.0.0");
    ASSERT_EQ(ipv4::toString(ipv4::make(255, 255, 255, 255)), "255.255.255.255");
}

TEST(ipv4, toMask)
{
    ASSERT_EQ(ipv4::toMask(ipv4::make(255, 0, 0, 0)), 8);
    ASSERT_EQ(ipv4::toMask(ipv4::make(0, 0, 0, 0)), 0);
    ASSERT_EQ(ipv4::toMask(ipv4::make(255, 255, 255, 255)), 32);
    ASSERT_EQ(ipv4::toMask(ipv4::make(192, 255, 255, 255)), 2);
}

TEST(ipv6, fullIpV6)
{
    quint8 ipv6[16] = {
        0x12,
        0x34,
        0x56,
        0x78,
        0x9A,
        0xBC,
        0xDE,
        0xF0,
        0xAA,
        0xBB,
        0xCC,
        0xDD,
        0xEE,
        0xFF,
        0x11,
        0x22,
    };
    const auto address = ipv6::toString(ipv6);
    ASSERT_TRUE("1234:5678:9abc:def0:aabb:ccdd:eeff:1122" == address);
}

TEST(ipv6, fullIpV6W0)
{
    quint8 ipv6[16] = {
        0x0,
        0x34,
        0x06,
        0x78,
        0x9A,
        0xBC,
        0xDE,
        0xF0,
        0xAA,
        0xBB,
        0xCC,
        0xDD,
        0xEE,
        0xFF,
        0x11,
        0x22,
    };
    const auto address = ipv6::toString(ipv6);
    ASSERT_TRUE("34:678:9abc:def0:aabb:ccdd:eeff:1122" == address);
}

TEST(ipv6, fullIpV6Full0)
{
    quint8 ipv6[16] = {
        0x0,
        0x0,
        0x06,
        0x78,
        0x9A,
        0xBC,
        0xDE,
        0xF0,
        0xAA,
        0xBB,
        0xCC,
        0xDD,
        0xEE,
        0xFF,
        0x11,
        0x22,
    };
    const auto address = ipv6::toString(ipv6);
    ASSERT_TRUE(":678:9abc:def0:aabb:ccdd:eeff:1122" == address);
}

TEST(ipv6, fullIpV6FullMultiple0)
{
    quint8 ipv6[16] = {
        0x0,
        0x0,
        0x06,
        0x78,
        0x9A,
        0xBC,
        0xDE,
        0xF0,
        0xAA,
        0xBB,
        0,
        0,
        0,
        0,
        0x11,
        0x22,
    };
    const auto address = ipv6::toString(ipv6);
    ASSERT_TRUE("0:678:9abc:def0:aabb::1122" == address);
}

TEST(ipv6, fullIpV6FullOnly0)
{
    quint8 ipv6[16] = {
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
    };
    const auto address = ipv6::toString(ipv6);
    ASSERT_TRUE("::" == address);
}

TEST(ipv6, fullIpV6LotsOf0)
{
    quint8 ipv6[16] = {
        0,
        0,
        1,
        2,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
    };
    const auto address = ipv6::toString(ipv6);
    ASSERT_TRUE("0:102::" == address);
}

TEST(ipv6, fullIpV6Local)
{
    quint8 ipv6[16] = {
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        1,
    };
    const auto address = ipv6::toString(ipv6);
    ASSERT_TRUE("::1" == address);
}

TEST(ipv6, fullIpV6LotsOf02)
{
    quint8 ipv6[16] = {
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        1,
        0,
        0,
        0,
        0,
    };
    const auto address = ipv6::toString(ipv6);
    ASSERT_TRUE("::1:0:0" == address);
}

TEST(ipv6, fullIpV6LotsOf03)
{
    quint8 ipv6[16] = {
        0x10,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        1,
        0,
        0,
        0,
        0,
    };
    const auto address = ipv6::toString(ipv6);
    ASSERT_TRUE("1000::1:0:0" == address);
}

TEST(ipv6, get)
{
    const std::string ip1 = "1:2:3:4:5:6:7:8";
    const std::string ip2 = "1::";
    const std::string ip3 = "1::8";
    const std::string ip4 = "1:2:3:4:5:6::8";
    const std::string ip5 = "1::7:8";
    const std::string ip6 = "1:2:3:4:5::7:8";
    const std::string ip7 = "1:2:3:4:5::8";
    const std::string ip8 = "1::6:7:8";
    const std::string ip9 = "1:2:3:4::6:7:8";
    const std::string ip10 = "1:2:3:4::8";
    const std::string ip11 = "1::5:6:7:8";
    const std::string ip12 = "1:2:3::5:6:7:8";
    const std::string ip13 = "1:2:3::8";
    const std::string ip14 = "1::4:5:6:7:8";
    const std::string ip15 = "1:2::4:5:6:7:8";
    const std::string ip16 = "1:2::8";
    const std::string ip17 = "1::3:4:5:6:7:8";
    const std::string ip19 = "::2:3:4:5:6:7:8";
    const std::string ip21 = "::8";

    uint8_t ip[16];
    uint8_t ip1Res[16] = {0, 1, 0, 2, 0, 3, 0, 4, 0, 5, 0, 6, 0, 7, 0, 8};
    uint8_t ip2Res[16] = {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    uint8_t ip3Res[16] = {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8};
    uint8_t ip4Res[16] = {0, 1, 0, 2, 0, 3, 0, 4, 0, 5, 0, 6, 0, 0, 0, 8};
    uint8_t ip5Res[16] = {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 8};
    uint8_t ip6Res[16] = {0, 1, 0, 2, 0, 3, 0, 4, 0, 5, 0, 0, 0, 7, 0, 8};
    uint8_t ip7Res[16] = {0, 1, 0, 2, 0, 3, 0, 4, 0, 5, 0, 0, 0, 0, 0, 8};
    uint8_t ip8Res[16] = {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 7, 0, 8};
    uint8_t ip9Res[16] = {0, 1, 0, 2, 0, 3, 0, 4, 0, 0, 0, 6, 0, 7, 0, 8};
    uint8_t ip10Res[16] = {0, 1, 0, 2, 0, 3, 0, 4, 0, 0, 0, 0, 0, 0, 0, 8};
    uint8_t ip11Res[16] = {0, 1, 0, 0, 0, 0, 0, 0, 0, 5, 0, 6, 0, 7, 0, 8};
    uint8_t ip12Res[16] = {0, 1, 0, 2, 0, 3, 0, 0, 0, 5, 0, 6, 0, 7, 0, 8};
    uint8_t ip13Res[16] = {0, 1, 0, 2, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8};
    uint8_t ip14Res[16] = {0, 1, 0, 0, 0, 0, 0, 4, 0, 5, 0, 6, 0, 7, 0, 8};
    uint8_t ip15Res[16] = {0, 1, 0, 2, 0, 0, 0, 4, 0, 5, 0, 6, 0, 7, 0, 8};
    uint8_t ip16Res[16] = {0, 1, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8};
    uint8_t ip17Res[16] = {0, 1, 0, 0, 0, 3, 0, 4, 0, 5, 0, 6, 0, 7, 0, 8};
    uint8_t ip19Res[16] = {0, 0, 0, 2, 0, 3, 0, 4, 0, 5, 0, 6, 0, 7, 0, 8};
    uint8_t ip21Res[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8};

    bool success;

    memset(ip, 0, 16);
    success = ipv6::get(ip1, ip);
    EXPECT_TRUE(success);
    ASSERT_EQ(memcmp(ip, ip1Res, 16), 0);

    memset(ip, 0, 16);
    success = ipv6::get(ip2, ip);
    EXPECT_TRUE(success);
    ASSERT_EQ(memcmp(ip, ip2Res, 16), 0);

    memset(ip, 0, 16);
    success = ipv6::get(ip3, ip);
    EXPECT_TRUE(success);
    ASSERT_EQ(memcmp(ip, ip3Res, 16), 0);

    memset(ip, 0, 16);
    success = ipv6::get(ip4, ip);
    EXPECT_TRUE(success);
    ASSERT_EQ(memcmp(ip, ip4Res, 16), 0);

    memset(ip, 0, 16);
    success = ipv6::get(ip5, ip);
    EXPECT_TRUE(success);
    ASSERT_EQ(memcmp(ip, ip5Res, 16), 0);

    memset(ip, 0, 16);
    success = ipv6::get(ip6, ip);
    EXPECT_TRUE(success);
    ASSERT_EQ(memcmp(ip, ip6Res, 16), 0);

    memset(ip, 0, 16);
    success = ipv6::get(ip7, ip);
    EXPECT_TRUE(success);
    ASSERT_EQ(memcmp(ip, ip7Res, 16), 0);

    memset(ip, 0, 16);
    success = ipv6::get(ip8, ip);
    EXPECT_TRUE(success);
    ASSERT_EQ(memcmp(ip, ip8Res, 16), 0);

    memset(ip, 0, 16);
    success = ipv6::get(ip9, ip);
    EXPECT_TRUE(success);
    ASSERT_EQ(memcmp(ip, ip9Res, 16), 0);

    memset(ip, 0, 16);
    success = ipv6::get(ip10, ip);
    EXPECT_TRUE(success);
    ASSERT_EQ(memcmp(ip, ip10Res, 16), 0);

    memset(ip, 0, 16);
    success = ipv6::get(ip11, ip);
    EXPECT_TRUE(success);
    ASSERT_EQ(memcmp(ip, ip11Res, 16), 0);

    memset(ip, 0, 16);
    success = ipv6::get(ip12, ip);
    EXPECT_TRUE(success);
    ASSERT_EQ(memcmp(ip, ip12Res, 16), 0);

    memset(ip, 0, 16);
    success = ipv6::get(ip13, ip);
    EXPECT_TRUE(success);
    ASSERT_EQ(memcmp(ip, ip13Res, 16), 0);

    memset(ip, 0, 16);
    success = ipv6::get(ip14, ip);
    EXPECT_TRUE(success);
    ASSERT_EQ(memcmp(ip, ip14Res, 16), 0);

    memset(ip, 0, 16);
    success = ipv6::get(ip15, ip);
    EXPECT_TRUE(success);
    ASSERT_EQ(memcmp(ip, ip15Res, 16), 0);

    memset(ip, 0, 16);
    success = ipv6::get(ip16, ip);
    EXPECT_TRUE(success);
    ASSERT_EQ(memcmp(ip, ip16Res, 16), 0);

    memset(ip, 0, 16);
    success = ipv6::get(ip17, ip);
    EXPECT_TRUE(success);
    ASSERT_EQ(memcmp(ip, ip17Res, 16), 0);

    memset(ip, 0, 16);
    success = ipv6::get(ip19, ip);
    EXPECT_TRUE(success);
    ASSERT_EQ(memcmp(ip, ip19Res, 16), 0);

    memset(ip, 0, 16);
    success = ipv6::get(ip21, ip);
    EXPECT_TRUE(success);
    ASSERT_EQ(memcmp(ip, ip21Res, 16), 0);
}

TEST(ipv6, mask)
{
    std::uint8_t ip1Res[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::uint8_t ip2Res[16] = {255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::uint8_t ip3Res[16] = {255, 255, 255, 255, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::uint8_t ip4Res[16] = {
        255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255};
    ASSERT_EQ(ipv6::toMask(ip1Res), 0);
    ASSERT_EQ(ipv6::toMask(ip2Res), 8);
    ASSERT_EQ(ipv6::toMask(ip3Res), 40);
    ASSERT_EQ(ipv6::toMask(ip4Res), 128);
}

TEST(mac, get)
{
    std::uint8_t mac[6];

    const std::string mac1 = "00:00:00:00:00:00";
    std::uint8_t mac1Res[6] = {0, 0, 0, 0, 0, 0};
    ASSERT_TRUE(mac::get(mac1, mac));
    ASSERT_EQ(memcmp(mac1Res, mac, 6), 0);

    const std::string mac2 = "01:02:03:04:05:06";
    std::uint8_t mac2Res[6] = {1, 2, 3, 4, 5, 6};
    ASSERT_TRUE(mac::get(mac2, mac));
    ASSERT_EQ(memcmp(mac2Res, mac, 6), 0);

    const std::string mac3 = "AB:CD:EF:12:34:56";
    std::uint8_t mac3Res[6] = {0xAB, 0xCD, 0xEF, 0x12, 0x34, 0x56};
    ASSERT_TRUE(mac::get(mac3, mac));
    ASSERT_EQ(memcmp(mac3Res, mac, 6), 0);

    const std::string mac4 = "ab:cd:ef:12:34:56";
    std::uint8_t mac4Res[6] = {0xAB, 0xCD, 0xEF, 0x12, 0x34, 0x56};
    ASSERT_TRUE(mac::get(mac4, mac));
    ASSERT_EQ(memcmp(mac4Res, mac, 6), 0);

    ASSERT_FALSE(mac::get(":::::::", mac));
    ASSERT_FALSE(mac::get("00:00:00:00", mac));
    ASSERT_FALSE(mac::get("00:00:00:00:", mac));
    ASSERT_FALSE(mac::get("0:0:0:0:0:0", mac));
    ASSERT_FALSE(mac::get("00:00:00:00:00:00:", mac));
    ASSERT_FALSE(mac::get("00", mac));
    ASSERT_FALSE(mac::get("123:00:00:00:99", mac));
}

TEST(mac, toString)
{
    const std::uint8_t mac1[6] = {0, 0, 0, 0, 0, 0};
    const std::uint8_t mac2[6] = {1, 2, 3, 4, 5, 6};
    const std::uint8_t mac3[6] = {0xAB, 0xCD, 0xEF, 0x12, 0x34, 0x56};

    ASSERT_EQ(mac::toString(mac1), "00:00:00:00:00:00");
    ASSERT_EQ(mac::toString(mac2), "01:02:03:04:05:06");
    ASSERT_EQ(mac::toString(mac3), "ab:cd:ef:12:34:56");
}
