// CSTimerCmdSetDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SuperWord.h"
#include "CSTimerCmdSetDlg.h"
#include "ConcreteCommand.h"

#include <sstream>
#include ".\cstimercmdsetdlg.h"

using namespace compdlg;
using namespace comp;
using namespace std;

// CCSTimerCmdSetDlg dialog

CCSTimerCmdSetDlg::CCSTimerCmdSetDlg(CWnd* pParent /*=NULL*/)
	: CCSRootDlg(CCSTimerCmdSetDlg::IDD, pParent)
    , m_interval(0)
	, m_strRepeatTime(_T(""))
	, m_delete_on_word_change(FALSE)
{

}

CCSTimerCmdSetDlg::~CCSTimerCmdSetDlg()
{
}

void CCSTimerCmdSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CCSRootDlg::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_INTERVAL, m_interval);
	DDX_Control(pDX, IDC_COMBO_REPEAT_TIME, m_cbRepeatTime);
	DDX_CBString(pDX, IDC_COMBO_REPEAT_TIME, m_strRepeatTime);
	DDX_Check(pDX, IDC_CHECK_DELETE_ON_WORD_CHANGE, m_delete_on_word_change);
}


BEGIN_MESSAGE_MAP(CCSTimerCmdSetDlg, CCSRootDlg)
END_MESSAGE_MAP()


// CCSTimerCmdSetDlg message handlers

void compdlg::CCSTimerCmdSetDlg::OnOK()
{
    CCSRootDlg::OnOK();

	size_t repeat;
	stringstream((LPCTSTR)m_strRepeatTime) >> repeat;

    std::stringstream ss;
    ss << m_interval << " " << repeat << " " << m_delete_on_word_change;
    m_pComp->Configure(ss.str());
}

BOOL compdlg::CCSTimerCmdSetDlg::OnInitDialog()
{
	std::string repeat;
    std::stringstream(m_pComp->GetConfiguration()) >> m_interval >> repeat >> m_delete_on_word_change;
	m_strRepeatTime = repeat.c_str();

	CCSRootDlg::OnInitDialog();

    return TRUE;
}
