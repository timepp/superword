#if !defined(AFX_PRACTISERESULTDLG_H__E3B97619_BF61_4E51_A842_D03BC736D731__INCLUDED_)
#define AFX_PRACTISERESULTDLG_H__E3B97619_BF61_4E51_A842_D03BC736D731__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PractiseResultDlg.h : header file
//

#include "Resource.h"

#define SPR_RIGHT	1
#define SPR_WRONG	0
/////////////////////////////////////////////////////////////////////////////
// CPractiseResultDlg dialog

class CPractiseResultDlg : public CDialog
{
// Construction
public:
	CPractiseResultDlg(CWnd* pParent = NULL);   // standard constructor
	~CPractiseResultDlg();
	
	BOOL ShowWindow(int nCmdShow);
	BOOL ShowPractiseResult(CPoint ptBottomRight, int nType);

// Dialog Data
	//{{AFX_DATA(CPractiseResultDlg)
	enum { IDD = IDD_PRACTISE_RESULT_DLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPractiseResultDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// 提示用户的练习是否正确的位图
	HBITMAP m_hBmpRight;
	HBITMAP m_hBmpWrong;
	HRGN m_hRgn;
	BOOL m_bCapturing;

	BITMAP m_bmRight;
	BITMAP m_bmWrong;

	CPoint m_ptBottomRight;
	int m_nShowType;

	BOOL LoadBitmapsFromFile();

	HRGN BitmapToRegion(HBITMAP hBmp, COLORREF cTransparentColor = 0, COLORREF cTolerance = 0x101010);

	// Generated message map functions
	//{{AFX_MSG(CPractiseResultDlg)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnTimer(UINT nIDEvent);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRACTISERESULTDLG_H__E3B97619_BF61_4E51_A842_D03BC736D731__INCLUDED_)
