// DetailMeaning.h: interface for the CDetailMeaning class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DETAILMEANING_H__EAFCAC16_08CC_4C4E_B80D_89AA486A6DCD__INCLUDED_)
#define AFX_DETAILMEANING_H__EAFCAC16_08CC_4C4E_B80D_89AA486A6DCD__INCLUDED_

#include "stdafx.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDetailMeaning  
{
public:
	CDetailMeaning();
	virtual ~CDetailMeaning();
	CString GetDetailedMeaningFromFile(const CString& strWord);
	CString GetDetailedMeaning(const CString& strWord);
private:
	CFile m_fMeaning;
};

#endif // !defined(AFX_DETAILMEANING_H__EAFCAC16_08CC_4C4E_B80D_89AA486A6DCD__INCLUDED_)
