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

#endif
