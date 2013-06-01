// SuperWordDlg.cpp : implementation file
//
#include "stdafx.h"

#include "SuperWord.h"
#include "AboutDlg.h"
#include "SuperWordDlg.h"
#include "CompositeCreator.h"
#include "OptionSheet.h"
#include "WordtypeDlg.h"
#include "ReciteSchemeDlg.h"
#include "GlobalCmdSetDlg.h"
#include "Word.h"
#include "WordType.h"

#include <algorithm>
#include <fstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace comp;
using namespace std;
using namespace helper;

#define IDTIMER_SHOW_WORD 			1000
#define IDTIMER_SHOW_MEANING 		1001
#define IDTIMER_MOVE_NEXT           1002
#define IDTIMER_MARK_ACCESSTIME		1003
#define IDTIMER_TIMERCMD_BEGIN      2000
#define IDTIMER_TIMERCMD_END        2999

#define ID_HOTKEYCMD_BEGIN          3000
#define ID_HOTKEYCMD_END            3999

/////////////////////////////////////////////////////////////////////////////
// CSuperWordDlg dialog

CSuperWordDlg::CSuperWordDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSuperWordDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSuperWordDlg)
	m_strPractice = _T("");
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    m_hAccelGUserHotkey = NULL;
	m_hAccelWUserHotkey = NULL;
	m_pSet = GlobalSetting::Instance();
	m_pw = NULL;

	m_mapSetColorCmd.insert(SetColorCmdMap::value_type("单词", &CSuperWordDlg::SetWordColor));
	m_mapSetColorCmd.insert(SetColorCmdMap::value_type("单词背景", &CSuperWordDlg::SetWordBkColor));

	m_mapOpenDlg.insert(ActionMap::value_type("选项对话框", &CSuperWordDlg::OnOption));
	m_mapOpenDlg.insert(ActionMap::value_type("单词属性对话框", &CSuperWordDlg::OnManageWordtype));
	m_mapOpenDlg.insert(ActionMap::value_type("背诵方案对话框", &CSuperWordDlg::OnSetReciteScheme));

	m_mapShowElementCmd.insert(ShowElementCmdMap::value_type("单词", &CSuperWordDlg::ShowWord));
	m_mapShowElementCmd.insert(ShowElementCmdMap::value_type("汉意", &CSuperWordDlg::ShowMeaning));

	m_mapMiscCmd.insert(ActionMap::value_type("设置单词的访问时间", &CSuperWordDlg::OnSetAccessTime));
	m_mapMiscCmd.insert(ActionMap::value_type("取消单词的访问时间", &CSuperWordDlg::OnUnsetAccessTime));
	m_mapMiscCmd.insert(ActionMap::value_type("切换单词的访问时间", &CSuperWordDlg::OnToogleAccessTime));
	m_mapMiscCmd.insert(ActionMap::value_type("显示默写结果", &CSuperWordDlg::ShowPracticeResult));

	m_mapMiscConditionCmd.insert(MiscConditionCmdMap::value_type("用户默写正确", &CSuperWordDlg::CheckPractice));
}

CSuperWordDlg::~CSuperWordDlg()
{
	if (m_hAccelGUserHotkey != NULL)
	{
		::DestroyAcceleratorTable(m_hAccelGUserHotkey);
		m_hAccelGUserHotkey = NULL;
	}
	if (m_hAccelWUserHotkey != NULL)
	{
		::DestroyAcceleratorTable(m_hAccelWUserHotkey);
		m_hAccelWUserHotkey = NULL;
	}
}

void CSuperWordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSuperWordDlg)
	DDX_Control(pDX, IDC_PROGRESS, m_pgWord);
	DDX_Control(pDX, IDC_ACCESS_DATE, m_dtAccess);
	DDX_Control(pDX, IDC_BTN_MENU, m_btnMenu);
	DDX_Control(pDX, IDC_WORDTYPE, m_wndWordType);
	DDX_Control(pDX, IDC_RICHEDIT_PRACTISE, m_rdPractice);
	DDX_Control(pDX, IDC_RICHEDIT_WORD, m_rdWord);
	DDX_Text(pDX, IDC_RICHEDIT_PRACTISE, m_strPractice);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_PROGRESS, m_pgWord);
}

