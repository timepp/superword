// CSOpenDlgDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SuperWord.h"
#include "CSOpenDlgDlg.h"
#include "NavigateWndCreator.h"


using namespace compdlg;

CCSOpenDlgDlg::CCSOpenDlgDlg(CWnd* pParent /*=NULL*/)
	: CCSRootDlg(CCSOpenDlgDlg::IDD, pParent)
{
}

CCSOpenDlgDlg::~CCSOpenDlgDlg()
{
}

void CCSOpenDlgDlg::DoDataExchange(CDataExchange* pDX)
{
	CCSRootDlg::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_DIALOG, m_cbDlgs);
}


BEGIN_MESSAGE_MAP(CCSOpenDlgDlg, CCSRootDlg)
END_MESSAGE_MAP()


// CCSOpenDlgDlg message handlers

BOOL CCSOpenDlgDlg::OnInitDialog()
{
	CCSRootDlg::OnInitDialog();

	NavigateWnd::DlgNameArray arr;
	NavigateWnd::DlgNameArray::const_iterator ci;

	NavigateWnd * pWnd = NavigateWndCreator::Instance()->GetCurrentNavigateWnd();
	pWnd->GetDialogs(arr);
	for (ci = arr.begin(); ci != arr.end(); ++ci)
	{
		m_cbDlgs.AddString(ci->c_str());
	}
	
	m_cbDlgs.SelectString(0, m_pComp->GetConfiguration().c_str());

	return TRUE;
}

void CCSOpenDlgDlg::OnOK()
{
	CString strDlgName;
	m_cbDlgs.GetWindowText(strDlgName);

	m_pComp->Configure((LPCTSTR)strDlgName);

	CCSRootDlg::OnOK();
}
