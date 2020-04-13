#ifndef __STRINGIFY_VERSION_REGEX_HPP__
#define __STRINGIFY_VERSION_REGEX_HPP__

// ─────────────────────────────────────────────────────────────
//                  INCLUDE
// ─────────────────────────────────────────────────────────────

// C Header

// C++ Header

// Qt Header
#include <QObject>

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

class STRINGIFY_API_ VersionRegex
{
public:
    /**
     * \brief Extract version digit from a version string.
     * - 1.2.3.0x12345678
     * - 0.255.254.0xABCDEF12
     * \param subject Represent a version in the for 1.2.3.12A45ABC
     * \param major Major version in the string, between 1 to 255
     * \param minor Minor version in the string, between 1 to 255
     * \param patch Patch version in the string, between 1 to 255
     * \param tag Git tag in hex, can be with a 0x prefix. (which will be ignored)
     * \return true if the string could have been parsed and every subitem were parsed correctly
     */
    static bool getFullVersion(const QString& subject, quint8& major, quint8& minor, quint8& patch, quint32& tag);

    /**
     * \brief Extract version digit from a version string.
     * - 1.2.3
     * - 0.255.254
     * \param subject Represent a version in the for 1.2.3
     * \param major Major version in the string, between 1 to 255
     * \param minor Minor version in the string, between 1 to 255
     * \param patch Patch version in the string, between 1 to 255
     * \return true if the string could have been parsed and every subitem were parsed correctly
     */
    static bool getVersion(const QString& subject, quint8& major, quint8& minor, quint8& patch);

    static QString fullVersionToString(const quint8& major, const quint8& minor, const quint8& patch, const quint32& tag);

    static QString versionToString(const quint8& major, const quint8& minor, const quint8& patch);
};
STRINGIFY_NAMESPACE_END

#endif // __STRINGIFY_VERSION_REGEX_HPP__