void CSuperWordDlg::RenewRichEditStyles()
{
	// 练习窗口
	m_pSet->Cf.cfPractise.crTextColor = m_pSet->Cr.crPractise;
	m_rdPractice.SetDefaultCharFormat(m_pSet->Cf.cfPractise);
	m_rdPractice.SetBackgroundColor(FALSE, m_pSet->Cr.crPractiseBk);
	// 单词窗口
	m_pSet->Cf.cfWord.crTextColor = m_pSet->Cr.crWord;
	m_rdWord.SetDefaultCharFormat(m_pSet->Cf.cfWord);
	m_rdWord.SetBackgroundColor(FALSE, m_pSet->Cr.crWordBk);
	// 解释窗口
	m_pSet->Cf.cfPhonetic.crTextColor = m_pSet->Cr.crPhonetic;
	m_pSet->Cf.cfMeaning.crTextColor = m_pSet->Cr.crMeaning;

	m_rdPractice.SetEventMask(ENM_KEYEVENTS | ENM_CHANGE);
	m_rdWord.SetEventMask(ENM_MOUSEEVENTS);
}

void CSuperWordDlg::SetChildColors()
{
	m_htmlMeaing.SetColors(m_pSet->Cr.crMeaningBk, m_pSet->Cr.crMeaning, m_pSet->Cr.crPhonetic);
	m_wndWordType.SetColors(m_pSet->Cr.crWordTypeBorder, m_pSet->Cr.crWordTypeActive, m_pSet->Cr.crWordTypeInactive);
	m_dtAccess.SetColor(m_pSet->Cr.crAccesstimeBk, m_pSet->Cr.crAccesstime);
	m_pgWord.SetStartColor(m_pSet->Cr.crProgress1);
	m_pgWord.SetEndColor(m_pSet->Cr.crProgress2);
	m_pgWord.SetBkColor(m_pSet->Cr.crProgressBk);
	m_pgWord.SetTextColor(m_pSet->Cr.crProgressFont);
}

void CSuperWordDlg::ChangeRicheditColors()
{
	RenewRichEditStyles();
	if (m_rdWord.GetTextLength() > 0)
		ShowWord(true);
//	if (m_rdMeaning.GetTextLength() > 0)
		ShowMeaning(true);
}

void CSuperWordDlg::ShowWord(bool bShow)
{
	m_rdWord.SetWindowText(bShow ? m_pw->word() : "");
	m_rdWord.UpdateWindow();
}

void CSuperWordDlg::ShowMeaning(bool bShow)
{
	NullWord nw;
	m_htmlMeaing.ShowMeaning(bShow? m_pw : &nw);
}

void CSuperWordDlg::ShowAccesstime(time_t tt)
{
	m_dtAccess.SetTime(tt);
}

void CSuperWordDlg::ShowPracticeResult()
{
	CRect rc;
	BOOL bRet = CheckPractice();
	m_rdPractice.GetWindowRect(&rc);
	m_prDlg.ShowPractiseResult(rc.BottomRight(), bRet ? SPR_RIGHT : SPR_WRONG);	
}

bool CSuperWordDlg::CheckPractice()
{
	return (m_strPractice.CompareNoCase(m_pw->word()) == 0);
}

void CSuperWordDlg::RestartRecite()
{
	m_pw = m_wm.MoveFirst();
	m_pgWord.SetRange(0, static_cast<int>(m_wm.WordCount()));
	StartWordRecite();
}

