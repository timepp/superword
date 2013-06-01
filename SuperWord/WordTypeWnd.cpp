// WordTypeWnd.cpp : implementation file
//

#include "stdafx.h"
#include "superword.h"
#include "WordTypeWnd.h"
#include "WordType.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CWordTypeWnd

CWordTypeWnd::CWordTypeWnd()
{
	m_crActive = RGB(0, 192, 0);
	m_crInActive = DarkColor(m_crActive);
	m_crBorder = 0;
	m_cxCount = 8;
	m_wWordType = 0;
	m_pTipDlg = NULL;
}

CWordTypeWnd::~CWordTypeWnd()
{
	m_pTipDlg = NULL;
}

COLORREF CWordTypeWnd::DarkColor(COLORREF cr)
{
	int r = GetRValue(cr);
	int g = GetGValue(cr);
	int b = GetBValue(cr);
	return RGB(r/2, g/2, b/2);
}

void CWordTypeWnd::SetColors(COLORREF crBorder, COLORREF crActive, COLORREF crInActive /* = 0xFF000000 */)
{
	m_crBorder = crBorder;
	m_crActive = crActive;
	m_crInActive = crInActive;
	if (crInActive == 0XFF000000)
	{
		m_crInActive = DarkColor(crActive);
	}
	else
	{
		m_crInActive = crInActive;
	}
	if (m_hWnd)
		InvalidateRect(NULL);
}

void CWordTypeWnd::SetCxCount(int cxCount)
{
	ASSERT(16 % cxCount == 0);

	m_cxCount = cxCount;
}

void CWordTypeWnd::SetWordType(WORD wWordType)
{
	WORD change = wWordType ^ m_wWordType;
	m_wWordType = wWordType;
	DrawCell(change);
}

void CWordTypeWnd::UpdateTip(CPoint pt)
{
	for (int i = 0; i < 16; i++)
	{
		if (m_Cells[i].PtInRect(pt))
		{
			CString str = WordType::Instance()->Type(i).c_str();
			ClientToScreen(&pt);
			pt.Offset(20, 20);
			m_pTipDlg->Update(pt, str);
			return;
		}
	}
}

void CWordTypeWnd::DrawCell(WORD wMask)
{
	CClientDC dc(this);
	CPen *pOldpen = dc.GetCurrentPen();
	CBrush *pOldBrs = dc.GetCurrentBrush();

	CPen pen(PS_SOLID, 1, m_crBorder);
	CBrush brsActive(m_crActive);
	CBrush brsInActive(m_crInActive);

	dc.SelectObject(&pen);

	for (WORD w = 1, i = 0; i < 16; w <<= 1, i++)
	{
		if (wMask & w)
		{
			dc.SelectObject((m_wWordType & w) ? &brsActive : &brsInActive);
			dc.Rectangle(m_Cells[i]);
		}
	}
	
	dc.SelectObject(pOldBrs);
	dc.SelectObject(pOldpen);
}

BEGIN_MESSAGE_MAP(CWordTypeWnd, CButton)
	//{{AFX_MSG_MAP(CWordTypeWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONUP()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWordTypeWnd message handlers

void CWordTypeWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	for (int i = 0; i < 16; i++)
		DrawCell();
}

void CWordTypeWnd::PreSubclassWindow() 
{
	CRect rc;
	GetClientRect(rc);
	int cxCount = m_cxCount;
	int cyCount = 16 / cxCount;
	
	int cx = (rc.Width() - cxCount - 1) / cxCount;
	int cy = (rc.Height() - cyCount - 1) / cyCount;

	for (int i = 0; i < cxCount; i++)
		for (int j = 0; j < cyCount; j++)
	{
		m_Cells[j * cxCount + i].SetRect(i + i * cx, j + j * cy, i + i * cx + cx + 2, j + j * cy + cy + 2);
	}

	m_pTipDlg = new CPopupDlg(this);
	m_pTipDlg->Create(IDD_POPUP_DLG, this);
	
	CButton::PreSubclassWindow();
}

void CWordTypeWnd::OnLButtonUp(UINT nFlags, CPoint point) 
{
	for (int i = 0; i < 16; i++)
	{
		if (m_Cells[i].PtInRect(point))
		{
			::SendMessage(GetParent()->m_hWnd, WM_COMMAND, IDC_TOGGLE_WORDTYPE_1 + i, NULL);
		}
	}

	CButton::OnLButtonUp(nFlags, point);
}

void CWordTypeWnd::OnMouseMove(UINT nFlags, CPoint point) 
{
	CButton::OnMouseMove(nFlags, point);
	
	UpdateTip(point);
	TRACKMOUSEEVENT tme = {sizeof(TRACKMOUSEEVENT), TME_LEAVE, m_hWnd, HOVER_DEFAULT};
	::_TrackMouseEvent(&tme);
}

void CWordTypeWnd::DrawItem(LPDRAWITEMSTRUCT) 
{
	for (int i = 0; i < 16; i++)
		DrawCell();
}

LRESULT CWordTypeWnd::OnMouseLeave(WPARAM, LPARAM)
{
	m_pTipDlg->ShowWindow(SW_HIDE);
	return 1;
}

void CWordTypeWnd::OnRButtonUp(UINT nFlags, CPoint point) 
{
	WordType *wt = WordType::Instance();
	const StringVector& sv = wt->GetAllType();

	CMenu mu;
	mu.CreatePopupMenu();

	StringVector::const_iterator ci;
	int pos = 0;
	for (ci = sv.begin(); ci != sv.end(); ++ci, ++pos)
	{
		UINT nID = IDC_TOGGLE_WORDTYPE_1 + pos;
		BOOL bChecked = m_wWordType & (1 << pos);
		mu.InsertMenu(pos, MF_BYPOSITION, nID, (*ci).c_str());
		mu.CheckMenuItem(nID, MF_BYCOMMAND | (bChecked ? MF_CHECKED : MF_UNCHECKED));
	}

	POINT pt;
	GetCursorPos(&pt);
	mu.TrackPopupMenu(TPM_LEFTALIGN, pt.x, pt.y, GetParent());
	
	CButton::OnRButtonUp(nFlags, point);
}
