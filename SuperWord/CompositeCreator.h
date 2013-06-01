#pragma once

#include "composite.h"
#include "Command.h"
#include "Condition.h"

#include <string>

namespace comp
{

// Singleton
class CompositeCreator  
{
public:
    virtual ~CompositeCreator();
    static CompositeCreator * Instance();

    Composite * CreateComposite(const std::string& name);

    static cond::Condition * GetFilter();
    static cmd::Command * GetGlobalCommand();
    static cmd::Command * GetPerWordCommand();

private:
    CompositeCreator();
    CompositeArray m_arrComp;
};

}