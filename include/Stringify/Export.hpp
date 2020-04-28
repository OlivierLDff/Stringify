#ifndef __STRINGIFY_EXPORT_HPP__
#define __STRINGIFY_EXPORT_HPP__

#ifdef WIN32
#    ifdef STRINGIFY_DLL_EXPORT
#        define STRINGIFY_API_ __declspec(dllexport)
#    elif STRINGIFY_STATIC
#        define STRINGIFY_API_
#    else
#        define STRINGIFY_API_ __declspec(dllimport)
#    endif
#else
#    define STRINGIFY_API_
#endif

#endif
