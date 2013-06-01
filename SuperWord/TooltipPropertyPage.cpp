// TooltipPropertyPage.cpp : implementation file
//

#include "stdafx.h"
#include "SuperWord.h"
#include "TooltipPropertyPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTooltipPropertyPage property page

IMPLEMENT_DYNCREATE(CTooltipPropertyPage, CPropertyPage)

CTooltipPropertyPage::CTooltipPropertyPage(UINT nID) 
: CPropertyPage(nID)
{
	//{{AFX_DATA_INIT(CTooltipPropertyPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CTooltipPropertyPage::CTooltipPropertyPage()
{
}

CTooltipPropertyPage::~CTooltipPropertyPage()
{
}

void CTooltipPropertyPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTooltipPropertyPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTooltipPropertyPage, CPropertyPage)
	//{{AFX_MSG_MAP(CTooltipPropertyPage)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTooltipPropertyPage message handlers

BOOL CTooltipPropertyPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	EnableToolTips();
	CWnd *pWnd = GetWindow(GW_CHILD);
	while (pWnd != NULL)
	{
		UINT nID = pWnd->GetDlgCtrlID();
		LPCTSTR pszTooltip = helper::IDS(nID);
		if (pszTooltip != NULL)
		{
			m_tooltip.AddTool(pWnd, pszTooltip);
		}
		pWnd = GetWindow(GW_HWNDNEXT);
	}
	
	return TRUE;
}

int CTooltipPropertyPage::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CPropertyPage::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_tooltip.Create(this);
	return 0;
}

BOOL CTooltipPropertyPage::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_MOUSEFIRST ||
		pMsg->message == WM_MOUSELAST)
	{
		m_tooltip.RelayEvent(pMsg);
	}
	return CPropertyPage::PreTranslateMessage(pMsg);
}
