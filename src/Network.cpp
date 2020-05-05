#include <Stringify/Network.hpp>
#include <regex>
#include <sstream>

using namespace stringify::net;

template<typename _Type>
static std::string to_hex(_Type ptr, std::size_t justified = 0)
{
    std::stringstream stream;
    stream << std::hex << std::size_t(ptr);
    const auto str = stream.str();

    if(str.size() < justified)
    {
        std::string toPrepend;
        for(std::size_t i = 0; i < (justified - str.size()); ++i) toPrepend += '0';
        return toPrepend + str;
    }

    return str;
}

std::string ipv4::toString(const std::uint32_t address)
{
    return std::to_string((address >> 24) & 0xFF) + "." + std::to_string((address >> 16) & 0xFF) +
           "." + std::to_string((address >> 8) & 0xFF) + "." + std::to_string((address)&0xFF);
}

bool ipv4::get(const std::string& subject, std::uint32_t& address)
{
    static const std::regex regex("^(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\."
                                  "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\."
                                  "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\."
                                  "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$");

    std::smatch match;

    if(std::regex_match(subject, match, regex) && match.size() == 5)
    {
        address = std::uint32_t(std::stoi(match[1].str())) << 24 |
                  std::uint32_t(std::stoi(match[2].str())) << 16 |
                  std::uint32_t(std::stoi(match[3].str())) << 8 |
                  std::uint32_t(std::stoi(match[4].str()));

        return true;
    }

    return false;
}

bool ipv4::isValid(const std::string& subject)
{
    std::uint32_t address;
    return get(subject, address);
}

std::uint8_t ipv4::toMask(const std::uint32_t ip)
{
    std::uint8_t mask = 0;
    for(auto i = 0; i < 32; ++i)
    {
        const bool bit = ip & (1 << (31 - i));
        if(bit)
            ++mask;
        else
            break;
    }
    return mask;
}

std::string ipv6::toString(const std::uint8_t* address)
{
    constexpr int MAX_IP_BLOCK = 8;
    std::string res[MAX_IP_BLOCK];

    int startZeroToRemove = -1;
    int maxZeroCounter = 0;

    int currentStartZero = -1;
    int currentZeroCounter = 0;

    for(int i = 0; i < MAX_IP_BLOCK; ++i)
    {
        const std::uint16_t g =
            ((address[(i << 1) + 1]) & 0xFF) | std::uint16_t(((address[(i << 1)] & 0xFF) << 8));
        if(!g)
        {
            ++currentZeroCounter;
            if(currentStartZero < 0)
                currentStartZero = i;
        }
        else
        {
            if(currentZeroCounter > maxZeroCounter)
            {
                startZeroToRemove = currentStartZero;
                maxZeroCounter = currentZeroCounter;
            }
            currentZeroCounter = 0;
            currentStartZero = -1;
        }

        res[i] = to_hex(g);
    }
    if(currentZeroCounter > maxZeroCounter)
    {
        startZeroToRemove = currentStartZero;
        maxZeroCounter = currentZeroCounter;
    }

    std::string finalRes;
    bool prevWas0 = false;
    for(int i = 0; i < MAX_IP_BLOCK; ++i)
    {
        if(i >= startZeroToRemove && i < startZeroToRemove + maxZeroCounter)
        {
            prevWas0 = true;
        }
        else
        {
            if(prevWas0)
            {
                finalRes += ":";
                if(!startZeroToRemove && maxZeroCounter > 1)
                    finalRes += ":";
                prevWas0 = false;
            }
            finalRes += res[i];
            if(i < MAX_IP_BLOCK - 1)
                finalRes += ":";
        }
    }
    if(prevWas0)
    {
        finalRes += ":";
        if(!startZeroToRemove && maxZeroCounter > 1)
            finalRes += ":";
    }

    return finalRes;
}

