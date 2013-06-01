#pragma once

#include "Composite.h"

namespace comp
{

// RootComposite is a class which acts as the corresponding composite of a root
// node of a tree control.
// When save, This class will not save its informations into stream. Instead,
// it only saves all its child.

class RootComposite : public Component
{
public:
    RootComposite(CompType tp, size_t capacity = (size_t)-1);
    virtual ~RootComposite(void);
    virtual bool HaveRoom() const;
    virtual bool CanAddChild(const Composite * pChild) const;
    virtual bool Save(std::ostream & os, int indent = 0) const;
    virtual std::string GetName() const;
    virtual std::string GetDescription() const;
private:
    virtual Component * CreateObject() const;

    CompType m_tp;
    size_t   m_capacity;
};

}