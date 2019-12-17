// ─────────────────────────────────────────────────────────────
//                  INCLUDE
// ─────────────────────────────────────────────────────────────

// C Header

// C++ Header

// Qt Header
#include <QString>

// Dependencies Header

// Application Header
#include <Stringify/Version.hpp>
#include <Stringify/VersionRegex.hpp>

// ─────────────────────────────────────────────────────────────
//                  DECLARATION
// ─────────────────────────────────────────────────────────────

STRINGIFY_USING_NAMESPACE

// ─────────────────────────────────────────────────────────────
//                  FUNCTIONS
// ─────────────────────────────────────────────────────────────

Version::Version(QObject* parent): QObject(parent),
    _major(STRINGIFY_VERSION_MAJOR),
    _minor(STRINGIFY_VERSION_MINOR),
    _patch(STRINGIFY_VERSION_PATCH),
    _tag(STRINGIFY_VERSION_TAG_HEX),
    _readable(Stringify::VersionRegex::fullVersionToString(_major, _minor, _patch, _tag))
{
}
