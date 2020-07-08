#ifndef __NETREP_PCH_HPP__
#define __NETREP_PCH_HPP__

// ─────────────────────────────────────────────────────────────
//                  INCLUDE
// ─────────────────────────────────────────────────────────────

// Types
#include <cstdint>
#include <cstddef>
#include <string>

// Containers
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <vector>
#include <list>
#include <stack>
#include <queue>

// Utilities
#include <chrono>
#include <initializer_list>
#include <utility>

// spdlog
#include <spdlog/logger.h>
#include <spdlog/sinks/sink.h>

// flatbuffers
#include <flatbuffers/flatbuffers.h>

// eventpp
#include <eventpp/callbacklist.h>

// Unique
#include <Unique/Unique.hpp>

// Qt Headers
#include <QAbstractListModel>
#include <QObject>
#include <QByteArray>
#include <QHash>
#include <QList>
#include <QMetaObject>
#include <QMetaProperty>
#include <QString>
#include <QVariant>
#include <QDebug>
#include <QQmlEngine>
#include <QJSValue>

#ifdef major
#undef major
#endif
#ifdef minor
#undef minor
#endif

#endif
