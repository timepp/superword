// MiscCondDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SuperWord.h"
#include "MiscCondDlg.h"
#include "NavigateWndCreator.h"

using namespace compdlg;

CCSMiscCondDlg::CCSMiscCondDlg(CWnd* pParent /*=NULL*/)
	: CCSRootDlg(CCSMiscCondDlg::IDD, pParent)
{
}

CCSMiscCondDlg::~CCSMiscCondDlg()
{
}

void CCSMiscCondDlg::DoDataExchange(CDataExchange* pDX)
{
	CCSRootDlg::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_MISC_CONDITION, m_cbMiscCond);
}


BEGIN_MESSAGE_MAP(CCSMiscCondDlg, CCSRootDlg)
END_MESSAGE_MAP()


// CCSMiscCondDlg message handlers

void compdlg::CCSMiscCondDlg::OnOK()
{
	CString str;
	m_cbMiscCond.GetWindowText(str);
	m_pComp->Configure((LPCSTR)str);

	CCSRootDlg::OnOK();
}

BOOL compdlg::CCSMiscCondDlg::OnInitDialog()
{
	CCSRootDlg::OnInitDialog();

	NavigateWnd::MiscConditionArray mca;
	NavigateWnd::MiscConditionArray::iterator it;
	NavigateWnd * pWnd = NavigateWndCreator::Instance()->GetCurrentNavigateWnd();
	pWnd->GetMiscConditions(mca);
	for (it = mca.begin(); it != mca.end(); ++it)
	{
		m_cbMiscCond.AddString(it->c_str());
	}

	m_cbMiscCond.SelectString(0, m_pComp->GetConfiguration().c_str());

	return TRUE;
}
