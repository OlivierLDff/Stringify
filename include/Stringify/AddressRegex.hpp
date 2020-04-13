#ifndef __STRINGIFY_ADDRESSREGEX_HPP__
#define __STRINGIFY_ADDRESSREGEX_HPP__

// ─────────────────────────────────────────────────────────────
//                  INCLUDE
// ─────────────────────────────────────────────────────────────

// C Header

// C++ Header

// Qt Header
#include <QString>

// Dependencies Header

// Application Header
#include <Stringify/Export.hpp>

// ─────────────────────────────────────────────────────────────
//                  DECLARATION
// ─────────────────────────────────────────────────────────────

STRINGIFY_NAMESPACE_START

// ─────────────────────────────────────────────────────────────
//                  CLASS
// ─────────────────────────────────────────────────────────────

class AddressRegex
{
public:
    static QString ipv4ToString(const quint32 address);
    static QString ipv6ToString(const quint8* address);
    static bool getIpv4(const QString& subject, quint32& address);
    static bool isIpv6(const QString& subject);
    static bool getIpv6(const QString& subject, quint8* address);
    static bool getMacAddress(const QString& subject, quint8* mac);
    static QString macAddressToString(const quint8* mac);
};

STRINGIFY_NAMESPACE_END

#endif // __STRINGIFY_ADDRESSREGEX_HPP__
