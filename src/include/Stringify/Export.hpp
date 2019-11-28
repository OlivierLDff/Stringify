#ifndef __STRINGIFY_EXPORT_HPP__
#define __STRINGIFY_EXPORT_HPP__

// ─────────────────────────────────────────────────────────────
//                  DECLARATION
// ─────────────────────────────────────────────────────────────

#ifdef WIN32
    #ifdef STRINGIFY_DLL_EXPORT  // Shared build
        #define STRINGIFY_API_ __declspec(dllexport)
    #elif STRINGIFY_STATIC       // No decoration when building staticlly
        #define STRINGIFY_API_
    #else                       // Link to lib
        #define STRINGIFY_API_ __declspec(dllimport)
    #endif
#else
    #define STRINGIFY_API_
#endif // WIN32

#ifdef STRINGIFY_USE_NAMESPACE

    #ifndef STRINGIFY_NAMESPACE
        #define STRINGIFY_NAMESPACE Stringify
    #endif // ifndef STRINGIFY_NAMESPACE

    #define STRINGIFY_NAMESPACE_START namespace STRINGIFY_NAMESPACE {
    #define STRINGIFY_NAMESPACE_END }
    #define STRINGIFY_USING_NAMESPACE using namespace STRINGIFY_NAMESPACE;

#else // STRINGIFY_USE_NAMESPACE

    #undef STRINGIFY_NAMESPACE
    #define STRINGIFY_NAMESPACE
    #define STRINGIFY_NAMESPACE_START
    #define STRINGIFY_NAMESPACE_END
    #define STRINGIFY_USING_NAMESPACE

#endif // STRINGIFY_USE_NAMESPACE

#endif // __STRINGIFY_EXPORT_HPP__
