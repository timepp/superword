// DateWnd.cpp : implementation file
//

#include "stdafx.h"
#include "superword.h"
#include "DateWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDateWnd

CDateWnd::CDateWnd()
{
	m_rc.SetRect(0, 0, 0, 0);
	m_Font.CreateFont(18,0, 0,0,400, 0,0,0, 0, 3,2,1, 34,"Verdana");
}

CDateWnd::~CDateWnd()
{
}


BEGIN_MESSAGE_MAP(CDateWnd, CStatic)
	//{{AFX_MSG_MAP(CDateWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDateWnd message handlers

void CDateWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	CString str;
	if (m_Time != CTime(0))
		str = m_Time.Format("%y-%m-%d");
	
	if (m_rc == CRect(0, 0, 0, 0))
	{
		GetClientRect(&m_rc);
	}
	
	CFont * pOldFont = dc.SelectObject(&m_Font);
	dc.FillSolidRect(&m_rc, m_crBack);
	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(m_crText);
	dc.DrawText(str, &m_rc, DT_CENTER);
	dc.SelectObject(pOldFont);
}

void CDateWnd::SetColor(COLORREF crBk, COLORREF crText)
{
	m_crText = crText;
	m_crBack = crBk;
	InvalidateRect(NULL);
}

void CDateWnd::SetTime(time_t t)
{
	if (m_Time != CTime(t))
	{
		m_Time = t;
		InvalidateRect(NULL);
	}
}

void CDateWnd::PreSubclassWindow() 
{
	CRect rc;
	GetClientRect(&rc);
	ModifyStyle(0, SS_NOTIFY);
	
	CStatic::PreSubclassWindow();
}

void CDateWnd::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	GetParent()->SendMessage(WM_COMMAND, ID_TOOGLE_ACCESS_TIME, NULL);
	CStatic::OnLButtonDblClk(nFlags, point);
}
