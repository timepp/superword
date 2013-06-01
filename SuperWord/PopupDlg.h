#if !defined(AFX_POPUPDLG_H__2C19B789_6930_488A_8478_CBFDF86CC565__INCLUDED_)
#define AFX_POPUPDLG_H__2C19B789_6930_488A_8478_CBFDF86CC565__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PopupDlg.h : header file
//
#include "Resource.h"
/////////////////////////////////////////////////////////////////////////////
// CPopupDlg dialog

class CPopupDlg : public CDialog
{
// Construction
public:
	CPopupDlg(CWnd* pParent = NULL);   // standard constructor
	void Update(CPoint pt, const CString& str);

	CString m_strText;
// Dialog Data
	//{{AFX_DATA(CPopupDlg)
	enum { IDD = IDD_POPUP_DLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPopupDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPopupDlg)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_POPUPDLG_H__2C19B789_6930_488A_8478_CBFDF86CC565__INCLUDED_)
