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
	{ HIDE, "鼠标左键" },
	{ HIDE, "鼠标右键" },
	{ HIDE, "控制:中断(CTRL+BREAK)" },
	{ HIDE, "鼠标中键" },
	{ HIDE, "鼠标X1键" },
	{ HIDE, "鼠标X2键" },
	{ HIDE, "VK_7" },
	{ NORM, "特殊:Backspace" },
	{ NORM, "特殊:TAB" },
	{ HIDE, "VK_10" },
	{ HIDE, "VK_11" },
	{ NORM, "特殊:CLEAR" },
	{ NORM, "特殊:回车" },
	{ HIDE, "VK_14" },
	{ HIDE, "VK_15" },
// 0x10
	{ ESTP, "控制:Shift" },
	{ ESTP, "控制:Control" },
	{ ESTP, "控制:Alt" },
	{ NORM, "特殊:Pause(Break)" },
	{ NORM, "控制:Caps Lock" },
	{ HIDE, "IME-Kana模式" },
	{ HIDE, "VK_22" },
	{ HIDE, "IME-Junja模式" },
	{ HIDE, "IME-final模式" },
	{ HIDE, "IME-Hanja/Kanji模式" },
	{ HIDE, "VK_26" },
	{ NORM, "控制:Esc" },
	{ HIDE, "IME-Convert" },
	{ HIDE, "IME-No Convert" },
	{ HIDE, "IME-Accept" },
	{ HIDE, "IME-切换" },
// 0x20
	{ NORM, "空格" },
	{ NORM, "特殊:Page Up" },
	{ NORM, "特殊:Page Down" },
	{ NORM, "特殊:End" },
	{ NORM, "特殊:Home" },
	{ NORM, "特殊:Arrow Left" },
	{ NORM, "特殊:Arrow Up" },
	{ NORM, "特殊:Arrow Right" },
	{ NORM, "特殊:Arrow Down" },
	{ NORM, "扩展:Select" },
	{ NORM, "扩展:Print" },
	{ NORM, "扩展:Execute" },
	{ NORM, "控制:PrintScreen" },
	{ NORM, "特殊:Insert" },
	{ NORM, "特殊:Delete" },
	{ NORM, "扩展:Help" },
// 0x30
	{ NORM, "数字0" },
	{ NORM, "数字1" },
	{ NORM, "数字2" },
	{ NORM, "数字3" },
	{ NORM, "数字4" },
	{ NORM, "数字5" },
	{ NORM, "数字6" },
	{ NORM, "数字7" },
	{ NORM, "数字8" },
	{ NORM, "数字9" },
	{ HIDE, "VK_58" },
	{ HIDE, "VK_59" },
	{ HIDE, "VK_60" },
	{ HIDE, "VK_61" },
	{ HIDE, "VK_62" },
	{ HIDE, "VK_63" },
// 0x40
	{ HIDE, "VK_64" },
	{ NORM, "字母:A" },
	{ NORM, "字母:B" },
	{ NORM, "字母:C" },
	{ NORM, "字母:D" },
	{ NORM, "字母:E" },
	{ NORM, "字母:F" },
	{ NORM, "字母:G" },
	{ NORM, "字母:H" },
	{ NORM, "字母:I" },
	{ NORM, "字母:J" },
	{ NORM, "字母:K" },
	{ NORM, "字母:L" },
	{ NORM, "字母:M" },
	{ NORM, "字母:N" },
	{ NORM, "字母:O" },
// 0x50
	{ NORM, "字母:P" },
	{ NORM, "字母:Q" },
	{ NORM, "字母:R" },
	{ NORM, "字母:S" },
	{ NORM, "字母:T" },
	{ NORM, "字母:U" },
	{ NORM, "字母:V" },
	{ NORM, "字母:W" },
	{ NORM, "字母:X" },
	{ NORM, "字母:Y" },
	{ NORM, "字母:Z" },
	{ ESTP, "控制:左Windows" },
	{ ESTP, "控制:右Windows" },
	{ ESTP, "控制:Applications" },
	{ HIDE, "VK_94" },
	{ HIDE, "控制:Sleep" },
// 0x60
	{ NORM, "小键盘0" },
	{ NORM, "小键盘1" },
	{ NORM, "小键盘2" },
	{ NORM, "小键盘3" },
	{ NORM, "小键盘4" },
	{ NORM, "小键盘5" },
	{ NORM, "小键盘6" },
	{ NORM, "小键盘7" },
	{ NORM, "小键盘8" },
	{ NORM, "小键盘9" },
	{ NORM, "小键盘*" },
	{ NORM, "小键盘+" },
	{ NORM, "小键盘分隔符键" },
	{ NORM, "小键盘-" },
	{ NORM, "小键盘." },
	{ NORM, "小键盘/" },
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
	{ NORM, "控制:Num Lock" },
	{ NORM, "控制:Scroll Lock" },
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
	{ ESTP, "控制:左Shift" },
	{ ESTP, "控制:右Shift" },
	{ ESTP, "控制:左Control" },
	{ ESTP, "控制:右Control" },
	{ ESTP, "控制:左Alt" },
	{ ESTP, "控制:右Alt" },
	{ HIDE, "Browser-Back" },
	{ HIDE, "Browser-Forward" },
	{ HIDE, "Browser-Refresh" },
	{ HIDE, "Browser-Stop" },
	{ HIDE, "Browser-Search" },
	{ HIDE, "Browser-Favorite" },
	{ HIDE, "Browser-Home" },
	{ HIDE, "附加:静音" },
	{ HIDE, "附加:调小音量" },
	{ HIDE, "附加:调大音量" },
// 0xB0
	{ HIDE, "附加:下一曲目" },
	{ HIDE, "附加:前一曲目" },
	{ HIDE, "附加:停止播放" },
	{ HIDE, "附加:暂停播放" },
	{ HIDE, "附加:启动邮件(Start Mail)" },
	{ HIDE, "附加:启动媒体选择" },
	{ HIDE, "附加:启动程序1" },
	{ HIDE, "附加:启动程序2" },
	{ HIDE, "VK_184" },
	{ HIDE, "VK_185" },
	{ NORM, "标点:;" },
	{ NORM, "标点:=" },
	{ NORM, "标点:," },
	{ NORM, "标点:-" },
	{ NORM, "标点:." },
	{ NORM, "标点:/" },
// 0xC0
	{ NORM, "标点:`" },
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
	{ NORM, "标点:[" },
	{ NORM, "标点:\\" },
	{ NORM, "标点:]" },
	{ NORM, "标点:\'" },
	{ HIDE, "VK_223" },
// 0xE0
	{ HIDE, "VK_224" },
	{ HIDE, "VK_225" },
	{ NORM, "标点:(102键盘) , . 或 /" },
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
	{ NORM, "扩展:Attn" },
	{ NORM, "扩展:CrSel" },
	{ NORM, "扩展:ExSel" },
	{ NORM, "扩展:Erase EOF" },
	{ HIDE, "附加:播放" },
	{ NORM, "扩展:Zoom" },
	{ HIDE, "VK_252" },
	{ NORM, "扩展:PA1" },
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
