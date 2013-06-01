// RSMiscPage.cpp : implementation file
//

#include "stdafx.h"
#include "superword.h"
#include "RSMiscPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRSMiscPage property page

IMPLEMENT_DYNCREATE(CRSMiscPage, CPropertyPage)

CRSMiscPage::CRSMiscPage() : CPropertyPage(CRSMiscPage::IDD)
{
	//{{AFX_DATA_INIT(CRSMiscPage)
	m_nWordOrderBase = -1;
	m_nWordOrder = -1;
	//}}AFX_DATA_INIT
}

CRSMiscPage::~CRSMiscPage()
{
}

void CRSMiscPage::UpdateControlState()
{
	// 如果用户选择了"自动设置访问时间",则显示"设置延迟"框,否则不显示
	
}

void CRSMiscPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	GlobalSetting *pSet = GlobalSetting::Instance();
	if (!pDX->m_bSaveAndValidate)
	{
		m_nWordOrder = (pSet->Ms.dwWordOrder & 0x0f) - 1;
		m_nWordOrderBase = ((pSet->Ms.dwWordOrder & 0xf0) >> 4) - 1;
	}
	//{{AFX_DATA_MAP(CRSMiscPage)
	DDX_Control(pDX, IDC_CB_MARK_ACCESSTIME_MODE, m_cbMarkAccesstimeMode);
	DDX_CBIndex(pDX, IDC_CB_WORD_ORDER_BASE, m_nWordOrderBase);
	DDX_CBIndex(pDX, IDC_CB_WORD_ORDER, m_nWordOrder);
	//}}AFX_DATA_MAP
	DDX_CBIndex(pDX, IDC_CB_MARK_ACCESSTIME_MODE, pSet->Ms.maMode);
	DDX_Check(pDX, IDC_CHECK_SHOW_DETAIL_MEANING, pSet->Ms.bShowDetailedMeaning);
	DDX_Check(pDX, IDC_CHECK_MOVENEXT_WHEN_TYPE_RIGHT, pSet->Ms.bMovenextWhenTypeRight);
	DDX_Check(pDX, IDC_CHECK_SHOW_PRACTISE_WND, pSet->Ms.bShowPractiseWnd);
	DDX_Text(pDX, IDC_EDIT_AUTOMARK_ACCESS_TIME_DELAY, pSet->Ms.nDelayWhenAutoSetAccessTime);

	if (pDX->m_bSaveAndValidate)
	{
		pSet->Ms.dwWordOrder = ((m_nWordOrderBase + 1) << 4) | (m_nWordOrder + 1);
	}
}


BEGIN_MESSAGE_MAP(CRSMiscPage, CPropertyPage)
	//{{AFX_MSG_MAP(CRSMiscPage)
	ON_CBN_SELCHANGE(IDC_CB_MARK_ACCESSTIME_MODE, OnSelchangeCbMarkAccesstimeMode)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRSMiscPage message handlers

BOOL CRSMiscPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	CPopupHelpStyle::CreateDecorator(this);
	
	OnSelchangeCbMarkAccesstimeMode();
	return TRUE;
}

void CRSMiscPage::OnSelchangeCbMarkAccesstimeMode() 
{
	int index = m_cbMarkAccesstimeMode.GetCurSel();
	int nShow =  (index == MAM_AUTO) ? SW_SHOW : SW_HIDE;
	GetDlgItem(IDC_STATIC_AUTOMARK_ACCESS_TIME_DELAY)->ShowWindow(nShow);
	GetDlgItem(IDC_EDIT_AUTOMARK_ACCESS_TIME_DELAY)->ShowWindow(nShow);
}

