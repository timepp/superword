// RgnDlg.cpp : implementation file
//

#include "stdafx.h"
#include "superword.h"
#include "RgnDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRgnDlg dialog


CRgnDlg::CRgnDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRgnDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRgnDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CRgnDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRgnDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CRgnDlg::SetFontRegion(LPCTSTR pszText, const LOGFONT *pLf)
{
	CFont font;
	font.CreateFontIndirect(pLf);

	CClientDC dc(this);
	CFont *poldfont = (CFont *)dc.SelectObject(&font);

	dc.BeginPath();
	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(0);
	dc.TextOut(0, 0, pszText);
	dc.EndPath();

	CRgn rgn;
	rgn.CreateFromPath(&dc);
	SetWindowRgn(rgn, TRUE);
	dc.SelectObject(poldfont);
}

void CRgnDlg::SetDlgColor(COLORREF cr)
{
	m_bkColor = cr;

	CClientDC dc(this);
	OnEraseBkgnd(&dc);
}

BEGIN_MESSAGE_MAP(CRgnDlg, CDialog)
	//{{AFX_MSG_MAP(CRgnDlg)
//	ON_WM_NCHITTEST()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
	ON_WM_NCHITTEST()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRgnDlg message handlers

BOOL CRgnDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	return TRUE;
}

BOOL CRgnDlg::OnEraseBkgnd(CDC* pDC) 
{
	CRect rc;
	GetClientRect(&rc);
	pDC->FillSolidRect(&rc, m_bkColor);
	return TRUE;
}

LRESULT CRgnDlg::OnNcHitTest(CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	LRESULT ret = CDialog::OnNcHitTest(point);
	if (ret == HTCLIENT) ret = HTCAPTION;

	return ret;
}