void CSuperWordDlg::StartWordRecite()
{
	ResetElementsColor();

	m_pgWord.SetPos(static_cast<int>(m_wm.GetCurrentPos()));
	m_pgWord.RedrawWindow();

	// 练习窗口的字符要先清掉
	// 因为练习窗口的内容改变时,练习窗口会收到一个EditChange的消息
	// 而在收到此消息后如果练习窗口为空,就显示单词,这是一个特定的风格
	// 但有时单词并不是一开始就显示出来(比如用户按tab键才显示单词)
	// 这时如果在切换单词时练习窗口的内容非空,将练习窗口内容置空的话就会显示单词
	m_rdPractice.SetWindowText(_T(""));
	m_rdWord.SetWindowText(_T(""));
	NullWord nw;
	m_htmlMeaing.ShowMeaning(&nw);
	m_prDlg.ShowWindow(SW_HIDE);

	ShowAccesstime(m_pw->access_time());
	m_wndWordType.SetWordType(m_pw->type());

	ExecutePerwordCommand();
}

void CSuperWordDlg::ExecuteGlobalCommand()
{
	remove_if(m_listTimerCmdInfo.begin(), m_listTimerCmdInfo.end(),
		CmdInfo::is_global_cmd);

	m_listGHotKeyCmdInfo.clear();
	if (m_hAccelGUserHotkey != NULL)
	{
		::DestroyAcceleratorTable(m_hAccelGUserHotkey);
		m_hAccelGUserHotkey = NULL;
	}

	cmd::Command * pCmd = CompositeCreator::GetGlobalCommand();
	if (pCmd != NULL) pCmd->Execute(this);
}

void CSuperWordDlg::ExecutePerwordCommand()
{
	m_listTimerCmdInfo.remove_if(CmdInfo::is_perword_cmd);

	m_listWHotKeyCmdInfo.clear();
	if (m_hAccelWUserHotkey != NULL)
	{
		::DestroyAcceleratorTable(m_hAccelWUserHotkey);
		m_hAccelWUserHotkey = NULL;
	}

	cmd::Command * pCmd = CompositeCreator::GetPerWordCommand();
	if (pCmd != NULL) pCmd->Execute(this);
}

void CSuperWordDlg::ResetElementsColor()
{
	SetWordColor(m_pSet->Cr.crWord);
	SetWordBkColor(m_pSet->Cr.crWordBk);
}

void CSuperWordDlg::SetWordColor(COLORREF cr)
{
	CHARFORMAT cf = m_pSet->Cf.cfWord;
	cf.crTextColor = cr;
	m_rdWord.SetDefaultCharFormat(cf);
}

void CSuperWordDlg::SetWordBkColor(COLORREF cr)
{
	m_rdWord.SetBackgroundColor(FALSE, cr);
}

bool CSuperWordDlg::SetWordType(size_t index, SetTypeStyle style)
{
	if (index >= WordType::Instance()->GetAllType().size())
	{
		return false;
	}

	WORD tp = m_pw->type();

	switch (style)
	{
	case add:
		tp |= (1 << index);
		break;
	case del:
		tp &= ~(1 << index);
		break;
	case toggle:
		tp ^= (1 << index);
	default:
		break;
	}

	m_pw->set_type(tp);
	m_wndWordType.SetWordType(tp);

	return true;
}

// interface from "NavagateWnd" ------------------------------------------------
// -----------------------------------------------------------------------------

bool CSuperWordDlg::CreateNavigate()
{
	/*
	Create(IDD_SuperWord_DIALOG);
	ShowWindow(SW_SHOW);
	UpdateWindow();
	*/
	DoModal();
	return true;
}

const Word * CSuperWordDlg::GetCurrentWord() const
{
    return m_pw;
}

bool CSuperWordDlg::MoveWord(MoveOp mo)
{
    UINT nIDCmd = 0;
    switch (mo)
    {
    case first: nIDCmd = IDC_FIRSTWORD; break;
    case last:  nIDCmd = IDC_LASTWORD; break;
    case prev:  nIDCmd = IDC_PREVWORD; break;
    case next:  nIDCmd = IDC_NEXTWORD; break;
    }

    if (nIDCmd != 0)
    {
        PostMessage(WM_COMMAND, nIDCmd);
    }

    return true;
}

