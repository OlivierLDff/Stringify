#ifndef __STRINGIFY_TEMPLATE_HPP__
#define __STRINGIFY_TEMPLATE_HPP__

// ─────────────────────────────────────────────────────────────
//                  INCLUDE
// ─────────────────────────────────────────────────────────────

// Application Headers
#include <Stringify/Export.hpp>

// Dependencies Headers

// Qt Headers
#include <QObject>

// C++ Headers

// ─────────────────────────────────────────────────────────────
//                  DECLARATION
// ─────────────────────────────────────────────────────────────

namespace stringify {

// ─────────────────────────────────────────────────────────────
//                  CLASS
// ─────────────────────────────────────────────────────────────

/**
 */
class STRINGIFY_API_ ITemplate
{
public:
    virtual ~Template() = default;
};

/**
 */
class STRINGIFY_API_ BaseTemplate: public QObject, public ITemplate
{
    Q_OBJECT

public:
    BaseTemplate(QObject* parent = nullptr);
    virtual ~BaseTemplate() = default;
};

/**
 */
class STRINGIFY_API_ Template: public BaseTemplate
{
    Q_OBJECT

public:
    Template(QObject* parent = nullptr);
    virtual ~Template() = default;
};


}

#endif // __STRINGIFY_TEMPLATE_HPP__
