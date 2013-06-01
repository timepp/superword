#if !defined(AFX_FSMEANINGDLG_H__8CC799C3_D993_4E60_8C50_5F5E30E1BCFC__INCLUDED_)
#define AFX_FSMEANINGDLG_H__8CC799C3_D993_4E60_8C50_5F5E30E1BCFC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CSMeaningDlg.h : header file
//

#include "CSRootDlg.h"

namespace compdlg
{

/////////////////////////////////////////////////////////////////////////////
// CCSMeaningDlg dialog

class CCSMeaningDlg : public CCSRootDlg
{
// Construction
public:
	CCSMeaningDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCSMeaningDlg)
	enum { IDD = IDD_CS_MEANING_DLG };
	CString	m_strMatcher;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCSMeaningDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CCSMeaningDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    BOOL m_bMatchDetail;
};

};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FSMEANINGDLG_H__8CC799C3_D993_4E60_8C50_5F5E30E1BCFC__INCLUDED_)