bool CSuperWordDlg::GetColorElement(ColorElementArray& array)
{
	SetColorCmdMap::const_iterator ci;
	for (ci = m_mapSetColorCmd.begin(); ci != m_mapSetColorCmd.end(); ++ci)
	{
		array.push_back(ci->first);
	}

    return true;
}

bool CSuperWordDlg::SetColor(const string& color_element, unsigned long cr)
{
	SetColorCmdMap::const_iterator ci = m_mapSetColorCmd.find(color_element);
	if (ci != m_mapSetColorCmd.end())
	{
		(this->*(ci->second))(cr);
		return true;
	}

    return false;
}

bool CSuperWordDlg::GetDialogs(DlgNameArray& array)
{
	ActionMap::const_iterator ci;
	for (ci = m_mapOpenDlg.begin(); ci != m_mapOpenDlg.end(); ++ci)
	{
		array.push_back(ci->first);
	}

	return true;
}

bool CSuperWordDlg::OpenDialog(const std::string &dlg)
{
	ActionMap::const_iterator ci = m_mapOpenDlg.find(dlg);
	if (ci != m_mapOpenDlg.end())
	{
		(this->*(ci->second))();
		return true;
	}

	return false;
}

bool CSuperWordDlg::GetVisualElement(VisualElementArray &array)
{
	ShowElementCmdMap::const_iterator ci;
	for (ci = m_mapShowElementCmd.begin(); ci != m_mapShowElementCmd.end(); ++ci)
	{
		array.push_back(ci->first);
	}

	return true;
}

bool CSuperWordDlg::ShowElement(const string& visual_element, bool bShow)
{
	ShowElementCmdMap::const_iterator ci = m_mapShowElementCmd.find(visual_element);
	if (ci != m_mapShowElementCmd.end())
	{
		(this->*(ci->second))(bShow);
		return true;
	}

	return false;
}

bool CSuperWordDlg::GetMiscCommands(MiscCommandArray& array)
{
	ActionMap::const_iterator ci;
	for (ci = m_mapMiscCmd.begin(); ci != m_mapMiscCmd.end(); ++ci)
	{
		array.push_back(ci->first);
	}

	return true;
}

bool CSuperWordDlg::RunMiscCommand(const string& cmd)
{
	ActionMap::const_iterator ci = m_mapMiscCmd.find(cmd);
	if (ci != m_mapMiscCmd.end())
	{
		(this->*(ci->second))();
		return true;
	}

	return false;
}

bool CSuperWordDlg::GetMiscConditions(MiscConditionArray & array)
{
	MiscConditionCmdMap::const_iterator ci;
	for (ci = m_mapMiscConditionCmd.begin(); ci != m_mapMiscConditionCmd.end(); ++ci)
	{
		array.push_back(ci->first);
	}
	return true;
}

bool CSuperWordDlg::CheckMiscCondition(const std::string& cond)
{
	MiscConditionCmdMap::const_iterator ci = m_mapMiscConditionCmd.find(cond);
	if (ci != m_mapMiscConditionCmd.end())
	{
		return (this->*(ci->second))();
	}

	return false;
}

bool CSuperWordDlg::TimerExecute(unsigned long interval, size_t repeat_time, 
								 bool bGlobal, const cmd::Command * cmd)
{
    static UINT current_id = IDTIMER_TIMERCMD_BEGIN;

    TimerCmdInfo tci;
    tci.timer_id = current_id;
	tci.repeat_time = repeat_time;
	tci.global = bGlobal;
    tci.cmd = cmd;
    m_listTimerCmdInfo.push_back(tci);
    SetTimer(current_id, interval, NULL);

    current_id++;
    if (current_id > IDTIMER_TIMERCMD_END) current_id = IDTIMER_TIMERCMD_BEGIN;

    return true;
}

