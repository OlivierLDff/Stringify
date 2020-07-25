// ─────────────────────────────────────────────────────────────
//                  INCLUDE
// ─────────────────────────────────────────────────────────────

// Application Headers
#include <Stringify/Utils.hpp>
#include <Stringify/Version.hpp>
#include <Stringify/Logger.hpp>

// Qt Headers
#include <QCoreApplication>  // Call register type at startup when loaded as a dynamic library

// ─────────────────────────────────────────────────────────────
//                  DECLARATION
// ─────────────────────────────────────────────────────────────

// clang-format off
#ifdef NDEBUG
# define LOG_DEV_DEBUG(str, ...) do {} while (0)
#else
# define LOG_DEV_DEBUG(str, ...) stringify::Logger::UTILS->debug( str, ## __VA_ARGS__ )
#endif

#ifdef NDEBUG
# define LOG_DEV_INFO(str, ...)  do {} while (0)
#else
# define LOG_DEV_INFO(str, ...)  stringify::Logger::UTILS->info(  str, ## __VA_ARGS__ )
#endif

#ifdef NDEBUG
# define LOG_DEV_WARN(str, ...)  do {} while (0)
#else
# define LOG_DEV_WARN(str, ...)  stringify::Logger::UTILS->warn(  str, ## __VA_ARGS__ )
#endif

#ifdef NDEBUG
# define LOG_DEV_ERR(str, ...)   do {} while (0)
#else
# define LOG_DEV_ERR(str, ...)   stringify::Logger::UTILS->error( str, ## __VA_ARGS__ )
#endif

#define LOG_DEBUG(str, ...)      stringify::Logger::UTILS->debug( str, ## __VA_ARGS__ )
#define LOG_INFO(str, ...)       stringify::Logger::UTILS->info(  str, ## __VA_ARGS__ )
#define LOG_WARN(str, ...)       stringify::Logger::UTILS->warn(  str, ## __VA_ARGS__ )
#define LOG_ERR(str, ...)        stringify::Logger::UTILS->error( str, ## __VA_ARGS__ )
// clang-format on

// ─────────────────────────────────────────────────────────────
//                  FUNCTIONS
// ─────────────────────────────────────────────────────────────

static const char* _defaultUri = "Stringify";
static const char** _uri = &_defaultUri;
static quint8 _major = 1;
static quint8 _minor = 0;

static void Stringify_registerTypes()
{
    LOG_DEV_INFO("Register Stringify v{}", stringify::Version::version().readable().toStdString());

    LOG_DEV_INFO("Register Singleton {}.Version {}.{} to QML", *_uri, _major, _minor);
    stringify::Version::registerSingleton(*_uri, _major, _minor);
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
    LOG_DEV_INFO("Load Stringify.qrc v{}", stringify::Version::version().readable().toStdString());
    Q_INIT_RESOURCE(Stringify);
}

#ifndef STRINGIFY_STATIC
Q_COREAPP_STARTUP_FUNCTION(Stringify_registerTypes);
Q_COREAPP_STARTUP_FUNCTION(Stringify_loadResources);
#endif

using namespace stringify;

void stringify::registerQmlTypes(const char* uri, const quint8 major, const quint8 minor)
{
    ::Stringify_registerTypes(uri, major, minor);
}

void stringify::loadQmlResources() { ::Stringify_loadResources(); }
