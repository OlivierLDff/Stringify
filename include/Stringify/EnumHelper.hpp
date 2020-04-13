#ifndef __STRINGIFY_ENUM_HELPER_HPP__
#define __STRINGIFY_ENUM_HELPER_HPP__

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

class EnumHelper
{
public:
    static QString valueToStrWithHex(const QString& s, int value)
    {
        return s + QStringLiteral(" (0x") + QString::number(value, 16) + QStringLiteral(")");
    }
};

STRINGIFY_NAMESPACE_END

#endif
