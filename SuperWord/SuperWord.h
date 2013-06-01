// SuperWord.h : main header file for the SuperWord application
//

#if !defined(AFX_SuperWord_H__335E0784_59AA_4F98_85C3_380AB4AC8B41__INCLUDED_)
#define AFX_SuperWord_H__335E0784_59AA_4F98_85C3_380AB4AC8B41__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "Helper.h"
#include "GlobalSetting.h"

/////////////////////////////////////////////////////////////////////////////
// CSuperWordApp:
// See SuperWord.cpp for the implementation of this class
//

class CSuperWordApp : public CWinApp
{
public:
	CSuperWordApp();
	~CSuperWordApp();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSuperWordApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL
	
private:	
	void PrepareEnv();
	void ReCreateFileIfMissing(LPCTSTR pszPath, UINT idResource, LPSTR lpType);

// Implementation

	//{{AFX_MSG(CSuperWordApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SuperWord_H__335E0784_59AA_4F98_85C3_380AB4AC8B41__INCLUDED_)
