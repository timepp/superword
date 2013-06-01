// SWAddWord.h : main header file for the SWADDWORD application
//

#if !defined(AFX_SWADDWORD_H__A4D03342_F72F_4FBA_9184_1DF09398EC2B__INCLUDED_)
#define AFX_SWADDWORD_H__A4D03342_F72F_4FBA_9184_1DF09398EC2B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSWAddWordApp:
// See SWAddWord.cpp for the implementation of this class
//

class CSWAddWordApp : public CWinApp
{
public:
	CSWAddWordApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSWAddWordApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSWAddWordApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SWADDWORD_H__A4D03342_F72F_4FBA_9184_1DF09398EC2B__INCLUDED_)
