#if !defined(AFX_WORDTYPEWND_H__CB6C54C1_56A1_4504_A662_10DE738C01CC__INCLUDED_)
#define AFX_WORDTYPEWND_H__CB6C54C1_56A1_4504_A662_10DE738C01CC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WordTypeWnd.h : header file
//

#include "PopupDlg.h"

#define WM_TOGGLE_WORD_TYPE WM_USER + 0x111
/////////////////////////////////////////////////////////////////////////////
// CWordTypeWnd window

class CWordTypeWnd : public CButton
{
// Construction
public:
	CWordTypeWnd();

// Attributes
public:

// Operations
public:
	void SetColors(COLORREF crBorder, COLORREF crActive, COLORREF crInActive = 0xFF000000);
	void SetWordType(WORD wWordType);
	void SetCxCount(int cxCount);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWordTypeWnd)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWordTypeWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CWordTypeWnd)
	afx_msg void OnPaint();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	afx_msg LRESULT OnMouseLeave(WPARAM wp, LPARAM lp);
	
	void UpdateTip(CPoint pt);
	void DrawCell(WORD wMask = 0xffff);
	COLORREF DarkColor(COLORREF cr);

	CPopupDlg * m_pTipDlg;

	COLORREF m_crActive, m_crInActive, m_crBorder;
	WORD m_wWordType;
	int m_cxCount;
	CRect m_Cells[16];
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WORDTYPEWND_H__CB6C54C1_56A1_4504_A662_10DE738C01CC__INCLUDED_)
