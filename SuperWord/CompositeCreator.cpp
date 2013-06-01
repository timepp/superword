#include "stdafx.h"

#include "resource.h"
#include "CompositeCreator.h"
#include "ConcreteCondition.h"
#include "ConcreteCommand.h"
#include "RootComposite.h"
#include "helper.h"

#include <fstream>

using namespace comp;
using namespace std;

CompositeCreator::CompositeCreator()
{
	// TODO: New Concrete Subclass of Composite must be registered here
	m_arrComp.push_back(new cond::AndCondition());
	m_arrComp.push_back(new cond::OrCondition());
	m_arrComp.push_back(new cond::NotCondition());
	m_arrComp.push_back(new cond::WordCondition());
	m_arrComp.push_back(new cond::MeaningCondition());
	m_arrComp.push_back(new cond::PhoneticCondition());
	m_arrComp.push_back(new cond::AccesstimeCondition());
	m_arrComp.push_back(new cond::ClassCondition());
	m_arrComp.push_back(new cond::TypeCondition());
	m_arrComp.push_back(new cond::MiscCondition());

	m_arrComp.push_back(new cmd::SeriesCommand);
	m_arrComp.push_back(new cmd::RandomCommand);
	m_arrComp.push_back(new cmd::IfCommand);
	m_arrComp.push_back(new cmd::TimerCommand);
	m_arrComp.push_back(new cmd::HotkeyCommand);
	m_arrComp.push_back(new cmd::MoveWordCommand);
	m_arrComp.push_back(new cmd::SetColorCommand);
	m_arrComp.push_back(new cmd::OpenDlgCommand);
	m_arrComp.push_back(new cmd::ShowElementCommand);
	m_arrComp.push_back(new cmd::SetWordTypeCommand);
	m_arrComp.push_back(new cmd::MiscCommand);
	m_arrComp.push_back(new cmd::LoadCompCommand);
}

CompositeCreator::~CompositeCreator()
{
	CompositeArray::const_iterator ci;
	for (ci = m_arrComp.begin(); ci != m_arrComp.end(); ++ci)
	{
		delete *ci;
	}
	m_arrComp.clear();
}

CompositeCreator * CompositeCreator::Instance()
{
	static CompositeCreator cp;
	return &cp;
}

Composite * CompositeCreator::CreateComposite(const std::string& name)
{
	CompositeArray::const_iterator ci;
	for (ci = m_arrComp.begin(); ci != m_arrComp.end(); ++ci)
	{
		if ((*ci)->GetName() == name)
		{
			return (*ci)->Clone();
		}
	}

	return NULL;
}

cond::Condition * CompositeCreator::GetFilter()
{
	static RootComposite comp(condition);

	ifstream ifs(helper::SWPath(helper::IDS(IDSFN_WORD_FILTER)));
	comp.Read(ifs);

	comp.BeginEnumChild();
	return dynamic_cast<cond::Condition *>(comp.GetNextChild()); 
}

cmd::Command * CompositeCreator::GetGlobalCommand()
{
	static RootComposite comp(command);

	ifstream ifs(helper::SWPath(helper::IDS(IDSFN_GLOBAL_CMD)));
	comp.Read(ifs);

	comp.BeginEnumChild();
	return dynamic_cast<cmd::Command *>(comp.GetNextChild()); 
}

cmd::Command * CompositeCreator::GetPerWordCommand()
{
	static RootComposite comp(command);

	ifstream ifs(helper::SWPath(helper::IDS(IDSFN_WORD_CMD)));
	comp.Read(ifs);

	comp.BeginEnumChild();
	return dynamic_cast<cmd::Command *>(comp.GetNextChild()); 
}
