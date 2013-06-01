#include <stdafx.h>
#include "resource.h"
#include "GlobalSetting.h"
#include "Helper.h"

//////////////////////////////////////////////////////////////////////////
// MainColor

MainColor::MainColor()
{
	// 缺省颜色
	const COLORREF CR_WHITE = RGB(255, 255, 255);
	crWord = CR_WHITE;
	crMeaning = CR_WHITE;
	crPractise = CR_WHITE;
	crPhonetic = CR_WHITE;
	crWordBk = 0;
	crPractiseBk = 0;
	crMeaningBk = 0;
	crDlgBk = ::GetSysColor(COLOR_3DFACE);
	crAccesstime = CR_WHITE;
	crAccesstimeBk = 0;
	crProgress1 = RGB(0, 0, 255);
	crProgress2 = RGB(255, 0, 0);
	crProgressBk = ::GetSysColor(COLOR_3DFACE);
	crProgressFont = CR_WHITE;
	crWordTypeActive = RGB(0, 255, 0);
	crWordTypeInactive = RGB(0, 128, 0);
	crWordTypeBorder = RGB(0, 0, 0);
	crMsBase = 0x000000;
	crMsShadow = 0x808080;
	crMsDarkshadow = 0x404040;
	crMsArrow = 0x000000;
	crMsFace = 0xc8d0d4;
	crMsHighlight = 0xffffff;
}

//////////////////////////////////////////////////////////////////////////
// GlobalSetting

GlobalSetting GlobalSetting::m_gsOld(TRUE);
BOOL GlobalSetting::m_bSaveInReg = FALSE;

GlobalSetting::GlobalSetting(BOOL bTemp /* = FALSE */)
{
	m_bTemp = bTemp;
	if (!m_bTemp)
	{
		Init();
		LoadSetting(m_bSaveInReg? NULL : helper::SWPath(helper::IDS(IDSFN_CFG)));
	}
}

GlobalSetting::~GlobalSetting()
{
	if (!m_bTemp)
	{
		SaveSetting(m_bSaveInReg? NULL : helper::SWPath(helper::IDS(IDSFN_CFG)));
	}
}

GlobalSetting * GlobalSetting::Instance()
{
	static GlobalSetting gSet;

	return &gSet;
}

GlobalSetting& GlobalSetting::operator =(GlobalSetting& gs)
{
	Cf = gs.Cf;
	Coo = gs.Coo;
	Cr = gs.Cr;
	Ms = gs.Ms;
	Ws = gs.Ws;

	return *this;
}

const GlobalSetting * GlobalSetting::MarkRestorePoint()
{
	m_gsOld = *Instance();

	return &m_gsOld;
}

void GlobalSetting::Restore()
{
	*Instance() = m_gsOld;
}

void GlobalSetting::Init()
{
	Coo.word.bTabbed = FALSE;
	Coo.word.uTimerDelay = 0;
	Coo.meaning.bTabbed = FALSE;
	Coo.meaning.uTimerDelay = 0;

	CHARFORMAT cf = 
	{
		sizeof(CHARFORMAT),
		CFM_SIZE | CFM_COLOR | CFM_FACE | CFM_CHARSET,
		0, 340, 0, RGB(255, 255, 255), 0,  34,  _T("Arial")
	};
	memcpy(&Cf.cfWord, &cf, sizeof(cf));
	memcpy(&Cf.cfMeaning, &cf, sizeof(cf));
	memcpy(&Cf.cfPhonetic, &cf, sizeof(cf));
	memcpy(&Cf.cfPractise, &cf, sizeof(cf));
	Cf.cfMeaning.yHeight = 240;
	Cf.cfPhonetic.bCharSet = 2;
	Cf.cfPhonetic.bPitchAndFamily = 2;
	Cf.cfPhonetic.yHeight = 320;
	_tcscpy_s(Cf.cfPhonetic.szFaceName, helper::IDS(IDS_PHONETIC_FONT_NAME));

	Ms.bShowPractiseWnd = TRUE;
	Ms.bShowDetailedMeaning = FALSE;
	Ms.dwWordOrder = WO_DESC | WO_BY_WORD;
	Ms.maMode = MAM_NERVER;

	memset(&Ws.wndplMain, 0, sizeof(Ws.wndplMain));
}



#define SECT_WORD_BROWSE			_T("单词浏览")
#define SECT_FACE_SET				_T("界面设置")
#define SECT_WINDOW					_T("窗口")
#define SECT_OTHER					_T("其它")

#define KEY_COO						_T("单词元素出现时机")
#define KEY_CF						_T("字体")
#define KEY_MC						_T("颜色")
#define KEY_WS						_T("窗口位置")
#define KEY_MS						_T("杂项")
#define KEY_ATTWT					_T("切换单词属性的加速键")

BOOL GlobalSetting::LoadSetting(const char * file)
{
	Coo.LoadSetting(SECT_WORD_BROWSE, KEY_COO, file);
	Cf.LoadSetting(SECT_FACE_SET, KEY_CF, file);
	Cr.LoadSetting(SECT_FACE_SET, KEY_MC, file);
	Ws.LoadSetting(SECT_WINDOW, KEY_WS, file);
	Ms.LoadSetting(SECT_OTHER, KEY_MS, file);
	
	return TRUE;
}

BOOL GlobalSetting::SaveSetting(const char * file)
{
	Coo.SaveSetting(SECT_WORD_BROWSE, KEY_COO, file);
	Cf.SaveSetting(SECT_FACE_SET, KEY_CF, file);
	Cr.SaveSetting(SECT_FACE_SET, KEY_MC, file);
	Ws.SaveSetting(SECT_WINDOW, KEY_WS, file);
	Ms.SaveSetting(SECT_OTHER, KEY_MS, file);

	return TRUE;
}