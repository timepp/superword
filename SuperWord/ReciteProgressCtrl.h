#if !defined(AFX_RECITEPROGRESSCTRL_H__35026532_E344_412B_B82E_28C17D807B60__INCLUDED_)
#define AFX_RECITEPROGRESSCTRL_H__35026532_E344_412B_B82E_28C17D807B60__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ReciteProgressCtrl.h : header file
//
#include "LibSrc/GradientProgress/GradientProgressCtrl.h"
/////////////////////////////////////////////////////////////////////////////
// CReciteProgressCtrl window

class CReciteProgressCtrl : public CGradientProgressCtrl
{
// Construction
public:
	CReciteProgressCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReciteProgressCtrl)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CReciteProgressCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CReciteProgressCtrl)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg BOOL OnNcCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RECITEPROGRESSCTRL_H__35026532_E344_412B_B82E_28C17D807B60__INCLUDED_)