bool CSuperWordDlg::RegHotKey(ACCEL acl, bool bGlobal, const cmd::Command * cmd)
{
    static WORD idCmd = ID_HOTKEYCMD_BEGIN;
	static ACCEL aclBuf[1024];

	HACCEL *pAcl = bGlobal ? &m_hAccelGUserHotkey : &m_hAccelWUserHotkey;
	HotkeyCmdInfoList * pList = bGlobal? &m_listGHotKeyCmdInfo : &m_listWHotKeyCmdInfo;
    
    HotkeyCmdInfo hci;
    hci.acl = acl;
    hci.acl.cmd = idCmd;
    hci.cmd = cmd;
	hci.global = bGlobal;
    pList->push_back(hci);

	int sz = 0;
	HotkeyCmdInfoList::const_iterator ci = pList->begin();
	for (; ci != pList->end() && sz < sizeof(aclBuf) / sizeof(ACCEL); ++ci)
	{
		aclBuf[sz++] = ci->acl;
	}
	if (sz > 0)
	{
		if (*pAcl == NULL) ::DestroyAcceleratorTable(*pAcl);
		*pAcl = ::CreateAcceleratorTable(aclBuf, sz);
	}

    idCmd++;
    if (idCmd > ID_HOTKEYCMD_END) idCmd = ID_HOTKEYCMD_BEGIN;

    return true;
}

bool CSuperWordDlg::LoadComposite(const string& comp_file)
{
	RootComposite comp(unknown);
	ifstream ifs(comp_file.c_str());
	ofstream ofsFilter(SWPath(IDS(IDSFN_WORD_FILTER)));
	ofstream ofsGCmd(SWPath(IDS(IDSFN_GLOBAL_CMD)));
	ofstream ofsWCmd(SWPath(IDS(IDSFN_WORD_CMD)));
	if (!ifs || !ofsFilter || !ofsGCmd || !ofsWCmd)
	{
		return false;
	}

	comp.Read(ifs);
	comp.Save(ofsFilter);

	comp.Read(ifs);
	comp.Save(ofsGCmd);

	comp.Read(ifs);
	comp.Save(ofsWCmd);

	ofsFilter.close();
	ofsGCmd.close();
	ofsWCmd.close();

	ExecuteGlobalCommand();

	m_wm.ReFilterWords();
	RestartRecite();

	return true;
}

BEGIN_MESSAGE_MAP(CSuperWordDlg, CDialog)
	//{{AFX_MSG_MAP(CSuperWordDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(IDC_NEXTWORD, OnNextword)
	ON_COMMAND(IDC_PREVWORD, OnPrevword)
	ON_EN_CHANGE(IDC_RICHEDIT_PRACTISE, OnChangeRicheditPractise)
	ON_NOTIFY(EN_MSGFILTER, IDC_RICHEDIT_PRACTISE, OnMsgfilterRicheditPractise)
//	ON_NOTIFY(EN_MSGFILTER, IDC_RICHEDIT_WORD, OnMsgfilterRicheditWord)
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_WM_CREATE()
	ON_COMMAND(ID_OPTION, OnOption)
	ON_COMMAND(ID_MANAGE_WORDTYPE, OnManageWordtype)
	ON_BN_CLICKED(IDC_BTN_MENU, OnBtnMenu)
	ON_COMMAND(ID_RESET_COLORS, OnResetColors)
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_HELP, OnHelp)
	ON_COMMAND(ID_TOGGLE_WORD_DETAIL_MEANING, OnToggleWordDetailMeaning)
	ON_COMMAND(IDC_FIRSTWORD, OnFirstword)
	ON_COMMAND(IDC_LASTWORD, OnLastword)
	//}}AFX_MSG_MAP
	ON_COMMAND_RANGE(IDC_TOGGLE_WORDTYPE_1, IDC_TOGGLE_WORDTYPE_1 + 15, OnToggleWordType)
    ON_COMMAND_RANGE(ID_HOTKEYCMD_BEGIN, ID_HOTKEYCMD_END, OnUserHotkey)
	ON_MESSAGE(WM_TRANSLATE_ACCEL, OnTranslateAccel)
	ON_WM_DESTROY()
	ON_COMMAND(ID_SET_RECITE_SCHEME, OnSetReciteScheme)
    ON_COMMAND(ID_SET_GLOBAL_CMD, &CSuperWordDlg::OnSetGlobalCmd)
    ON_COMMAND(ID_TOOGLE_ACCESS_TIME, &CSuperWordDlg::OnToogleAccessTime)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSuperWordDlg message handlers

