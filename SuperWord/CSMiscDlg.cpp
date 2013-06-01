// CSMiscDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SuperWord.h"
#include "CSMiscDlg.h"
#include "NavigateWndCreator.h"

using namespace compdlg;
using namespace std;

CCSMiscDlg::CCSMiscDlg(CWnd* pParent /*=NULL*/)
	: CCSRootDlg(CCSMiscDlg::IDD, pParent)
	, m_strMiscCmd(_T(""))
{
}

CCSMiscDlg::~CCSMiscDlg()
{
}

void CCSMiscDlg::DoDataExchange(CDataExchange* pDX)
{
	CCSRootDlg::DoDataExchange(pDX);
	DDX_CBString(pDX, IDC_COMBO_MISC_CMD, m_strMiscCmd);
	DDX_Control(pDX, IDC_COMBO_MISC_CMD, m_cbMiscCmd);
}


BEGIN_MESSAGE_MAP(CCSMiscDlg, CCSRootDlg)
END_MESSAGE_MAP()


// CCSMiscDlg message handlers

BOOL compdlg::CCSMiscDlg::OnInitDialog()
{
	m_strMiscCmd = m_pComp->GetConfiguration().c_str();

	CCSRootDlg::OnInitDialog();
	
	NavigateWnd::MiscCommandArray mca;
	NavigateWnd::MiscCommandArray::iterator it;
	NavigateWnd * pWnd = NavigateWndCreator::Instance()->GetCurrentNavigateWnd();
	pWnd->GetMiscCommands(mca);
	for (it = mca.begin(); it != mca.end(); ++it)
	{
		m_cbMiscCmd.AddString(it->c_str());
	}

	m_cbMiscCmd.SelectString(0, m_strMiscCmd);

	return TRUE;
}

void compdlg::CCSMiscDlg::OnOK()
{
	UpdateData(TRUE);
	m_pComp->Configure((LPCTSTR)m_strMiscCmd);
	CCSRootDlg::OnOK();
}
