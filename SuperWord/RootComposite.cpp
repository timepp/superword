#include "rootcomposite.h"
#include "Command.h"
#include "Condition.h"

using namespace comp;
using namespace comp::cond;
using namespace comp::cmd;


RootComposite::RootComposite(CompType tp, size_t capacity /* = (size_t)-1 */)
{
    m_tp = tp;
    m_capacity = capacity;
}

RootComposite::~RootComposite(void)
{
}

bool RootComposite::CanAddChild(const Composite * pChild) const
{
    switch (m_tp)
    {
    case condition:
        return (dynamic_cast<const Condition *>(pChild) != NULL);
        break;
    case command:
        return (dynamic_cast<const Command *>(pChild) != NULL);
        break;
    default:
        break;
    }

    return true;
}

bool RootComposite::HaveRoom() const
{
    return (m_capacity > m_arrComp.size());
}

bool RootComposite::Save(std::ostream & os, int indent /* = 0 */) const
{
    CompositeArray::const_iterator ci = m_arrComp.begin();
    if (ci == m_arrComp.end())
    {
        return true;
    }

    (*ci)->Save(os, indent);
    for (++ci; ci != m_arrComp.end(); ++ci)
    {
        os << "\n";
        (*ci)->Save(os, indent);
    }

    return true;
}

std::string RootComposite::GetName() const
{
    return "根复合结点";
}
std::string RootComposite::GetDescription() const
{
    return GetName();
}

Component * RootComposite::CreateObject() const
{
    return new RootComposite(unknown);
}