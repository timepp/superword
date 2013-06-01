// CSAccelDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SuperWord.h"
#include "CSAccelDlg.h"

#include <sstream>
#include ".\csacceldlg.h"

using namespace compdlg;
using namespace std;

const int CCSAccelDlg::NORM = 0;		// normal
const int CCSAccelDlg::HIDE = 1;		// hide in combobox but when use press the key, then show
const int CCSAccelDlg::ESTP = 2;		// prevent user from use this key (estop)

CCSAccelDlg::VkInfo CCSAccelDlg::m_infoVk[256] =
{
// 0x00
	{ HIDE, "VK_0" },
	{ HIDE, "������" },
	{ HIDE, "����Ҽ�" },
	{ HIDE, "����:�ж�(CTRL+BREAK)" },
	{ HIDE, "����м�" },
	{ HIDE, "���X1��" },
	{ HIDE, "���X2��" },
	{ HIDE, "VK_7" },
	{ NORM, "����:Backspace" },
	{ NORM, "����:TAB" },
	{ HIDE, "VK_10" },
	{ HIDE, "VK_11" },
	{ NORM, "����:CLEAR" },
	{ NORM, "����:�س�" },
	{ HIDE, "VK_14" },
	{ HIDE, "VK_15" },
// 0x10
	{ ESTP, "����:Shift" },
	{ ESTP, "����:Control" },
	{ ESTP, "����:Alt" },
	{ NORM, "����:Pause(Break)" },
	{ NORM, "����:Caps Lock" },
	{ HIDE, "IME-Kanaģʽ" },
	{ HIDE, "VK_22" },
	{ HIDE, "IME-Junjaģʽ" },
	{ HIDE, "IME-finalģʽ" },
	{ HIDE, "IME-Hanja/Kanjiģʽ" },
	{ HIDE, "VK_26" },
	{ NORM, "����:Esc" },
	{ HIDE, "IME-Convert" },
	{ HIDE, "IME-No Convert" },
	{ HIDE, "IME-Accept" },
	{ HIDE, "IME-�л�" },
// 0x20
	{ NORM, "�ո�" },
	{ NORM, "����:Page Up" },
	{ NORM, "����:Page Down" },
	{ NORM, "����:End" },
	{ NORM, "����:Home" },
	{ NORM, "����:Arrow Left" },
	{ NORM, "����:Arrow Up" },
	{ NORM, "����:Arrow Right" },
	{ NORM, "����:Arrow Down" },
	{ NORM, "��չ:Select" },
	{ NORM, "��չ:Print" },
	{ NORM, "��չ:Execute" },
	{ NORM, "����:PrintScreen" },
	{ NORM, "����:Insert" },
	{ NORM, "����:Delete" },
	{ NORM, "��չ:Help" },
// 0x30
	{ NORM, "����0" },
	{ NORM, "����1" },
	{ NORM, "����2" },
	{ NORM, "����3" },
	{ NORM, "����4" },
	{ NORM, "����5" },
	{ NORM, "����6" },
	{ NORM, "����7" },
	{ NORM, "����8" },
	{ NORM, "����9" },
	{ HIDE, "VK_58" },
	{ HIDE, "VK_59" },
	{ HIDE, "VK_60" },
	{ HIDE, "VK_61" },
	{ HIDE, "VK_62" },
	{ HIDE, "VK_63" },
// 0x40
	{ HIDE, "VK_64" },
	{ NORM, "��ĸ:A" },
	{ NORM, "��ĸ:B" },
	{ NORM, "��ĸ:C" },
	{ NORM, "��ĸ:D" },
	{ NORM, "��ĸ:E" },
	{ NORM, "��ĸ:F" },
	{ NORM, "��ĸ:G" },
	{ NORM, "��ĸ:H" },
	{ NORM, "��ĸ:I" },
	{ NORM, "��ĸ:J" },
	{ NORM, "��ĸ:K" },
	{ NORM, "��ĸ:L" },
	{ NORM, "��ĸ:M" },
	{ NORM, "��ĸ:N" },
	{ NORM, "��ĸ:O" },
// 0x50
	{ NORM, "��ĸ:P" },
	{ NORM, "��ĸ:Q" },
	{ NORM, "��ĸ:R" },
	{ NORM, "��ĸ:S" },
	{ NORM, "��ĸ:T" },
	{ NORM, "��ĸ:U" },
	{ NORM, "��ĸ:V" },
	{ NORM, "��ĸ:W" },
	{ NORM, "��ĸ:X" },
	{ NORM, "��ĸ:Y" },
	{ NORM, "��ĸ:Z" },
	{ ESTP, "����:��Windows" },
	{ ESTP, "����:��Windows" },
	{ ESTP, "����:Applications" },
	{ HIDE, "VK_94" },
	{ HIDE, "����:Sleep" },
// 0x60
	{ NORM, "С����0" },
	{ NORM, "С����1" },
	{ NORM, "С����2" },
	{ NORM, "С����3" },
	{ NORM, "С����4" },
	{ NORM, "С����5" },
	{ NORM, "С����6" },
	{ NORM, "С����7" },
	{ NORM, "С����8" },
	{ NORM, "С����9" },
	{ NORM, "С����*" },
	{ NORM, "С����+" },
	{ NORM, "С���̷ָ�����" },
	{ NORM, "С����-" },
	{ NORM, "С����." },
	{ NORM, "С����/" },
// 0x70
	{ NORM, "F1" },
	{ NORM, "F2" },
	{ NORM, "F3" },
	{ NORM, "F4" },
	{ NORM, "F5" },
	{ NORM, "F6" },
	{ NORM, "F7" },
	{ NORM, "F8" },
	{ NORM, "F9" },
	{ NORM, "F10" },
	{ NORM, "F11" },
	{ NORM, "F12" },
	{ HIDE, "F13" },
	{ HIDE, "F14" },
	{ HIDE, "F15" },
	{ HIDE, "F16" },
// 0x80
	{ HIDE, "F17" },
	{ HIDE, "F18" },
	{ HIDE, "F19" },
	{ HIDE, "F20" },
	{ HIDE, "F21" },
	{ HIDE, "F22" },
	{ HIDE, "F23" },
	{ HIDE, "F24" },
	{ HIDE, "VK_136" },
	{ HIDE, "VK_137" },
	{ HIDE, "VK_138" },
	{ HIDE, "VK_139" },
	{ HIDE, "VK_140" },
	{ HIDE, "VK_141" },
	{ HIDE, "VK_142" },
	{ HIDE, "VK_143" },
// 0x90
	{ NORM, "����:Num Lock" },
	{ NORM, "����:Scroll Lock" },
	{ HIDE, "VK_146" },
	{ HIDE, "VK_147" },
	{ HIDE, "VK_148" },
	{ HIDE, "VK_149" },
	{ HIDE, "VK_150" },
	{ HIDE, "VK_151" },
	{ HIDE, "VK_152" },
	{ HIDE, "VK_153" },
	{ HIDE, "VK_154" },
	{ HIDE, "VK_155" },
	{ HIDE, "VK_156" },
	{ HIDE, "VK_157" },
	{ HIDE, "VK_158" },
	{ HIDE, "VK_159" },
// 0xA0
	{ ESTP, "����:��Shift" },
	{ ESTP, "����:��Shift" },
	{ ESTP, "����:��Control" },
	{ ESTP, "����:��Control" },
	{ ESTP, "����:��Alt" },
	{ ESTP, "����:��Alt" },
	{ HIDE, "Browser-Back" },
	{ HIDE, "Browser-Forward" },
	{ HIDE, "Browser-Refresh" },
	{ HIDE, "Browser-Stop" },
	{ HIDE, "Browser-Search" },
	{ HIDE, "Browser-Favorite" },
	{ HIDE, "Browser-Home" },
	{ HIDE, "����:����" },
	{ HIDE, "����:��С����" },
	{ HIDE, "����:��������" },
// 0xB0
	{ HIDE, "����:��һ��Ŀ" },
	{ HIDE, "����:ǰһ��Ŀ" },
	{ HIDE, "����:ֹͣ����" },
	{ HIDE, "����:��ͣ����" },
	{ HIDE, "����:�����ʼ�(Start Mail)" },
	{ HIDE, "����:����ý��ѡ��" },
	{ HIDE, "����:��������1" },
	{ HIDE, "����:��������2" },
	{ HIDE, "VK_184" },
	{ HIDE, "VK_185" },
	{ NORM, "���:;" },
	{ NORM, "���:=" },
	{ NORM, "���:," },
	{ NORM, "���:-" },
	{ NORM, "���:." },
	{ NORM, "���:/" },
// 0xC0
	{ NORM, "���:`" },
	{ HIDE, "VK_193" },
	{ HIDE, "VK_194" },
	{ HIDE, "VK_195" },
	{ HIDE, "VK_196" },
	{ HIDE, "VK_197" },
	{ HIDE, "VK_198" },
	{ HIDE, "VK_199" },
	{ HIDE, "VK_200" },
	{ HIDE, "VK_201" },
	{ HIDE, "VK_202" },
	{ HIDE, "VK_203" },
	{ HIDE, "VK_204" },
	{ HIDE, "VK_205" },
	{ HIDE, "VK_206" },
	{ HIDE, "VK_207" },
// 0xD0
	{ HIDE, "VK_208" },
	{ HIDE, "VK_209" },
	{ HIDE, "VK_210" },
	{ HIDE, "VK_211" },
	{ HIDE, "VK_212" },
	{ HIDE, "VK_213" },
	{ HIDE, "VK_214" },
	{ HIDE, "VK_215" },
	{ HIDE, "VK_216" },
	{ HIDE, "VK_217" },
	{ HIDE, "VK_218" },
	{ NORM, "���:[" },
	{ NORM, "���:\\" },
	{ NORM, "���:]" },
	{ NORM, "���:\'" },
	{ HIDE, "VK_223" },
// 0xE0
	{ HIDE, "VK_224" },
	{ HIDE, "VK_225" },
	{ NORM, "���:(102����) , . �� /" },
	{ HIDE, "VK_227" },
	{ HIDE, "VK_228" },
	{ HIDE, "IME-PROCESS" },
	{ HIDE, "VK_230" },
	{ HIDE, "VK_231" },
	{ HIDE, "VK_232" },
	{ HIDE, "VK_233" },
	{ HIDE, "VK_234" },
	{ HIDE, "VK_235" },
	{ HIDE, "VK_236" },
	{ HIDE, "VK_237" },
	{ HIDE, "VK_238" },
	{ HIDE, "VK_239" },
// 0xF0
	{ HIDE, "VK_240" },
	{ HIDE, "VK_241" },
	{ HIDE, "VK_242" },
	{ HIDE, "VK_243" },
	{ HIDE, "VK_244" },
	{ HIDE, "VK_245" },
	{ NORM, "��չ:Attn" },
	{ NORM, "��չ:CrSel" },
	{ NORM, "��չ:ExSel" },
	{ NORM, "��չ:Erase EOF" },
	{ HIDE, "����:����" },
	{ NORM, "��չ:Zoom" },
	{ HIDE, "VK_252" },
	{ NORM, "��չ:PA1" },
	{ HIDE, "OEM Clear" },
	{ HIDE, "VK_255" }
};

