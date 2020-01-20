// ─────────────────────────────────────────────────────────────
//                  INCLUDE
// ─────────────────────────────────────────────────────────────

// C Header

// C++ Header

// Qt Header
#include <QRegularExpression>

// Dependencies Header

// Application Header
#include <Stringify/AddressRegex.hpp>

// ─────────────────────────────────────────────────────────────
//                  DECLARATION
// ─────────────────────────────────────────────────────────────

STRINGIFY_USING_NAMESPACE;

// ─────────────────────────────────────────────────────────────
//                  FUNCTIONS
// ─────────────────────────────────────────────────────────────
//
QString AddressRegex::ipv4ToString(const quint32 address)
{
    return QString::number((address >> 24) & 0xFF) + QStringLiteral(".") +
        QString::number((address >> 16) & 0xFF) + QStringLiteral(".") +
        QString::number((address >> 8) & 0xFF) + QStringLiteral(".") +
        QString::number((address) & 0xFF);
}

QString AddressRegex::ipv6ToString(const quint8* address)
{
    constexpr int MAX_IP_BLOCK = 8;
    QString res[MAX_IP_BLOCK];

    int startZeroToRemove = -1;
    int maxZeroCounter = 0;

    int currentStartZero = -1;
    int currentZeroCounter = 0;

    for (int i = 0; i < MAX_IP_BLOCK; ++i)
    {
        const quint16 g = ((address[(i << 1) + 1]) & 0xFF) | quint16(((address[(i << 1)] & 0xFF) << 8));
        if (!g)
        {
            ++currentZeroCounter;
            if (currentStartZero < 0)
                currentStartZero = i;
        }
        else
        {
            if (currentZeroCounter > maxZeroCounter)
            {
                startZeroToRemove = currentStartZero;
                maxZeroCounter = currentZeroCounter;
            }
            currentZeroCounter = 0;
            currentStartZero = -1;
        }

        res[i] = QString::number(g, 16);
    }
    if (currentZeroCounter > maxZeroCounter)
    {
        startZeroToRemove = currentStartZero;
        maxZeroCounter = currentZeroCounter;
    }

    QString finalRes;
    bool prevWas0 = false;
    for (int i = 0; i < MAX_IP_BLOCK; ++i)
    {
        if (i >= startZeroToRemove && i < startZeroToRemove + maxZeroCounter)
        {
            prevWas0 = true;
        }
        else
        {
            if (prevWas0)
            {
                finalRes += QStringLiteral(":");
                if (!startZeroToRemove && maxZeroCounter > 1)
                    finalRes += QStringLiteral(":");
                prevWas0 = false;
            }
            finalRes += res[i];
            if (i < MAX_IP_BLOCK - 1)
                finalRes += QStringLiteral(":");
        }
    }
    if (prevWas0)
    {
        finalRes += QStringLiteral(":");
        if (!startZeroToRemove && maxZeroCounter > 1)
            finalRes += QStringLiteral(":");
    }

    return finalRes;
}

bool AddressRegex::getIpv4(const QString& subject, quint32& address)
{
    static const QRegularExpression re(QStringLiteral(
            "^(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\."
            "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\."
            "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\."
            "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$")
    );
    const QRegularExpressionMatch match = re.match(subject);
    const bool hasMatch = match.hasMatch();
    if (!hasMatch)
        return false;
    bool ok = false;
    address = 0;
    address |= (match.captured(1).toUInt(&ok) & 0xFF) << 24;
    if (!ok)
        return false;
    address |= (match.captured(2).toUInt(&ok) & 0xFF) << 16;
    if (!ok)
        return false;
    address |= (match.captured(3).toUInt(&ok) & 0xFF) << 8;
    if (!ok)
        return false;
    address |= (match.captured(4).toUInt(&ok) & 0xFF) << 8;
    if (!ok)
        return false;

    return true;
}

