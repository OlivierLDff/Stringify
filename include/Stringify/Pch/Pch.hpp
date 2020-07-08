#ifndef __NETREP_PCH_HPP__
#define __NETREP_PCH_HPP__

// ─────────────────────────────────────────────────────────────
//                  INCLUDE
// ─────────────────────────────────────────────────────────────

// stl
#include <string>
#include <cstdint>
#include <memory>
#include <set>
#include <regex>
#include <sstream>

// spdlog
#include <spdlog/logger.h>
#include <spdlog/sinks/sink.h>

// qt
#include <QtGlobal>
#include <QString>
#include <QQmlEngine>
#include <QCoreApplication>
#include <QRegularExpression>

#ifdef major
#undef major
#endif
#ifdef minor
#undef minor
#endif

#endif
