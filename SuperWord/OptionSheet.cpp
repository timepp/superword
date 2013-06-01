// OptionSheet.cpp : implementation file
//

#include "stdafx.h"
#include "superword.h"
#include "OptionSheet.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptionSheet

IMPLEMENT_DYNAMIC(COptionSheet, CPropertySheet)

COptionSheet::COptionSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	AddPages();
}

COptionSheet::COptionSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	AddPages();
}

void COptionSheet::AddPages()
{
	m_rmp.m_psp.dwFlags &= ~PSP_HASHELP;
	m_cp.m_psp.dwFlags &= ~PSP_HASHELP;
	AddPage(&m_rmp);
	AddPage(&m_cp);
}

COptionSheet::~COptionSheet()
{
}


BEGIN_MESSAGE_MAP(COptionSheet, CPropertySheet)
	//{{AFX_MSG_MAP(COptionSheet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionSheet message handlers

BOOL COptionSheet::OnInitDialog() 
{
	CPropertySheet::OnInitDialog();
	ModifyStyleEx(0, WS_EX_CONTEXTHELP);
		
	CPopupHelpStyle::CreateDecorator(this);
	
	return TRUE;
}
