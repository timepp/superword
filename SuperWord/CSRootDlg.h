#if !defined(AFX_FILTERSETDLG_H__F95BA2FA_EB2A_464C_B01F_5B15CD5C5E72__INCLUDED_)
#define AFX_FILTERSETDLG_H__F95BA2FA_EB2A_464C_B01F_5B15CD5C5E72__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CSRootDlg.h : header file
//

#include "word.h"
#include "Composite.h"
#include "PopupHelpStyle.h"

namespace compdlg
{
/////////////////////////////////////////////////////////////////////////////
// CCSRootDlg dialog
using word::Word;
using namespace decorate;

class CCSRootDlg : public CDialog, public CPopupHelpStyle
{
// Construction
public:
	CCSRootDlg(UINT nIDTemplate, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCSRootDlg)
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

    comp::Composite * m_pComp;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCSRootDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCSRootDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILTERSETDLG_H__F95BA2FA_EB2A_464C_B01F_5B15CD5C5E72__INCLUDED_)
