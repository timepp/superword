#if !defined(AFX_RSCOLORPAGE_H__36A4F373_30D2_47D4_883D_744F9FBC2874__INCLUDED_)
#define AFX_RSCOLORPAGE_H__36A4F373_30D2_47D4_883D_744F9FBC2874__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSColorPage.h : header file
//

#include "ColorPage.h"
/////////////////////////////////////////////////////////////////////////////
// CRSColorPage dialog

class CRSColorPage : public CPropertyPage
{
// Construction
public:
	CRSColorPage();   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRSColorPage)
	enum { IDD = IDD_RS_COLOR_PAGE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSColorPage)
	public:
	virtual BOOL OnApply();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	
	CColorPage m_cp;
	// Generated message map functions
	//{{AFX_MSG(CRSColorPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnLoadColorscheme();
	afx_msg void OnBtnSaveColorscheme();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RSCOLORPAGE_H__36A4F373_30D2_47D4_883D_744F9FBC2874__INCLUDED_)
