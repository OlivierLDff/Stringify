// ─────────────────────────────────────────────────────────────
//                  INCLUDE
// ─────────────────────────────────────────────────────────────

// C Header

// C++ Header

// Qt Header
#include <QCoreApplication> // Call register type at startup when loaded as a dynamic library
#include <QLoggingCategory> // Logging support

// Dependencies Header

// Application Header
#include <Stringify/Utils.hpp>
#include <Stringify/Version.hpp>

// ─────────────────────────────────────────────────────────────
//                  DECLARATION
// ─────────────────────────────────────────────────────────────

Q_LOGGING_CATEGORY(STRINGIFY_UTILS_LOG_CAT, "stringify.utils")

// ─────────────────────────────────────────────────────────────
//                  FUNCTIONS
// ─────────────────────────────────────────────────────────────

static const char* _defaultUri = "Stringify";
static const char** _uri = &_defaultUri;
static quint8 _major = 1;
static quint8 _minor = 0;

static void Stringify_registerTypes()
{
    qCDebug(STRINGIFY_UTILS_LOG_CAT, "Register Stringify v%s", qPrintable(Stringify::Version::version().readable()));

    qCDebug(STRINGIFY_UTILS_LOG_CAT, "Register Singleton %s.Version %d.%d to QML", *_uri, _major, _minor);
	STRINGIFY_NAMESPACE::Version::registerSingleton(*_uri, _major, _minor);
}

static void Stringify_registerTypes(const char* uri, const quint8 major, const quint8 minor)
{
    if(uri)
        _uri = &uri;
    _major = major;
    _minor = minor;
    Stringify_registerTypes();
}

static void Stringify_loadResources()
{
    qCDebug(STRINGIFY_UTILS_LOG_CAT, "Load Stringify.qrc v%s", qPrintable(Stringify::Version::version().readable()));
    Q_INIT_RESOURCE(Stringify);
}

#ifndef STRINGIFY_STATIC
Q_COREAPP_STARTUP_FUNCTION(Stringify_registerTypes);
Q_COREAPP_STARTUP_FUNCTION(Stringify_loadResources);
#endif

STRINGIFY_USING_NAMESPACE;

void Utils::registerTypes(const char* uri, const quint8 major, const quint8 minor)
{
    ::Stringify_registerTypes(uri, major, minor);
}

void Utils::loadResources()
{
    ::Stringify_loadResources();
}
