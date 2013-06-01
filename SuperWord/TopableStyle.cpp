// TopableStyle.cpp: implementation of the CTopableStyle class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "superword.h"
#include "TopableStyle.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

using namespace decorate;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTopableStyle::CTopableStyle()
{
	m_bCursorOnTopBox = FALSE;
	m_bTopboxLButtonDown = FALSE;
	m_bTopMost = FALSE;
}

CTopableStyle::~CTopableStyle()
{

}

int CTopableStyle::WndProcBeforeOldProc(UINT msg, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(wParam);

	static BOOL bTopboxLastPushlike = 0;

	if (msg == WM_MOUSEMOVE)
	{
		CPoint point(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		m_pWnd->ClientToScreen(&point);
		m_bCursorOnTopBox = GetTopableBoxRect(TRUE).PtInRect(point);
		
		if (bTopboxLastPushlike != TopboxPushLike())
		{
			bTopboxLastPushlike = TopboxPushLike();
			DrawTopableBox();
		}
	}
	else if (msg == WM_LBUTTONUP)
	{
		if (m_bTopboxLButtonDown)
		{
			m_bTopboxLButtonDown = FALSE;
			::ReleaseCapture();
			if (m_bCursorOnTopBox)
			{
				m_bTopMost = !m_bTopMost;
				m_pWnd->SetWindowPos(m_bTopMost ? &CWnd::wndTopMost : &CWnd::wndNoTopMost,
					0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
				DrawTopableBox();
			}
		}
	}
	else if (msg == WM_NCHITTEST)
	{
		CPoint point(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		if (GetTopableBoxRect(TRUE).PtInRect(point))
		{
			return HTSIZE;
		}
	}
	else if (msg == WM_NCLBUTTONDOWN)
	{
		CPoint point(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		m_bCursorOnTopBox = GetTopableBoxRect(TRUE).PtInRect(point);
		if (m_bCursorOnTopBox)
		{
			m_bTopboxLButtonDown = TRUE;
			DrawTopableBox();
			m_pWnd->SetCapture();
		}
	}

	return RETURN_DEFAULT;
}

BOOL CTopableStyle::WndProcAfterOldProc(UINT msg, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);

	if (msg == WM_NCACTIVATE)
	{
		DrawTopableBox();
	}
	else if (msg == WM_NCPAINT)
	{
		DrawTopableBox();
	}

	return RETURN_DEFAULT;
}

BOOL CTopableStyle::OnInitDecorator()
{
	return TRUE;
}

CRect CTopableStyle::GetTopableBoxRect(BOOL bScreenCoordinates)
{
	BOOL bHasCloseBox = FALSE;
	BOOL bHasMinMaxBox = FALSE;

	LONG style = ::GetWindowLong(m_pWnd->m_hWnd, GWL_STYLE);
	if ((style & WS_CAPTION) && (style & WS_SYSMENU))
	{
		bHasCloseBox = TRUE;
		if ((style & WS_MAXIMIZEBOX) || (style & WS_MINIMIZEBOX))
		{
			bHasMinMaxBox = TRUE;
		}
	}

	int xborder = ::GetSystemMetrics(SM_CXBORDER);//SM_CXEDGE
//	int yborder = ::GetSystemMetrics(SM_CYBORDER);//SM_CYEDGE
	int xframe  = ::GetSystemMetrics(SM_CXFIXEDFRAME);//SM_CXEDGE
	int yframe  = ::GetSystemMetrics(SM_CYFIXEDFRAME);//SM_CYEDGE
	int xsize   = ::GetSystemMetrics(SM_CXSIZE);
	int ysize   = ::GetSystemMetrics(SM_CYSIZE);
//	int ycaption= ::GetSystemMetrics(SM_CYCAPTION);

	CRect rcWnd;
	m_pWnd->GetWindowRect(&rcWnd);
	if (!bScreenCoordinates)
		rcWnd.OffsetRect(-rcWnd.left, -rcWnd.top);

	rcWnd.right -= xborder + xframe;
	if (bHasCloseBox)
		rcWnd.right -= xsize + 1;
	if (bHasMinMaxBox)
		rcWnd.right -= xsize * 2;
	rcWnd.top += xborder + xframe + 2;
	rcWnd.left = rcWnd.right - xsize + 2;
	rcWnd.bottom = rcWnd.top + ysize + yframe - 7;

	return rcWnd;
}

void CTopableStyle::DrawTopableBox()
{
	CRect rcBox = GetTopableBoxRect(FALSE);

	CWindowDC dc(m_pWnd);

	if (TopboxPushLike())
	{
		dc.DrawFrameControl(&rcBox, DFC_BUTTON, DFCS_BUTTONPUSH | DFCS_PUSHED);
		rcBox.OffsetRect(1, 1);
	}
	else
	{
		dc.DrawFrameControl(&rcBox, DFC_BUTTON, DFCS_BUTTONPUSH);
	}

	CGdiObject * pOldObject = dc.SelectStockObject(NULL_BRUSH);
	rcBox.DeflateRect(5, 2, 4, 5);
	dc.Rectangle(&rcBox);
	CBrush brs(::GetSysColor(COLOR_3DFACE));
	dc.SelectObject(&brs);
	rcBox.OffsetRect(-2, 2);
	dc.Rectangle(&rcBox);

	dc.SelectObject(pOldObject);
}