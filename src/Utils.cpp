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

static void registerTypes()
{
    // Controller
    //qCDebug(STRINGIFY_REGISTER_LOG_CAT, "Register %s.Controller %d.%d to QML", *_uri, _major, _minor);
    //STRINGIFY_NAMESPACE::Controller::registerToQml(*_uri, _major, _minor);
	STRINGIFY_NAMESPACE::Version::registerSingleton(*_uri, _major, _minor);
}

static void registerTypes(const char* uri, const quint8 major, const quint8 minor)
{
    if(uri)
        _uri = &uri;
    _major = major;
    _minor = minor;
    registerTypes();
}

static void loadResources()
{
    Q_INIT_RESOURCE(Stringify);
}

Q_COREAPP_STARTUP_FUNCTION(registerTypes);
Q_COREAPP_STARTUP_FUNCTION(loadResources);

STRINGIFY_USING_NAMESPACE;

void Utils::registerTypes(const char* uri, const quint8 major, const quint8 minor)
{
    ::registerTypes(uri, major, minor);
}

void Utils::loadResources()
{
    ::loadResources();
}
