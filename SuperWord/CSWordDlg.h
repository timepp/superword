#if !defined(AFX_FSWORDDLG_H__C133C637_D0C0_460D_8650_D251DE80A48A__INCLUDED_)
#define AFX_FSWORDDLG_H__C133C637_D0C0_460D_8650_D251DE80A48A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CSWordDlg.h : header file
//
#include "CSRootDlg.h"
/////////////////////////////////////////////////////////////////////////////
// CCSWordDlg dialog
namespace compdlg
{

	class CCSWordDlg : public CCSRootDlg
	{
		// Construction
	public:
		CCSWordDlg(CWnd* pParent = NULL);   // standard constructor

		// Dialog Data
		//{{AFX_DATA(CCSWordDlg)
		enum { IDD = IDD_CS_WORD_DLG };
		CString	m_strMatcher;
		//}}AFX_DATA

		// Overrides
		// ClassWizard generated virtual function overrides
		//{{AFX_VIRTUAL(CCSWordDlg)
	protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
		//}}AFX_VIRTUAL

		// Implementation
	protected:
		// Generated message map functions
		//{{AFX_MSG(CCSWordDlg)
		// NOTE: the ClassWizard will add member functions here
		//}}AFX_MSG
		DECLARE_MESSAGE_MAP()
	};

};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FSWORDDLG_H__C133C637_D0C0_460D_8650_D251DE80A48A__INCLUDED_)
