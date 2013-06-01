// CSWordTypeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SuperWord.h"
#include "CSWordTypeDlg.h"
#include "WordType.h"
#include "LibSrc/greta/regexpr2.h"

#include <sstream>

using namespace compdlg;
using namespace std;

CCSWordTypeDlg::CCSWordTypeDlg(CWnd* pParent /*=NULL*/)
	: CCSRootDlg(CCSWordTypeDlg::IDD, pParent)
	, m_nStyle(2)
{
}

CCSWordTypeDlg::~CCSWordTypeDlg()
{
}

void CCSWordTypeDlg::DoDataExchange(CDataExchange* pDX)
{
	CCSRootDlg::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_WORD_TYPE, m_cbWordType);
	DDX_Radio(pDX, IDC_RADIO_SET_WORD_TYPE_STYLE, m_nStyle);
}


BEGIN_MESSAGE_MAP(CCSWordTypeDlg, CCSRootDlg)
END_MESSAGE_MAP()


// CCSWordTypeDlg message handlers

BOOL compdlg::CCSWordTypeDlg::OnInitDialog()
{
	regex::rpattern pat("^(.*) ([0-9]+)$");
	regex::match_results ret;
	std::string word_type;

	std::string str = m_pComp->GetConfiguration();
	if (pat.match(str, ret).matched)
	{
		word_type = ret.backref(1).str();
		stringstream(ret.backref(2).str()) >> m_nStyle;
	}

	CCSRootDlg::OnInitDialog();

	const StringVector& types = WordType::Instance()->GetAllType();
	for (StringVector::const_iterator ci = types.begin(); ci != types.end(); ++ci)
	{
		m_cbWordType.AddString(ci->c_str());
	}

	m_cbWordType.SelectString(0, word_type.c_str());

	return TRUE;
}

void compdlg::CCSWordTypeDlg::OnOK()
{
	UpdateData(TRUE);

	CString strType;
	m_cbWordType.GetWindowText(strType);

	stringstream ss;
	ss << (LPCTSTR)strType << " " << m_nStyle;
	m_pComp->Configure(ss.str());

	CCSRootDlg::OnOK();
}
