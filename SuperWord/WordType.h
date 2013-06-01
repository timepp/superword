// WordType.h: interface for the WordType class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WORDTYPE_H__A9DD6FE1_3292_411A_802C_3DEAAEB70CF1__INCLUDED_)
#define AFX_WORDTYPE_H__A9DD6FE1_3292_411A_802C_3DEAAEB70CF1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include <string>
#include <fstream>
#include "LibSrc/greta/regexpr2.h"

typedef std::vector<std::string> StringVector;

class WordType  
{
friend class CWordtypeDlg;
public:
	virtual ~WordType();
	static WordType* Instance();
	static const int MaxWordTypeCount;
	
	BOOL SetType(size_t index, const std::string& tp);
	const std::string Type(size_t index) const;
	size_t GetTypeIndex(const std::string& tp);
	const StringVector& GetAllType() const;
private:
	std::vector<std::string> m_vTypes;

	WordType();
	void ReadTypes();
	void WriteTypes() const;
};

#endif // !defined(AFX_WORDTYPE_H__A9DD6FE1_3292_411A_802C_3DEAAEB70CF1__INCLUDED_)
