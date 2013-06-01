// CSMoveWordCmdSetDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SuperWord.h"
#include "CSMoveWordCmdSetDlg.h"
#include "ConcreteCommand.h"


// CCSMoveWordCmdSetDlg dialog

using namespace compdlg;
using namespace comp;

CCSMoveWordCmdSetDlg::CCSMoveWordCmdSetDlg(CWnd* pParent /*=NULL*/)
	: CCSRootDlg(CCSMoveWordCmdSetDlg::IDD, pParent)
{
}

CCSMoveWordCmdSetDlg::~CCSMoveWordCmdSetDlg()
{
}

void CCSMoveWordCmdSetDlg::DoDataExchange(CDataExchange* pDX)
{
    CCSRootDlg::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO_MOVEWORD_CMD, m_cbMoveWordCmd);
}


BEGIN_MESSAGE_MAP(CCSMoveWordCmdSetDlg, CCSRootDlg)
END_MESSAGE_MAP()


// CCSMoveWordCmdSetDlg message handlers

BOOL compdlg::CCSMoveWordCmdSetDlg::OnInitDialog()
{
    CCSRootDlg::OnInitDialog();

    cmd::MoveWordCommand * pCmd = dynamic_cast<cmd::MoveWordCommand *>(m_pComp);

    int sel = 0;
    for (int i = 0; cmd::MoveWordCommand::ms_arrOp[i][0] != '\0'; i++)
    {
        m_cbMoveWordCmd.AddString(cmd::MoveWordCommand::ms_arrOp[i]);
        if (pCmd->GetConfiguration() == cmd::MoveWordCommand::ms_arrOp[i])
        {
            sel = i;
        }
    }
    m_cbMoveWordCmd.SetCurSel(sel);
    return TRUE;  
}

void compdlg::CCSMoveWordCmdSetDlg::OnOK()
{
    int sel = m_cbMoveWordCmd.GetCurSel();
    cmd::MoveWordCommand * pCmd = dynamic_cast<cmd::MoveWordCommand *>(m_pComp);

    pCmd->Configure(cmd::MoveWordCommand::ms_arrOp[sel]);

    CCSRootDlg::OnOK();
}
