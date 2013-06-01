// FilterSetDlg.cpp : implementation file
//

#include "stdafx.h"
#include "superword.h"
#include "CSRootDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace compdlg;
/////////////////////////////////////////////////////////////////////////////
// CCSRootDlg dialog

CCSRootDlg::CCSRootDlg(UINT nIDTemplate, CWnd* pParent /* = NULL */)
	: CDialog(nIDTemplate, pParent)
{
	//{{AFX_DATA_INIT(CCSRootDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CCSRootDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCSRootDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCSRootDlg, CDialog)
	//{{AFX_MSG_MAP(CCSRootDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCSRootDlg message handlers

BOOL CCSRootDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CPopupHelpStyle::CreateDecorator(this);
	
	return TRUE;
}

