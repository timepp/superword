#if !defined(AFX_FSPHONETICDLG_H__F7D4EA24_6CB4_45A6_944B_F1DDAE3B38EF__INCLUDED_)
#define AFX_FSPHONETICDLG_H__F7D4EA24_6CB4_45A6_944B_F1DDAE3B38EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CSPhoneticDlg.h : header file
//

#include "CSRootDlg.h"

namespace compdlg
{

/////////////////////////////////////////////////////////////////////////////
// CCSPhoneticDlg dialog

class CCSPhoneticDlg : public CCSRootDlg
{
// Construction
public:
	CCSPhoneticDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCSPhoneticDlg)
	enum { IDD = IDD_CS_PHONETIC_DLG };
	CRichEditCtrl	m_rdMatcher;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCSPhoneticDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	static char m_szControl[];
	static char m_szPhonetic[][16];
	static char m_szAll[];

	COLORREF m_crBorder;
	COLORREF m_crBack;
	COLORREF m_crPhonetic;

	CHARFORMAT m_cfControl;
	CHARFORMAT m_cfPhonetic;

	CString m_strPhoneticFontName;

    CSize m_szCell;
    CRect m_rcPhonetic;

	void DrawSelectCell(const CRect& rc, char ch, LPCTSTR pszFont, int nCharSet, int nPitchAndFamily,
		COLORREF crBack, COLORREF crChar, COLORREF crBorder);
	BOOL GetFocusRectChar(CPoint pt, CRect *pRect, char *pChar);
	void DrawColorBorder(CRect rc, COLORREF cr);
	void InsertMatcher(char ch);

	// Generated message map functions
	//{{AFX_MSG(CCSPhoneticDlg)
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeRicheditMatcher();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FSPHONETICDLG_H__F7D4EA24_6CB4_45A6_944B_F1DDAE3B38EF__INCLUDED_)
