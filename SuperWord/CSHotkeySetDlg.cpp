// CSHotkeySetDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SuperWord.h"
#include "CSHotkeySetDlg.h"
#include "ConcreteCommand.h"

#include <sstream>
#include ".\cshotkeysetdlg.h"


// CCSHotkeySetDlg dialog
using namespace compdlg;
using namespace comp;
using namespace std;


CCSHotkeySetDlg::CCSHotkeySetDlg(CWnd* pParent /*=NULL*/)
	: CCSRootDlg(CCSHotkeySetDlg::IDD, pParent)
{
}

CCSHotkeySetDlg::~CCSHotkeySetDlg()
{
}

void CCSHotkeySetDlg::DoDataExchange(CDataExchange* pDX)
{
    CCSRootDlg::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_HOTKEY, m_hotkey);
}


BEGIN_MESSAGE_MAP(CCSHotkeySetDlg, CCSRootDlg)
END_MESSAGE_MAP()


// CCSHotkeySetDlg message handlers


BOOL compdlg::CCSHotkeySetDlg::OnInitDialog()
{
    CCSRootDlg::OnInitDialog();

    ACCEL acl;
    string str1;
    cmd::HotkeyCommand * pCmd = dynamic_cast<cmd::HotkeyCommand *>(m_pComp);
    string str = pCmd->GetConfiguration();
    stringstream ss(str);
    ss >> (int&)acl.fVirt >> acl.key >> str1;
    m_hotkey.SetHotKey(acl);

    return TRUE; 
}

void compdlg::CCSHotkeySetDlg::OnOK()
{
    ACCEL acl;
    cmd::HotkeyCommand * pCmd = dynamic_cast<cmd::HotkeyCommand *>(m_pComp);

    m_hotkey.GetHotKey(acl);
    stringstream ss;
    ss << (int)acl.fVirt << " " << acl.key << " " << m_hotkey.GetHotKeyName();
    pCmd->Configure(ss.str());
    CCSRootDlg::OnOK();
}

BOOL compdlg::CCSHotkeySetDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message >= WM_KEYFIRST && pMsg->message <= WM_KEYLAST)
	{
		if (pMsg->wParam == VK_TAB || pMsg->wParam == VK_RETURN)
		{
			if (pMsg->hwnd == m_hotkey.m_hWnd)
			{
				m_hotkey.CHotKeyCtrl::SetHotKey(static_cast<WORD>(pMsg->wParam), 0);
				return FALSE;
			}
		}
	}
	return CCSRootDlg::PreTranslateMessage(pMsg);
}