CCSAccelDlg::CCSAccelDlg(CWnd* pParent /*=NULL*/)
	: CCSRootDlg(CCSAccelDlg::IDD, pParent)
	, m_bAlt(FALSE)
	, m_bControl(FALSE)
	, m_bShift(FALSE)
	, m_bGlobal(FALSE)
{
}

CCSAccelDlg::~CCSAccelDlg()
{
}

void CCSAccelDlg::DoDataExchange(CDataExchange* pDX)
{
	CCSRootDlg::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK_ALT, m_bAlt);
	DDX_Check(pDX, IDC_CHECK_CONTROL, m_bControl);
	DDX_Check(pDX, IDC_CHECK_SHIFT, m_bShift);
	DDX_Control(pDX, IDC_COMBO_VIRTUAL_KEY, m_cbVirtualKey);
	DDX_Check(pDX, IDC_CHECK_DELETE_ON_WORD_CHANGE, m_bGlobal);
}


BEGIN_MESSAGE_MAP(CCSAccelDlg, CCSRootDlg)
END_MESSAGE_MAP()


// CCSAccelDlg message handlers

BOOL compdlg::CCSAccelDlg::OnInitDialog()
{
	WORD fVirt;
	WORD key;
	stringstream ss(m_pComp->GetConfiguration());

	ss >> fVirt >> key >> m_bGlobal;
	key &= 0xff;

	m_bControl = ((fVirt & FCONTROL) != 0);
	m_bAlt =     ((fVirt & FALT) != 0);
	m_bShift =   ((fVirt & FSHIFT) != 0);

	CCSRootDlg::OnInitDialog();
	
	for (LONG index = 0; index < 0xff; index++)
	{
		if (m_infoVk[index].state == NORM)
		{
			m_cbVirtualKey.AddString(m_infoVk[index].name);
		}
	}

	if (key == 0 || m_infoVk[key].state == ESTP)
	{
		m_cbVirtualKey.SelectString(0, m_infoVk['S'].name);
	}
	else
	{
		if (m_cbVirtualKey.FindString(0, m_infoVk[key].name) < 0)
		{
			m_cbVirtualKey.AddString(m_infoVk[key].name);
		}
		m_cbVirtualKey.SelectString(0, m_infoVk[key].name);
	}

	return TRUE; 
}

