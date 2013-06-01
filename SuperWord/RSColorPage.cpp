// RSColorPage.cpp : implementation file
//

#include "stdafx.h"
#include "superword.h"
#include "RSColorPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSColorPage dialog


CRSColorPage::CRSColorPage()
	: CPropertyPage(CRSColorPage::IDD)
{
	//{{AFX_DATA_INIT(CRSColorPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CRSColorPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRSColorPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CRSColorPage, CPropertyPage)
	//{{AFX_MSG_MAP(CRSColorPage)
	ON_BN_CLICKED(IDC_BTN_LOAD_COLORSCHEME, OnBtnLoadColorscheme)
	ON_BN_CLICKED(IDC_BTN_SAVE_COLORSCHEME, OnBtnSaveColorscheme)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRSColorPage message handlers

BOOL CRSColorPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	CRect rc;
	GetDlgItem(IDC_COLOR_CHILD)->GetWindowRect(&rc);
	ScreenToClient(&rc);
	m_cp.Create(IDD_COLOR_PAGE, this);
	m_cp.MoveWindow(&rc);	
		
	return TRUE;
}

void CRSColorPage::OnBtnLoadColorscheme() 
{
	m_cp.LoadColorscheme();
	SetModified(TRUE);
}

void CRSColorPage::OnBtnSaveColorscheme() 
{
	m_cp.SaveColorscheme();
}

BOOL CRSColorPage::OnApply() 
{
	m_cp.UpdateData(TRUE);
	GetParent()->GetParent()->SendMessage(WM_COMMAND, ID_RESET_COLORS);
	return CPropertyPage::OnApply();
}
