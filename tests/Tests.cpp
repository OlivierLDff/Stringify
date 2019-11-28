#include <gtest/gtest.h>

#include <Stringify.hpp>

class AddressRegexTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }
public:
};

STRINGIFY_USING_NAMESPACE;

TEST_F(AddressRegexTest, ipv6)
{
    const QString ip1  = QString("1:2:3:4:5:6:7:8");
    const QString ip2  = QString("1::");
    const QString ip3  = QString("1::8");
    const QString ip4  = QString("1:2:3:4:5:6::8");
    const QString ip5  = QString("1::7:8");
    const QString ip6  = QString("1:2:3:4:5::7:8");
    const QString ip7  = QString("1:2:3:4:5::8");
    const QString ip8  = QString("1::6:7:8");
    const QString ip9  = QString("1:2:3:4::6:7:8");
    const QString ip10 = QString("1:2:3:4::8");
    const QString ip11 = QString("1::5:6:7:8");
    const QString ip12 = QString("1:2:3::5:6:7:8");
    const QString ip13 = QString("1:2:3::8");
    const QString ip14 = QString("1::4:5:6:7:8");
    const QString ip15 = QString("1:2::4:5:6:7:8");
    const QString ip16 = QString("1:2::8");
    const QString ip17 = QString("1::3:4:5:6:7:8");
    const QString ip19 = QString("::2:3:4:5:6:7:8");
    const QString ip21 = QString("::8");

    uint8_t ip[16];
    uint8_t ip1Res[16] =  { 0, 1, 0, 2, 0, 3, 0, 4, 0, 5, 0, 6, 0, 7, 0, 8 };
    uint8_t ip2Res[16] =  { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    uint8_t ip3Res[16] =  { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8 };
    uint8_t ip4Res[16] =  { 0, 1, 0, 2, 0, 3, 0, 4, 0, 5, 0, 6, 0, 0, 0, 8 };
    uint8_t ip5Res[16] =  { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 8 };
    uint8_t ip6Res[16] =  { 0, 1, 0, 2, 0, 3, 0, 4, 0, 5, 0, 0, 0, 7, 0, 8 };
    uint8_t ip7Res[16] =  { 0, 1, 0, 2, 0, 3, 0, 4, 0, 5, 0, 0, 0, 0, 0, 8 };
    uint8_t ip8Res[16] =  { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 7, 0, 8 };
    uint8_t ip9Res[16] =  { 0, 1, 0, 2, 0, 3, 0, 4, 0, 0, 0, 6, 0, 7, 0, 8 };
    uint8_t ip10Res[16] = { 0, 1, 0, 2, 0, 3, 0, 4, 0, 0, 0, 0, 0, 0, 0, 8 };
    uint8_t ip11Res[16] = { 0, 1, 0, 0, 0, 0, 0, 0, 0, 5, 0, 6, 0, 7, 0, 8 };
    uint8_t ip12Res[16] = { 0, 1, 0, 2, 0, 3, 0, 0, 0, 5, 0, 6, 0, 7, 0, 8 };
    uint8_t ip13Res[16] = { 0, 1, 0, 2, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8 };
    uint8_t ip14Res[16] = { 0, 1, 0, 0, 0, 0, 0, 4, 0, 5, 0, 6, 0, 7, 0, 8 };
    uint8_t ip15Res[16] = { 0, 1, 0, 2, 0, 0, 0, 4, 0, 5, 0, 6, 0, 7, 0, 8 };
    uint8_t ip16Res[16] = { 0, 1, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8 };
    uint8_t ip17Res[16] = { 0, 1, 0, 0, 0, 3, 0, 4, 0, 5, 0, 6, 0, 7, 0, 8 };
    uint8_t ip19Res[16] = { 0, 0, 0, 2, 0, 3, 0, 4, 0, 5, 0, 6, 0, 7, 0, 8 };
    uint8_t ip21Res[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8 };

    memset(ip, 0, 16);
    AddressRegex::getIpv6(ip1, ip);
    ASSERT_EQ(memcmp(ip, ip1Res, 16), 0);

    memset(ip, 0, 16);
    AddressRegex::getIpv6(ip2, ip);
    ASSERT_EQ(memcmp(ip, ip2Res, 16), 0);

    memset(ip, 0, 16);
    AddressRegex::getIpv6(ip3, ip);
    ASSERT_EQ(memcmp(ip, ip3Res, 16), 0);

    memset(ip, 0, 16);
    AddressRegex::getIpv6(ip4, ip);
    ASSERT_EQ(memcmp(ip, ip4Res, 16), 0);

    memset(ip, 0, 16);
    AddressRegex::getIpv6(ip5, ip);
    ASSERT_EQ(memcmp(ip, ip5Res, 16), 0);

    memset(ip, 0, 16);
    AddressRegex::getIpv6(ip6, ip);
    ASSERT_EQ(memcmp(ip, ip6Res, 16), 0);

    memset(ip, 0, 16);
    AddressRegex::getIpv6(ip7, ip);
    ASSERT_EQ(memcmp(ip, ip7Res, 16), 0);

    memset(ip, 0, 16);
    AddressRegex::getIpv6(ip8, ip);
    ASSERT_EQ(memcmp(ip, ip8Res, 16), 0);

    memset(ip, 0, 16);
    AddressRegex::getIpv6(ip9, ip);
    ASSERT_EQ(memcmp(ip, ip9Res, 16), 0);

    memset(ip, 0, 16);
    AddressRegex::getIpv6(ip10, ip);
    ASSERT_EQ(memcmp(ip, ip10Res, 16), 0);

    memset(ip, 0, 16);
    AddressRegex::getIpv6(ip11, ip);
    ASSERT_EQ(memcmp(ip, ip11Res, 16), 0);

    memset(ip, 0, 16);
    AddressRegex::getIpv6(ip12, ip);
    ASSERT_EQ(memcmp(ip, ip12Res, 16), 0);

    memset(ip, 0, 16);
    AddressRegex::getIpv6(ip13, ip);
    ASSERT_EQ(memcmp(ip, ip13Res, 16), 0);

    memset(ip, 0, 16);
    AddressRegex::getIpv6(ip14, ip);
    ASSERT_EQ(memcmp(ip, ip14Res, 16), 0);

    memset(ip, 0, 16);
    AddressRegex::getIpv6(ip15, ip);
    ASSERT_EQ(memcmp(ip, ip15Res, 16), 0);

    memset(ip, 0, 16);
    AddressRegex::getIpv6(ip16, ip);
    ASSERT_EQ(memcmp(ip, ip16Res, 16), 0);

    memset(ip, 0, 16);
    AddressRegex::getIpv6(ip17, ip);
    ASSERT_EQ(memcmp(ip, ip17Res, 16), 0);

    memset(ip, 0, 16);
    AddressRegex::getIpv6(ip19, ip);
    ASSERT_EQ(memcmp(ip, ip19Res, 16), 0);

    memset(ip, 0, 16);
    AddressRegex::getIpv6(ip21, ip);
    ASSERT_EQ(memcmp(ip, ip21Res, 16), 0);

    // todo move with real tests
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}