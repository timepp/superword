// CSRemarkDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SuperWord.h"
#include "CSRemarkDlg.h"
#include ".\csremarkdlg.h"

using namespace compdlg;

CCSRemarkDlg::CCSRemarkDlg(CWnd* pParent /*=NULL*/)
	: CCSRootDlg(CCSRemarkDlg::IDD, pParent)
	, m_strRemark(_T(""))
{
}

CCSRemarkDlg::~CCSRemarkDlg()
{
}

void CCSRemarkDlg::DoDataExchange(CDataExchange* pDX)
{
	CCSRootDlg::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_COMP_REMARK, m_strRemark);
}


BEGIN_MESSAGE_MAP(CCSRemarkDlg, CCSRootDlg)
END_MESSAGE_MAP()


// CCSRemarkDlg message handlers

BOOL compdlg::CCSRemarkDlg::OnInitDialog()
{
	m_strRemark = m_pComp->GetConfiguration().c_str();

	CCSRootDlg::OnInitDialog();

	return TRUE;
}

void compdlg::CCSRemarkDlg::OnOK()
{
	UpdateData(TRUE);

	m_pComp->Configure((LPCTSTR)m_strRemark);

	CCSRootDlg::OnOK();
}
