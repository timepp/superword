// CSShowElementDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SuperWord.h"
#include "CSShowElementDlg.h"
#include "NavigateWndCreator.h"

#include <sstream>

using namespace compdlg;
using namespace std;

CCSShowElementDlg::CCSShowElementDlg(CWnd* pParent /*=NULL*/)
	: CCSRootDlg(CCSShowElementDlg::IDD, pParent)
	, m_bShow(FALSE)
{
}

CCSShowElementDlg::~CCSShowElementDlg()
{
}

void CCSShowElementDlg::DoDataExchange(CDataExchange* pDX)
{
	CCSRootDlg::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO_HIDE_WORD, m_bShow);
	DDX_Control(pDX, IDC_COMBO_VISUAL_ELEMENT, m_cbVisualElement);
}


BEGIN_MESSAGE_MAP(CCSShowElementDlg, CCSRootDlg)
END_MESSAGE_MAP()


// CCSShowElementDlg message handlers

BOOL compdlg::CCSShowElementDlg::OnInitDialog()
{
	std::string visual_element;
	stringstream ss(m_pComp->GetConfiguration());
	ss >> visual_element >> m_bShow;

	CCSRootDlg::OnInitDialog();

	NavigateWnd::VisualElementArray vea;
	NavigateWnd::VisualElementArray::iterator it;
	NavigateWnd * pWnd = NavigateWndCreator::Instance()->GetCurrentNavigateWnd();
	pWnd->GetVisualElement(vea);
	for (it = vea.begin(); it != vea.end(); ++it)
	{
		m_cbVisualElement.AddString(it->c_str());
	}

	int index = m_cbVisualElement.FindString(0, visual_element.c_str());
	m_cbVisualElement.SetCurSel(index);

	return TRUE;
}

void compdlg::CCSShowElementDlg::OnOK()
{
	UpdateData(TRUE);

	int index = m_cbVisualElement.GetCurSel();
	if (index < 0)
	{
		AfxMessageBox("必须选择一个界面元素");
		return;
	}

	CString strElement;
	m_cbVisualElement.GetWindowText(strElement);
	stringstream ss;
	ss << (LPCTSTR)strElement << " " << m_bShow;
	m_pComp->Configure(ss.str());

	CCSRootDlg::OnOK();
}
