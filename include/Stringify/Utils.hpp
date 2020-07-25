#ifndef __STRINGIFY_UTILS_HPP__
#define __STRINGIFY_UTILS_HPP__

// ─────────────────────────────────────────────────────────────
//                  INCLUDE
// ─────────────────────────────────────────────────────────────

// Qt Headers
#include <QtGlobal>

// ─────────────────────────────────────────────────────────────
//                  DECLARATION
// ─────────────────────────────────────────────────────────────

namespace stringify {

// ─────────────────────────────────────────────────────────────
//                  CLASS
// ─────────────────────────────────────────────────────────────

void registerQmlTypes(const char* uri = nullptr, const quint8 major = 1, const quint8 minor = 0);
void loadQmlResources();

}

#endif
