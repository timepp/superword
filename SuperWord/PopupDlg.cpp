// PopupDlg.cpp : implementation file
//

#include "stdafx.h"
#include "superword.h"
#include "PopupDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPopupDlg dialog


CPopupDlg::CPopupDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPopupDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPopupDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CPopupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPopupDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CPopupDlg::Update(CPoint pt, const CString& str)
{
	if (str != m_strText || !IsWindowVisible())
	{
		m_strText = str;
		if (str == _T(""))
		{
			ShowWindow(SW_HIDE);
			return;
		}

		InvalidateRect(NULL);
	}
	CClientDC dc(this);
	dc.SelectStockObject(SYSTEM_FIXED_FONT);
	CSize sz = dc.GetTextExtent(m_strText);
	SetWindowPos(NULL, pt.x, pt.y, sz.cx + 2, sz.cy + 2, SWP_SHOWWINDOW | SWP_NOACTIVATE);
}


BEGIN_MESSAGE_MAP(CPopupDlg, CDialog)
	//{{AFX_MSG_MAP(CPopupDlg)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPopupDlg message handlers

void CPopupDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CBrush brs(RGB(255, 255, 255));
	CBrush *pOldBrs = dc.SelectObject(&brs);
	CPen *pOldPen = (CPen *)dc.SelectStockObject(BLACK_PEN);

	CRect rc;
	GetClientRect(&rc);
	dc.Rectangle(&rc);
	dc.SetBkMode(TRANSPARENT);
	dc.SelectStockObject(SYSTEM_FIXED_FONT);
	dc.TextOut(1, 1, m_strText);

    dc.SelectObject(pOldPen);
    dc.SelectObject(pOldBrs);
}

void CPopupDlg::PostNcDestroy() 
{
	delete this;
}
