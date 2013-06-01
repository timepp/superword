// AboutDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SuperWord.h"
#include "AboutDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog

CAboutDlg::CAboutDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAboutDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_WM_CREATE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg message handlers

int CAboutDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	

	
	return 0;
}

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAboutDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect rc;
	GetDlgItem(IDC_STATIC_LOGO)->GetWindowRect(&rc);
	ScreenToClient(&rc);

	rc.DeflateRect(1, 1, 1, 1);
	dc.FillSolidRect(&rc, 0);

	CFont f;
	f.CreateFont(-48,0, 0,0,700, 0,0,0, 0, 3,2,1, 34,_T("Arial"));

	dc.SelectObject(&f);
	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(RGB(0, 192, 0));
	dc.DrawText(_T("SuperWord"), &rc, DT_CENTER | DT_VCENTER);
	dc.SetTextColor(RGB(255, 255, 255));
	rc.OffsetRect(-4, -4);
	dc.DrawText(_T("SuperWord"), &rc, DT_CENTER | DT_VCENTER);
}