BOOL CSuperWordDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	if (!m_pSet->Ms.bShowPractiseWnd)
	{
		CWnd *pPractice = GetDlgItem(IDC_RICHEDIT_PRACTISE);
		pPractice->ShowWindow(SW_HIDE);
		CRect rc;
		GetWindowRect(&rc);
		CRect rcReduce;
		pPractice->GetWindowRect(&rcReduce);
		rc.bottom -= rcReduce.Height() + 3;
		MoveWindow(&rc);
	}
	
	// 设置所有子窗口的重定位信息
	CResizableStyle::CreateDecorator(this);
	SetDlgItemResizeInfo(IDC_RICHEDIT_WORD, WRS_LEFT | WRS_RIGHT);
	SetDlgItemResizeInfo(IDC_WORDTYPE, WRS_RIGHT);
	SetDlgItemResizeInfo(IDC_HTML_MEANING, WRS_SYNWIDTH | WRS_SYNHEIGHT);
	SetDlgItemResizeInfo(IDC_RICHEDIT_PRACTISE, WRS_SYNWIDTH | WRS_BOTTOM);
	SetDlgItemResizeInfo(IDC_PROGRESS, WRS_SYNWIDTH | WRS_BOTTOM);
	SetDlgItemResizeInfo(IDC_ACCESS_DATE, WRS_RIGHT | WRS_BOTTOM);
	SetDlgItemResizeInfo(IDC_BTN_MENU, WRS_RIGHT | WRS_BOTTOM);

	// 其它控件
	m_pgWord.ShowPercent();

	SetChildColors();

	RenewRichEditStyles();

	m_btnMenu.SetBitmaps(IDB_MENU, RGB(192, 192, 192), IDB_MENU_SMALL, RGB(192, 192, 192));
	m_btnMenu.DrawBorder(FALSE);
	m_btnMenu.DrawTransparent();

	// 窗口
//	CTopableStyle::CreateDecorator(this);
	if (m_pSet->Ws.wndplMain.length > 0)
	{
		SetWindowPlacement(&m_pSet->Ws.wndplMain);
	}

	m_htmlMeaing.CreateFromStatic(IDC_HTML_MEANING, this);
	m_htmlMeaing.SetSilent(TRUE);

	ExecuteGlobalCommand();

	RestartRecite();
	
	return FALSE;
}

void CSuperWordDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

void CSuperWordDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this);

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CSuperWordDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSuperWordDlg::OnNextword() 
{
	if (m_wm.IsLast()) return;
	m_pw = m_wm.MoveNext();
	StartWordRecite();
}
void CSuperWordDlg::OnPrevword() 
{
	if (m_wm.IsFirst()) return;
	m_pw = m_wm.MovePrev();
	StartWordRecite();
}
void CSuperWordDlg::OnFirstword() 
{
	if (m_wm.IsFirst()) return;
	m_pw = m_wm.MoveFirst();
	StartWordRecite();
}
void CSuperWordDlg::OnLastword() 
{
	if (m_wm.IsLast()) return;
	m_pw = m_wm.MoveLast();
	StartWordRecite();
}

BOOL CSuperWordDlg::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message >= WM_MOUSEFIRST && pMsg->message <= WM_MOUSELAST)
	{
//		m_prDlg.ShowWindow(SW_HIDE);
	}
	
	if (pMsg->message >= WM_KEYFIRST && pMsg->message <= WM_KEYLAST)
	{
		if (OnTranslateAccel(0, (LPARAM)pMsg) == TRUE)
			return TRUE;
	}

	return CDialog::PreTranslateMessage(pMsg);
}

