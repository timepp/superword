// CSSetColorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SuperWord.h"
#include "CSSetColorDlg.h"
#include "NavigateWndCreator.h"

#include <sstream>

using namespace compdlg;
using namespace std;

CCSSetColorDlg::CCSSetColorDlg(CWnd* pParent /*=NULL*/)
	: CCSRootDlg(CCSSetColorDlg::IDD, pParent)
{
}


void CCSSetColorDlg::DoDataExchange(CDataExchange* pDX)
{
	CCSRootDlg::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_SET_COLOR, m_btnSetColor);
	DDX_Control(pDX, IDC_COMBO_COLOR_ELEMENT, m_cbColorElem);
}


BEGIN_MESSAGE_MAP(CCSSetColorDlg, CCSRootDlg)
END_MESSAGE_MAP()


// CCSSetColorDlg message handlers

BOOL CCSSetColorDlg::OnInitDialog()
{
	CCSRootDlg::OnInitDialog();

	std::string strColorElem;
	COLORREF cr;
	stringstream ss(m_pComp->GetConfiguration());
	ss >> strColorElem >> cr;

	NavigateWnd::ColorElementArray cea;
	NavigateWnd::ColorElementArray::iterator it;
	NavigateWnd * pWnd = NavigateWndCreator::Instance()->GetCurrentNavigateWnd();
	pWnd->GetColorElement(cea);
	for (it = cea.begin(); it != cea.end(); ++it)
	{
		m_cbColorElem.AddString(it->c_str());
	}

	int index = m_cbColorElem.FindStringExact(0, strColorElem.c_str());
	m_cbColorElem.SetCurSel(index);
	
	m_btnSetColor.SetColor(cr);

	return TRUE;
}

void CCSSetColorDlg::OnOK()
{
	int index = m_cbColorElem.GetCurSel();
	if (index < 0)
	{
		AfxMessageBox("必须选择一个界面元素");
		return;
	}

	CString strColorElem;
	COLORREF cr;
	m_cbColorElem.GetLBText(index, strColorElem);
	cr = m_btnSetColor.GetColor();

	stringstream ss;
	ss << (LPCTSTR)strColorElem << " " << cr;

	m_pComp->Configure(ss.str());

	CCSRootDlg::OnOK();
}