void compdlg::CCSAccelDlg::OnOK()
{
	UpdateData(TRUE);
	
	BYTE fVirt;
	WORD key = 0;
	fVirt = FNOINVERT | FVIRTKEY;
	if (m_bControl) fVirt |= FCONTROL;
	if (m_bAlt)     fVirt |= FALT;
	if (m_bShift)   fVirt |= FSHIFT;

	CString str;
	m_cbVirtualKey.GetLBText(m_cbVirtualKey.GetCurSel(), str);
	for (WORD index = 0; index < 0xff; index++)
	{
		if (str.Compare(m_infoVk[index].name) == 0)
		{
			key = index;
			break;
		}
	}

	char *pszShortName = strchr(m_infoVk[key].name, ':');
	if (pszShortName == NULL)
	{
		pszShortName = m_infoVk[key].name;
	}
	else
	{
		pszShortName++;
	}

	stringstream ss;
	ss << (int)fVirt << " " << key << " " << m_bGlobal;
	if (m_bControl) ss << " Ctrl +";
	if (m_bAlt)     ss << " Alt +";
	if (m_bShift)   ss << " Shift +";
	ss << " " << pszShortName;

	m_pComp->Configure(ss.str());

	CCSRootDlg::OnOK();
}

BOOL compdlg::CCSAccelDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN || pMsg->message == WM_SYSKEYDOWN)
//	if (pMsg->message >= WM_KEYFIRST && pMsg->message <= WM_KEYLAST)
	{
		if (pMsg->wParam <= 0xff)
		{
			// key
			size_t key = pMsg->wParam;
			if (m_infoVk[key].state != ESTP)
			{
				if (m_cbVirtualKey.FindString(0, m_infoVk[key].name) < 0)
				{
					m_cbVirtualKey.AddString(m_infoVk[key].name);
				}
				m_cbVirtualKey.ShowDropDown(FALSE);
				m_cbVirtualKey.SelectString(0, m_infoVk[key].name);
			}

			// control/alt/shift
			m_bControl = ((GetKeyState(VK_CONTROL) & 0x8000) != 0);
			m_bAlt =     ((GetKeyState(VK_MENU)    & 0x8000) != 0);
			m_bShift =   ((GetKeyState(VK_SHIFT)   & 0x8000) != 0);
			UpdateData(FALSE);

			return TRUE;
		}
	}
	return CCSRootDlg::PreTranslateMessage(pMsg);
}