bool ipv6::isValid(const std::string& subject)
{
    static const std::regex regex(
        "((([0-9A-Fa-f]{1,4}:){7}([0-9A-Fa-f]{1,4}|:))|"
        "(([0-9A-Fa-f]{1,4}:){6}(:[0-9A-Fa-f]{1,4}|"
        "((25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])"
        "(\\.(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])){3})|:))|"
        "(([0-9A-Fa-f]{1,4}:){5}(((:[0-9A-Fa-f]{1,4}){1,2})|"
        ":((25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])"
        "(\\.(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])){3})|:))|"
        "(([0-9A-Fa-f]{1,4}:){4}(((:[0-9A-Fa-f]{1,4}){1,3})|"
        "((:[0-9A-Fa-f]{1,4})?:((25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])"
        "(\\.(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])){3}))|:))|"
        "(([0-9A-Fa-f]{1,4}:){3}(((:[0-9A-Fa-f]{1,4}){1,4})|"
        "((:[0-9A-Fa-f]{1,4}){0,2}:((25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])"
        "(\\.(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])){3}))|:))|"
        "(([0-9A-Fa-f]{1,4}:){2}(((:[0-9A-Fa-f]{1,4}){1,5})|"
        "((:[0-9A-Fa-f]{1,4}){0,3}:((25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])"
        "(\\.(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])){3}))|:))|"
        "(([0-9A-Fa-f]{1,4}:){1}(((:[0-9A-Fa-f]{1,4}){1,6})|"
        "((:[0-9A-Fa-f]{1,4}){0,4}:((25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])"
        "(\\.(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])){3}))|:))|"
        "(:(((:[0-9A-Fa-f]{1,4}){1,7})|((:[0-9A-Fa-f]{1,4}){0,5}:"
        "((25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])"
        "(\\.(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])){3}))|:)))(%.+)?");
    std::smatch match;

    return std::regex_match(subject, match, regex);
}

bool ipv6::get(const std::string& subject, std::uint8_t* address)
{
    if(!address)
        return false;
    if(!isValid(subject))
        return false;

    std::size_t offset = 0;
    std::size_t numberOfLeftDigit = 0;
    std::size_t numberOfRightDigit = 0;

    std::string digits[8];
    std::string rightDigits[8];

    for(auto& digit: digits)
    {
        for(auto i = 0; i < 4; ++i)
        {
            if(offset >= subject.size())
                break;
            const auto currentChar = subject.at(offset);
            offset += 1;
            if(currentChar == ':')
                break;
            digit.push_back(currentChar);
        }
        if(!subject.empty() && offset < subject.size() && subject.at(offset) == ':')
        {
            ++offset;
            break;
        }
        ++numberOfLeftDigit;
    }
    for(auto& digit: rightDigits)
    {
        for(auto i = 0; i < 4; ++i)
        {
            if(offset >= subject.size())
                break;
            const auto currentChar = subject.at(offset);
            offset += 1;
            if(currentChar == ':')
                break;
            digit.push_back(currentChar);
        }
        if(!digit.empty())
            ++numberOfRightDigit;
        else
            break;

        if(offset >= subject.size())
            break;
    }

    for(std::size_t i = 0; i < numberOfRightDigit; ++i)
        digits[8 - i - 1] = rightDigits[numberOfRightDigit - i - 1];

    memset(address, 0, 16);
    for(auto i = 0; i < 8; ++i)
    {
        if(digits[i].empty())
            continue;
        const std::uint16_t digit = std::stoi(digits[i], nullptr, 16);
        address[i * 2] = std::uint8_t((digit >> 8) & 0xFF);
        address[(i * 2) + 1] = std::uint8_t(digit & 0xFF);
    }

    return true;
}

std::uint8_t ipv6::toMask(const std::uint8_t* ip)
{
    std::uint8_t mask = 0;
    for(auto i = 0; i < 16; ++i)
    {
        for(auto j = 0; j < 8; ++j)
        {
            const bool bit = ip[i] & (1 << (7 - j));
            if(bit)
                ++mask;
            else
                return mask;
        }
    }
    return mask;
}

bool mac::get(const std::string& subject, std::uint8_t* mac)
{
    if(!mac)
        return false;
    static const std::regex regex("^([0-9a-fA-F][0-9a-fA-F])(?::)"
                                  "([0-9a-fA-F][0-9a-fA-F])(?::)"
                                  "([0-9a-fA-F][0-9a-fA-F])(?::)"
                                  "([0-9a-fA-F][0-9a-fA-F])(?::)"
                                  "([0-9a-fA-F][0-9a-fA-F])(?::)"
                                  "([0-9a-fA-F][0-9a-fA-F])$");

    std::smatch match;

    if(std::regex_match(subject, match, regex) && match.size() == 7)
    {
        for(auto i = 0; i < 6; ++i) mac[i] = std::stoi(match[i + 1].str(), nullptr, 16) & 0xFF;
        return true;
    }
    std::memset(mac, 0, 6);
    return false;
}

bool mac::isValid(const std::string& subject)
{
    std::uint8_t mac[6];
    return get(subject, mac);
}

std::string mac::toString(const std::uint8_t* mac)
{
    if(!mac)
        return "00:00:00:00:00:00";
    std::string res;
    for(auto i = 0; i < 5; ++i)
    {
        res += to_hex(mac[i], 2);
        res += ':';
    }
    res += to_hex(mac[5], 2);
    return res;
}
