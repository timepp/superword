// WordType.cpp: implementation of the WordType class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SuperWord.h"
#include "WordType.h"

#include <algorithm>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


const int WordType::MaxWordTypeCount = 16;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

WordType::WordType()
{
}

WordType::~WordType()
{
	WriteTypes();
}

WordType * WordType::Instance()
{
	static WordType wt;
	if (wt.m_vTypes.size() == 0)
	{
		wt.ReadTypes();
	}
	return &wt;
}

BOOL WordType::SetType(size_t index, const std::string& tp)
{
	if (index < m_vTypes.size())
	{
		m_vTypes[index] = tp;
		return TRUE;
	}

	return FALSE;
}

const std::string WordType::Type(size_t index) const
{
	if (index < m_vTypes.size())
	{
		return m_vTypes[index];
	}

	return "";
}

size_t WordType::GetTypeIndex(const std::string& tp)
{
	std::vector<std::string>::const_iterator ci;
	ci = std::find(m_vTypes.begin(), m_vTypes.end(), tp);
	return (ci == m_vTypes.end()) ? -1 : (ci - m_vTypes.begin());
}

const StringVector& WordType::GetAllType() const
{
	return m_vTypes;
}

void WordType::ReadTypes()
{
	regex::rpattern type("^\\s*([^\\s]+)\\s*$");
	regex::match_results match;
	char buf[MAX_LINE];
	
	std::ifstream is(helper::SWPath(helper::IDS(IDSFN_WORD_TYPE)));
	if (!is) return;

	m_vTypes.clear();
	while (is.good() && m_vTypes.size() < 16)
	{
		is.getline(buf, MAX_LINE);
		if (type.match(std::string(buf), match).matched)
		{
			m_vTypes.push_back(buf);
		}
	}
}

void WordType::WriteTypes() const
{
	std::ofstream os(helper::SWPath(helper::IDS(IDSFN_WORD_TYPE)));
	if (!os) return;

	StringVector::const_iterator ci;
	for (ci = m_vTypes.begin(); ci != m_vTypes.end(); ++ci)
	{
		os << *ci << "\n";
	}
}