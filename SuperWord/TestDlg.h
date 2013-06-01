#if !defined(AFX_TESTDLG_H__1AA83139_6700_409E_B95D_E8266AED8640__INCLUDED_)
#define AFX_TESTDLG_H__1AA83139_6700_409E_B95D_E8266AED8640__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TestDlg.h : header file
//
#include "CompositeTreeCtrl.h"
#include "RootComposite.h"
#include "ScrollableStyle.h"
#include "afxcmn.h"

using namespace decorate;
/////////////////////////////////////////////////////////////////////////////
// CTestDlg dialog

class CTestDlg : public CDialog
{
// Construction
public:
	CTestDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTestDlg)
	enum { IDD = IDD_TEST_DLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTestDlg)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	CCompositeTreeCtrl m_tree;
    comp::RootComposite * m_pComp;
	virtual BOOL OnInitDialog();
    afx_msg void OnClose();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTDLG_H__1AA83139_6700_409E_B95D_E8266AED8640__INCLUDED_)
