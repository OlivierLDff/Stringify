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
    _readable(QString::number(_major) + "." +
        QString::number(_minor) + "." +
        QString::number(_patch) + "." +
        QString::number(_tag, 16))
{
}