void CSuperWordDlg::OnOK() 
{
}

// OnChangeRicheditPratise
// 在练习窗口内容发生变化时调用,目的是:
//	当用户在练习窗口输入第一个字符时, 隐藏单词窗口的内容
//	当练习窗口为空时, 显示单词窗口内容
void CSuperWordDlg::OnChangeRicheditPractise() 
{
	UpdateData();
	if (m_strPractice.GetLength())
		m_rdWord.SetWindowText(_T(""));
	else
		m_rdWord.SetWindowText(m_pw->word());
}

void CSuperWordDlg::OnMsgfilterRicheditPractise(NMHDR* pNMHDR, LRESULT* pResult) 
{
	MSGFILTER *pMsgFilter = reinterpret_cast<MSGFILTER *>(pNMHDR);
	// 在练习窗口按回车
	/*
	if (pMsgFilter->msg == WM_KEYUP && pMsgFilter->wParam == VK_RETURN)
	{
		UpdateData();
		if (m_strPractice != _T(""))
		{
			if (m_strPractice[0] != '/')
			{
			}
			else
			{
				// 查词
				m_strPractice.TrimLeft('/');
				Word *pw = m_wm.QuerySpecial((LPCTSTR)m_strPractice);
				if (pw != NULL)
				{
					m_pw = pw;
					StartWordRecite();
				}
			}
		}
	}
	*/
	if (pMsgFilter->msg == WM_KEYDOWN && pMsgFilter->wParam == VK_SPACE)
	{
		// 按空格的话,如果当时练习窗口为空则到下一单词
		UpdateData();
		if (m_strPractice == _T(""))
		{
			PostMessage(WM_COMMAND, IDC_NEXTWORD);
		}
	}
	
	*pResult = 0;
}

void CSuperWordDlg::OnTimer(UINT nIDEvent) 
{
    // Deal with the TimerCommand
    if (nIDEvent >= IDTIMER_TIMERCMD_BEGIN && nIDEvent <= IDTIMER_TIMERCMD_END)
    {
		bool found = false;
		TimerCmdInfoList::iterator ci = m_listTimerCmdInfo.begin();
        for (; ci != m_listTimerCmdInfo.end(); ++ci)
        {
            if (ci->timer_id == nIDEvent)
            {
				found = true;
                ci->cmd->Execute(this);
				if (--(ci->repeat_time) == 0)
				{
					KillTimer(nIDEvent);
					m_listTimerCmdInfo.erase(ci);
				}
                break;
            }
        }
		// Delete corresponding timer if a cmd was deleted from Timercmd info list
		if (!found) 
		{
			KillTimer(nIDEvent);
		}
    }

	CDialog::OnTimer(nIDEvent);
}

void CSuperWordDlg::OnToggleWordType(UINT nID)
{
	SetWordType(nID - IDC_TOGGLE_WORDTYPE_1, toggle);
}

// 在关闭之前记录窗口位置
void CSuperWordDlg::OnClose() 
{
//	AfxPostQuitMessage(0);
	CRect rc;
	GetWindowPlacement(&m_pSet->Ws.wndplMain);
	CDialog::OnClose();
}

int CSuperWordDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_prDlg.Create(IDD_PRACTISE_RESULT_DLG, NULL);
	
	return 0;
}

void CSuperWordDlg::OnOption() 
{
	COptionSheet ps(_T("选项"), this, 0);
	ps.m_psh.dwFlags &= ~(PSH_HASHELP);

	const GlobalSetting *pOldSet = m_pSet->MarkRestorePoint();

	if (ps.DoModal() == IDOK)
	{
		if (m_pSet->Ms.dwWordOrder != pOldSet->Ms.dwWordOrder)
		{
			m_wm.SortWords(m_pSet->Ms.dwWordOrder);
			RestartRecite();
		}
		
		StartWordRecite();
	}
	else
	{
		m_pSet->Restore();
		
	}

	// 因为颜色有可能被用户在颜色设置中改变, 所以调用以保证颜色正确
	OnResetColors();
}

