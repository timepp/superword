#if !defined(AFX_RGNDLG_H__31EA9952_9F27_444C_AF62_1275879F873C__INCLUDED_)
#define AFX_RGNDLG_H__31EA9952_9F27_444C_AF62_1275879F873C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RgnDlg.h : header file
//
#include "Resource.h"
/////////////////////////////////////////////////////////////////////////////
// CRgnDlg dialog

class CRgnDlg : public CDialog
{
// Construction
public:
	CRgnDlg(CWnd* pParent = NULL);   // standard constructor

	void SetFontRegion(LPCTSTR pszText, const LOGFONT *pLf);
	void SetDlgColor(COLORREF cr);

// Dialog Data
	//{{AFX_DATA(CRgnDlg)
	enum { IDD = IDD_RGN_DLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRgnDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	
// Implementation
protected:
	COLORREF m_bkColor;
	// Generated message map functions
	//{{AFX_MSG(CRgnDlg)
	virtual BOOL OnInitDialog();
//	afx_msg UINT OnNcHitTest(CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg LRESULT OnNcHitTest(CPoint point);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RGNDLG_H__31EA9952_9F27_444C_AF62_1275879F873C__INCLUDED_)
