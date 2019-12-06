#ifndef __STRINGIFY_UTILS_HPP__
#define __STRINGIFY_UTILS_HPP__

// ─────────────────────────────────────────────────────────────
//                  INCLUDE
// ─────────────────────────────────────────────────────────────

// C Header

// C++ Header

// Qt Header

// Dependencies Header

// Application Header
#include <Stringify/Export.hpp>

// ─────────────────────────────────────────────────────────────
//                  DECLARATION
// ─────────────────────────────────────────────────────────────

STRINGIFY_NAMESPACE_START

// ─────────────────────────────────────────────────────────────
//                  CLASS
// ─────────────────────────────────────────────────────────────

/**
 */
class STRINGIFY_API_ Utils
{
public:
    /**
     * Register type to the qml engines
     * Registered types are:
     * -
     */
    static void registerTypes(const char* uri = nullptr, const quint8 major = 1, const quint8 minor = 0);

    static void loadResources();
};

STRINGIFY_NAMESPACE_END // __STRINGIFY_UTILS_HPP__

#endif