void CSuperWordDlg::OnManageWordtype() 
{
	CWordtypeDlg dlg;
	
	if (dlg.DoModal() == IDOK)
	{
		m_wndWordType.SetWordType(m_pw->type());
	}	
}

void CSuperWordDlg::OnBtnMenu() 
{
	CMenu mu;
	mu.LoadMenu(IDR_MAINMENU);
	CMenu *pMu = mu.GetSubMenu(0);

	POINT pt;
	::GetCursorPos(&pt);
	pMu->TrackPopupMenu(0, pt.x, pt.y, this);
}

void CSuperWordDlg::OnResetColors() 
{
	InvalidateRect(NULL);
	m_btnMenu.DrawTransparent(TRUE);
	SetChildColors();
	ChangeRicheditColors();
}

BOOL CSuperWordDlg::OnEraseBkgnd(CDC* pDC) 
{	
	CRect rc;
	GetClientRect(&rc);
	pDC->FillSolidRect(&rc, m_pSet->Cr.crDlgBk);

	return TRUE;
}

void CSuperWordDlg::OnHelp() 
{
	::ShellExecute(NULL, "open", helper::SWPath("SuperWord.chm"), NULL, NULL, SW_SHOW);
}

LRESULT CSuperWordDlg::OnTranslateAccel(WPARAM, LPARAM lp)
{
    if (::TranslateAccelerator(GetSafeHwnd(), m_hAccelGUserHotkey, (MSG *)lp))
	{
        return TRUE;
	}
	else if (::TranslateAccelerator(GetSafeHwnd(), m_hAccelWUserHotkey, (MSG *)lp))
	{
		return TRUE;
	}

	return FALSE;
}

void CSuperWordDlg::OnToggleWordDetailMeaning() 
{
	BOOL & bShowDetail = GlobalSetting::Instance()->Ms.bShowDetailedMeaning;
	bShowDetail = !bShowDetail;
	ShowMeaning(true);
}

void CSuperWordDlg::OnUserHotkey(UINT nID)
{
    HotkeyCmdInfoList::iterator ci;
	ci = m_listGHotKeyCmdInfo.begin();
    for (; ci != m_listGHotKeyCmdInfo.end(); ++ci)
    {
        if (ci->acl.cmd == nID)
        {
            ci->cmd->Execute(this);
            return;
        }
    }

	ci = m_listWHotKeyCmdInfo.begin();
	for (; ci != m_listWHotKeyCmdInfo.end(); ++ci)
	{
		if (ci->acl.cmd == nID)
		{
			ci->cmd->Execute(this);
			return;
		}
	}
}

void CSuperWordDlg::OnDestroy()
{
	m_prDlg.DestroyWindow();

	__super::OnDestroy();
}

void CSuperWordDlg::OnSetReciteScheme()
{
	CReciteSchemeDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		if (dlg.m_bFilterChanged)
		{
			m_wm.ReFilterWords();
			RestartRecite();
		}
		else if (dlg.m_bPerwordCmdChanged)
		{
			StartWordRecite();
		}
	}
}

void CSuperWordDlg::OnSetGlobalCmd()
{
	// TODO: Add your command handler code here
	CGlobalCmdSetDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		if (dlg.m_bGlobalCmdChanged)
		{
			ExecuteGlobalCommand();
		}
	}
}

void CSuperWordDlg::OnToogleAccessTime()
{
    if (m_pw->access_time() == 0)
    {
        m_pw->set_access_time(time(NULL));
    }
    else
    {
        m_pw->set_access_time(0);
    }
    ShowAccesstime(m_pw->access_time());
}

void CSuperWordDlg::OnSetAccessTime() 
{
    m_pw->set_access_time(time(NULL));
    ShowAccesstime(m_pw->access_time());
}
void CSuperWordDlg::OnUnsetAccessTime() 
{
    m_pw->set_access_time(0);
    ShowAccesstime(m_pw->access_time());
}
