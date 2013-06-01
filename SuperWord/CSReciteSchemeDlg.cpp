// CSReciteSchemeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SuperWord.h"
#include "CSReciteSchemeDlg.h"
#include ".\csreciteschemedlg.h"

using namespace compdlg;

CCSReciteSchemeDlg::CCSReciteSchemeDlg(CWnd* pParent /*=NULL*/)
	: CCSRootDlg(CCSReciteSchemeDlg::IDD, pParent)
	, m_strReciteSchemeFile(_T(""))
{
}

CCSReciteSchemeDlg::~CCSReciteSchemeDlg()
{
}

void CCSReciteSchemeDlg::DoDataExchange(CDataExchange* pDX)
{
	CCSRootDlg::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_RECITE_SCHEME_FILE, m_strReciteSchemeFile);
}


BEGIN_MESSAGE_MAP(CCSReciteSchemeDlg, CCSRootDlg)
END_MESSAGE_MAP()


BOOL compdlg::CCSReciteSchemeDlg::OnInitDialog()
{
	m_strReciteSchemeFile = m_pComp->GetConfiguration().c_str();

	CCSRootDlg::OnInitDialog();

	CResizableStyle::CreateDecorator(this);
	SetDlgItemResizeInfo(IDC_EDIT_RECITE_SCHEME_FILE, WRS_SYNWIDTH | WRS_SYNHEIGHT);
	SetDlgItemResizeInfo(IDOK, WRS_RIGHT);
	SetDlgItemResizeInfo(IDCANCEL, WRS_RIGHT);

	return TRUE;
}

void compdlg::CCSReciteSchemeDlg::OnOK()
{
	UpdateData(TRUE);
	if (m_strReciteSchemeFile.IsEmpty())
	{
		return;
	}

	m_pComp->Configure((LPCTSTR)m_strReciteSchemeFile);

	CCSRootDlg::OnOK();
}

BOOL compdlg::CCSReciteSchemeDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_LBUTTONDBLCLK && 
		GetFocus()->m_hWnd == GetDlgItem(IDC_EDIT_RECITE_SCHEME_FILE)->m_hWnd)
	{
		CFileDialog dlg(TRUE, 0, 0, OFN_OVERWRITEPROMPT | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST, 
			"背诵方案文件(*.rs)|*.rs||");
		if (dlg.DoModal() == IDOK)
		{
			m_strReciteSchemeFile = dlg.GetPathName();
			UpdateData(FALSE);
		}

		return TRUE;
	}
	
	return CCSRootDlg::PreTranslateMessage(pMsg);
}
