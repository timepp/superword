#include "Composite.h"
#include "CompositeCreator.h"
#include "LibSrc/greta/regexpr2.h"

#include <algorithm>

using namespace comp;
using namespace std;

// Component -------------------------------------------------------------------
// -----------------------------------------------------------------------------

Component::Component()
{
}
Component::~Component()
{
    ClearAll();
}

bool Component::HaveRoom() const
{
    return true;
}

bool Component::CheckValid() const
{
	return (m_arrComp.size() > 0);
}

bool Component::AddChild(Composite *pChild)
{
    if (HaveRoom() && CanAddChild(pChild))
    {
        m_arrComp.push_back(pChild);
        return true;
    }

    return false;
}

bool Component::DelChild(Composite *pChild)
{
    CompositeArray::iterator ci;
    ci = std::find(m_arrComp.begin(), m_arrComp.end(), pChild);
    if (ci != m_arrComp.end())
    {
        delete *ci;
        m_currIter = m_arrComp.erase(ci);
        return true;
    }

    return false;
}

bool Component::ChgChild(Composite *pOldChild, Composite *pNewChild)
{
    CompositeArray::iterator ci;
    ci = std::find(m_arrComp.begin(), m_arrComp.end(), pOldChild);
    if (ci != m_arrComp.end())
    {
        m_currIter = m_arrComp.insert(ci, pNewChild);
        ci = std::find(m_arrComp.begin(), m_arrComp.end(), pOldChild);
        delete *ci;
        m_arrComp.erase(ci);
        return true;
    }

    return false;
}

bool Component::ClearAll()
{
    CompositeArray::iterator ci;
    for (ci = m_arrComp.begin(); ci != m_arrComp.end(); ++ci)
    {
        delete *ci;
    }
    m_arrComp.clear();
    return true;
}

void Component::BeginEnumChild()
{
    m_currIter = m_arrComp.begin();
}

Composite * Component::GetNextChild()
{
    if (m_currIter == m_arrComp.end())
    {
        return NULL;
    }
    else
    {
        return *m_currIter++;
    }
}

Composite * Component::Clone() const
{
    Composite * pComp = CreateObject();

    pComp->Configure(GetConfiguration());
    CompositeArray::const_iterator ci;
    for (ci = m_arrComp.begin(); ci != m_arrComp.end(); ++ci)
    {
        pComp->AddChild((*ci)->Clone());
    }

    return pComp;
}

bool Component::Read(std::istream & is)
{
    static regex::rpattern blank_line("^\\s*$");
    static regex::rpattern comp_end("^\\s*--\\s*$");
    static regex::rpattern comp_name("^\\s*([^\\s]+) ?(.*)$");
    regex::match_results ret;
    char line_buf[1024] = "";

    ClearAll();
    
	string line;
    while (is.good())
    {
        is.getline(line_buf, sizeof(line_buf));
		line = line_buf;
        if (blank_line.match(line, ret).matched) continue;
        if (comp_end.match(line, ret).matched)   break;

        comp_name.match(line, ret);
        Composite * pComp = CompositeCreator::Instance()->CreateComposite(ret.backref(1).str());
        if (pComp != NULL)
        {
            pComp->Configure(ret.backref(2).str());
            pComp->Read(is);
            if (CanAddChild(pComp))
            {
                m_arrComp.push_back(pComp);
            }
            else
            {
                delete pComp;
            }
        }
		else
		{
			break;
		}
    }

    return true;
}

bool Component::Save(std::ostream & os, int indent /* = 0 */) const
{
    string indent_str(indent, ' ');
    os << indent_str << GetName() << " " << GetConfiguration();

    CompositeArray::const_iterator ci;
    for (ci = m_arrComp.begin(); ci != m_arrComp.end(); ++ci)
    {
        os << "\n";
        (*ci)->Save(os, indent + 1);
    }
    os << "\n";

    os << indent_str << "--";

    return true;
}

bool Component::Configure(const std::string& )
{
    return true;
}
string Component::GetConfiguration() const
{
    return "";
}


// Leaf ------------------------------------------------------------------------
// -----------------------------------------------------------------------------

Leaf::Leaf()
{
}
Leaf::~Leaf()
{
}

bool Leaf::CanAddChild(const Composite *) const
{
    return false;
}

bool Leaf::HaveRoom() const
{
    return false;
}
bool Leaf::AddChild(Composite *)
{
    return false;
}
bool Leaf::DelChild(Composite *)
{
    return false;
}
bool Leaf::ChgChild(Composite *, Composite *)
{
    return false;
}
bool Leaf::ClearAll()
{
    return true;
}
void Leaf::BeginEnumChild()
{
}
Composite * Leaf::GetNextChild()
{
    return NULL;
}

Composite * Leaf::Clone() const
{
    Leaf * pLeaf = CreateObject();
    pLeaf->Configure(GetConfiguration());
    return pLeaf;
}

bool Leaf::Read(std::istream & )
{
/*
    static regex::rpattern blank_line("^\\s*$");
    static regex::rpattern match_pat("^\\s*(.*)\\s*$");
    regex::match_results ret;

    char line[1024] = "";
    while (is.good())
    {
        is.getline(line, sizeof(line));
        if (!blank_line.match(line, ret).matched)
        {
            match_pat.match(line, ret);
            Configure(ret.backref(1).str());
            return true;
        }
    }
*/
    return false;
}

bool Leaf::Save(std::ostream & os, int indent /* = 0 */) const
{
    os << string(indent, ' ');
    os << GetName() << " " << GetConfiguration();
    return true;
}