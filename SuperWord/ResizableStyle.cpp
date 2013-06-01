  // ResizableGrip.cpp: implementation of the CResizableStyle class.
//

#include "stdafx.h"
#include "ResizableStyle.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

using decorate::CResizableStyle;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CResizableStyle::CResizableStyle()
{
	m_bDisableHorizontalResize = FALSE;
	m_bDisableVerticalResize = FALSE;
}

CResizableStyle::~CResizableStyle()
{

}

void CResizableStyle::DisableHorizontalResize()
{
	m_bDisableHorizontalResize = TRUE;
}
void CResizableStyle::DisableVerticalResize()
{
	m_bDisableVerticalResize = TRUE;
}

void CResizableStyle::DrawGrip()
{
	CRect rc;
	m_pWnd->GetClientRect(&rc);
	CClientDC dc(m_pWnd);

	CPen penDark(PS_SOLID, 1, ::GetSysColor(COLOR_BTNSHADOW));
	CPen penLight(PS_SOLID, 1, ::GetSysColor(COLOR_BTNHILIGHT));
	CPen *pOldpen = dc.GetCurrentPen();
	CPen* penList[] = {&penDark, &penDark, &penLight};

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			CPoint pt1(rc.right, rc.bottom - 2 - i * 4 - j);
			CPoint pt2(rc.right - 2 - i * 4 - j, rc.bottom);
			dc.SelectObject(penList[j]);
			dc.MoveTo(pt1);
			dc.LineTo(pt2);
		}
	}

	dc.SelectObject(pOldpen);
}

BOOL CResizableStyle::PointOnResizeRgn(int x, int y)
{
	CRect rc;
	m_pWnd->GetWindowRect(&rc);
	rc.left = rc.right - 15;
	rc.top = rc.bottom - 15;
	
	return rc.PtInRect(CPoint(x, y));
}

BOOL CResizableStyle::WndProcBeforeOldProc(UINT msg, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);

	if (msg == WM_SIZE)
	{
		// TODO: finish the "disable horizontal resize" and "disable vertical resize"
		RecalcLayout();
	}
	return RETURN_DEFAULT;
}

BOOL CResizableStyle::WndProcAfterOldProc(UINT msg, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(wParam);

	if (msg == WM_PAINT)
	{
		// 在右下角画一个resizable sign
		DrawGrip();
	}

	else if (msg == WM_NCHITTEST)
	{
		int x = GET_X_LPARAM(lParam);
		int y = GET_Y_LPARAM(lParam);
		if (m_retOldProc == HTCLIENT && PointOnResizeRgn(x, y))
			return HTBOTTOMRIGHT;
	}

	return RETURN_DEFAULT;
}

BOOL CResizableStyle::OnInitDecorator()
{
	return TRUE;
}

// NOTE: If one child window is set by SetDlgItemResizeInfo, all other childs 
//       must be set exactly at the same time.
BOOL CResizableStyle::SetDlgItemResizeInfo(UINT nID, DWORD dwResizeStyle, DWORD dwResizeMeasureStyle /* = WRMS_PIXEL */)
{
	ASSERT_VALID(m_pWnd);
	m_pWnd->GetClientRect(&m_originalClientRect);
	m_pWnd->GetWindowRect(&m_originalFullRect);

	CWnd *pChild = m_pWnd->GetDlgItem(nID);

	if (pChild == NULL || !::IsWindow(pChild->m_hWnd))
		return FALSE;
	
	ChildResizeInfo cri;
	cri.dwResizeStyle = dwResizeStyle;
	cri.dwResizeMeasureStyle = dwResizeMeasureStyle;
	pChild->GetWindowRect(cri.rcOriginal);
	m_pWnd->ScreenToClient(&cri.rcOriginal);

	m_criMap.erase(nID);
	return m_criMap.insert(ChildResizeInfoMap::value_type(nID, cri)).second;
}

void CResizableStyle::RecalcLayout()
{
	CRect rcNew;
	m_pWnd->GetClientRect(&rcNew);

	UINT nID;
	ChildResizeInfo cri;
	ChildResizeInfoMap::const_iterator ci;
	for (ci = m_criMap.begin(); ci != m_criMap.end(); ++ci)
	{
		nID = ci->first;
		cri = ci->second;
		RePlaceChildWnd(nID, &cri, rcNew);
	}

	m_pWnd->InvalidateRect(NULL);
}

void CResizableStyle::RePlaceChildWnd(UINT nID, const ChildResizeInfo* pCri, const CRect& rcNew)
{
	CWnd *pChild = m_pWnd->GetDlgItem(nID);
	CRect rc = pCri->rcOriginal;
	int nRightOffset;
	int nBottomOffset;
	if (pCri->dwResizeMeasureStyle == WRMS_PIXEL)
	{
		if (pCri->dwResizeStyle & WRS_RIGHT)
		{
			nRightOffset = rcNew.right - m_originalClientRect.right;
			rc.right += nRightOffset;
			if (!(pCri->dwResizeStyle & WRS_LEFT)) rc.left += nRightOffset;
		}
		if (pCri->dwResizeStyle & WRS_BOTTOM)
		{
			nBottomOffset = rcNew.bottom - m_originalClientRect.bottom;
			rc.bottom += nBottomOffset;
			if (!(pCri->dwResizeStyle & WRS_TOP)) rc.top += nBottomOffset;
		}
	}

	pChild->MoveWindow(&rc, FALSE);
}