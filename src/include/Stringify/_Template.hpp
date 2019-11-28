#ifndef __STRINGIFY_TEMPLATE_HPP__
#define __STRINGIFY_TEMPLATE_HPP__

// ─────────────────────────────────────────────────────────────
//                  INCLUDE
// ─────────────────────────────────────────────────────────────

// C Header

// C++ Header

// Qt Header
#include <QObject>

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


STRINGIFY_NAMESPACE_END

#endif // __STRINGIFY_TEMPLATE_HPP__
