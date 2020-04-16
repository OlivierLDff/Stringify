// ─────────────────────────────────────────────────────────────
//                  INCLUDE
// ─────────────────────────────────────────────────────────────

// Application Header
#include <Stringify/Version.hpp>

// ─────────────────────────────────────────────────────────────
//                  DECLARATION
// ─────────────────────────────────────────────────────────────

using namespace Stringify;

// ─────────────────────────────────────────────────────────────
//                  FUNCTIONS
// ─────────────────────────────────────────────────────────────

Version::Version(QObject* parent): QObject(parent),
    _major(STRINGIFY_VERSION_MAJOR),
    _minor(STRINGIFY_VERSION_MINOR),
    _patch(STRINGIFY_VERSION_PATCH),
    _tag(STRINGIFY_VERSION_TAG_HEX),
    _readable(QString::number(_major) + QStringLiteral(".") +
        QString::number(_minor) + QStringLiteral(".") +
        QString::number(_patch) + QStringLiteral(".0x") +
        QString::number(_tag, 16).rightJustified(8, QChar('0')))
{
}
