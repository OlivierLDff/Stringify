#ifndef __STRINGIFY_ADDRESSREGEX_HPP__
#define __STRINGIFY_ADDRESSREGEX_HPP__

// ─────────────────────────────────────────────────────────────
//                  INCLUDE
// ─────────────────────────────────────────────────────────────

// Application Headers
#include <Stringify/Export.hpp>

// Qt Headers
#include <QtGlobal>
#include <QString>

// ─────────────────────────────────────────────────────────────
//                  DECLARATION
// ─────────────────────────────────────────────────────────────

namespace Stringify {

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

}

#endif
