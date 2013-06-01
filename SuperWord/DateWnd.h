#if !defined(AFX_DATEWND_H__2240FD95_5A10_449D_8487_0004B6F1F742__INCLUDED_)
#define AFX_DATEWND_H__2240FD95_5A10_449D_8487_0004B6F1F742__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DateWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDateWnd window

class CDateWnd : public CStatic
{
// Construction
public:
	CDateWnd();

// Attributes
protected:
	CTime m_Time;
	COLORREF m_crBack, m_crText;
	CFont m_Font;
	CRect m_rc;

// Operations
public:
	void SetTime(time_t t);
	void SetColor(COLORREF crBk, COLORREF crText);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDateWnd)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDateWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDateWnd)
	afx_msg void OnPaint();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATEWND_H__2240FD95_5A10_449D_8487_0004B6F1F742__INCLUDED_)
