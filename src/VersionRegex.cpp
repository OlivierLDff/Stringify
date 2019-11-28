// ─────────────────────────────────────────────────────────────
//                  INCLUDE
// ─────────────────────────────────────────────────────────────

// C Header

// C++ Header

// Qt Header
#include <QRegularExpression>

// Dependencies Header

// Application Header
#include <Stringify/VersionRegex.hpp>

// ─────────────────────────────────────────────────────────────
//                  DECLARATION
// ─────────────────────────────────────────────────────────────

STRINGIFY_USING_NAMESPACE;

// ─────────────────────────────────────────────────────────────
//                  FUNCTIONS
// ─────────────────────────────────────────────────────────────
//
bool VersionRegex::getFullVersion(const QString& subject, quint8& major, quint8& minor, quint8& patch, quint32& tag)
{
    static const QRegularExpression re(QStringLiteral(
            "^(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\."
            "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\."
            "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\."
            "(?:0x){0,1}([0-9A-Fa-f]{1,8})$")
    );
    const QRegularExpressionMatch match = re.match(subject);
    const bool hasMatch = match.hasMatch();
    if (!hasMatch)
        return false;
    bool ok = false;
    major = match.captured(1).toUInt(&ok);
    if (!ok)
        return false;
    minor = match.captured(2).toUInt(&ok);
    if (!ok)
        return false;
    patch = match.captured(3).toUInt(&ok);
    if (!ok)
        return false;
    tag = match.captured(4).toUInt(&ok, 16);
    if (!ok)
        return false;

    return true;
}

bool VersionRegex::getVersion(const QString& subject, quint8& major, quint8& minor, quint8& patch)
{
    static const QRegularExpression re(QStringLiteral(
            "^(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\."
            "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\."
            "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.")
    );
    const QRegularExpressionMatch match = re.match(subject);
    const bool hasMatch = match.hasMatch();
    if (!hasMatch)
        return false;
    bool ok = false;
    major = match.captured(1).toUInt(&ok);
    if (!ok)
        return false;
    minor = match.captured(2).toUInt(&ok);
    if (!ok)
        return false;
    patch = match.captured(3).toUInt(&ok);
    if (!ok)
        return false;

    return true;
}

QString VersionRegex::versionToString(quint8& major, quint8& minor, quint8& patch, quint32& tag)
{
    return QString::number(major) + QStringLiteral(".") +
        QString::number(minor) + QStringLiteral(".") +
        QString::number(patch) + QStringLiteral(".") +
        QString::number(tag, 16).rightJustified(8, QChar('0'));
}
