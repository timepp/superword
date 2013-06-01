#if !defined(AFX_FSCLASSDLG_H__523EB1C2_4D50_4CDD_9175_B1EABB0C7FB0__INCLUDED_)
#define AFX_FSCLASSDLG_H__523EB1C2_4D50_4CDD_9175_B1EABB0C7FB0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CSClassDlg.h : header file
//
#include "CSRootDlg.h"

namespace compdlg
{
/////////////////////////////////////////////////////////////////////////////
// CCSClassDlg dialog

class CCSClassDlg : public CCSRootDlg
{
// Construction
public:
	CCSClassDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCSClassDlg)
	enum { IDD = IDD_CS_CLASS_DLG };
	CString	m_strWordClass;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCSClassDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCSClassDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSelectWordClass();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
    virtual void OnOK();
};

};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FSCLASSDLG_H__523EB1C2_4D50_4CDD_9175_B1EABB0C7FB0__INCLUDED_)
