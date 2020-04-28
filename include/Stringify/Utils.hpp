#ifndef __STRINGIFY_UTILS_HPP__
#define __STRINGIFY_UTILS_HPP__

// ─────────────────────────────────────────────────────────────
//                  INCLUDE
// ─────────────────────────────────────────────────────────────

// Application Headers
#include <Stringify/Export.hpp>

// Qt Headers
#include <QtGlobal>

// ─────────────────────────────────────────────────────────────
//                  DECLARATION
// ─────────────────────────────────────────────────────────────

namespace stringify {

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
    static void registerTypes(
        const char* uri = nullptr, const quint8 major = 1, const quint8 minor = 0);

    static void loadResources();
};

}

#endif
