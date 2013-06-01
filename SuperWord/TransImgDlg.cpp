// TransImgDlg.cpp : implementation file
//

#include "stdafx.h"
#include "superword.h"
#include "TransImgDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTransImgDlg dialog


CTransImgDlg::CTransImgDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTransImgDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTransImgDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTransImgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTransImgDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTransImgDlg, CDialog)
	//{{AFX_MSG_MAP(CTransImgDlg)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTransImgDlg message handlers

void CTransImgDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
}

BOOL CTransImgDlg::OnEraseBkgnd(CDC* pDC) 
{
	UNREFERENCED_PARAMETER(pDC);
	return TRUE;
}