bool AddressRegex::isIpv6(const QString& subject)
{
    static const QRegularExpression re(QStringLiteral(
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
            "(\\.(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])){3}))|:)))(%.+)?")
    );
    const QRegularExpressionMatch match = re.match(subject);
    return match.hasMatch();
}

bool AddressRegex::getIpv6(const QString& subject, quint8* address)
{
    if (!address)
        return false;
    if (!isIpv6(subject))
        return false;

    int offset = 0;
    int numberOfLeftDigit = 0;
    int numberOfRightDigit = 0;

    QString digits[8];
    QString rightDigits[8];

    for (auto& digit : digits)
    {
        for (auto i = 0; i < 4; ++i)
        {
            if (offset >= subject.size())
                break;
            const auto currentChar = subject.at(offset);
            offset += 1;
            if (currentChar == QChar(':'))
                break;
            digit.append(currentChar);
        }
        if (subject.size() && offset < subject.size() && subject.at(offset) == QChar(':'))
        {
            ++offset;
            break;
        }
        ++numberOfLeftDigit;
    }
    for (auto& digit : rightDigits)
    {
        for (auto i = 0; i < 4; ++i)
        {
            if (offset >= subject.size())
                break;
            const auto currentChar = subject.at(offset);
            offset += 1;
            if (currentChar == QChar(':'))
                break;
            digit.append(currentChar);
        }
        if (digit.size())
            ++numberOfRightDigit;
        else
            break;

        if (offset >= subject.size())
            break;
    }

    for (auto i = 0; i < numberOfRightDigit; ++i)
        digits[8 - i - 1] = rightDigits[numberOfRightDigit - i - 1];

    memset(address, 0, 16);
    for (auto i = 0; i < 8; ++i)
    {
        if (digits[i].size() == 0)
            continue;
        bool ok = false;
        const quint16 digit = digits[i].toUInt(&ok, 16);
        if (!ok)
            return false;
        address[i * 2] = quint8((digit >> 8) & 0xFF);
        address[(i * 2) + 1] = quint8(digit & 0xFF);
    }

    return true;
}

bool AddressRegex::getMacAddress(const QString& subject, quint8* mac)
{
    if (!mac)
        return false;
    static const QRegularExpression re(QStringLiteral(
            "^([0-9a-fA-F][0-9a-fA-F])(?>:)"
            "([0-9a-fA-F][0-9a-fA-F])(?>:)"
            "([0-9a-fA-F][0-9a-fA-F])(?>:)"
            "([0-9a-fA-F][0-9a-fA-F])(?>:)"
            "([0-9a-fA-F][0-9a-fA-F])(?>:)"
            "([0-9a-fA-F][0-9a-fA-F])$")
    );
    const QRegularExpressionMatch match = re.match(subject);
    const bool hasMatch = match.hasMatch();
    if (!hasMatch)
        return false;
    bool ok = false;
    memset(mac, 0, 6);
    mac[0] |= (match.captured(1).toUInt(&ok) & 0xFF);
    if (!ok)
        return false;
    mac[1] |= (match.captured(2).toUInt(&ok) & 0xFF);
    if (!ok)
        return false;
    mac[2] |= (match.captured(3).toUInt(&ok) & 0xFF);
    if (!ok)
        return false;
    mac[3] |= (match.captured(4).toUInt(&ok) & 0xFF);
    if (!ok)
        return false;
    mac[4] |= (match.captured(5).toUInt(&ok) & 0xFF);
    if (!ok)
        return false;
    mac[5] |= (match.captured(6).toUInt(&ok) & 0xFF);
    if (!ok)
        return false;

    return true;
}

QString AddressRegex::macAddressToString(const quint8* mac)
{
    if (!mac)
        return QStringLiteral("00:00:00:00:00:00");
    QString res;
    for (auto i = 0; i < 5; ++i)
    {
        res += QString::number(mac[i], 16).rightJustified(2, QChar('0'));
        res += QStringLiteral(":");
    }
    res += QString::number(mac[5], 16).rightJustified(2, QChar('0'));
    return res;
}
