// SuperWord.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "SuperWord.h"
#include "SuperWordDlg.h"
#include "WordManager.h"
#include "AboutDlg.h"
#include "CSRootDlg.h"
#include "RgnDlg.h"
#include "GlobalSetting.h"
#include "HappyBirthdayDlg.h"
#include "NavigateWndCreator.h"
#include "TestDlg.h"
#include <locale>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSuperWordApp

BEGIN_MESSAGE_MAP(CSuperWordApp, CWinApp)
	//{{AFX_MSG_MAP(CSuperWordApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSuperWordApp construction

CSuperWordApp::CSuperWordApp()
{
	// fix bug: [VS2005] cannot open file if file path contains chinese chars.
	setlocale(LC_ALL, _T("chinese-simplified"));
}
CSuperWordApp::~CSuperWordApp()
{
	CString strFontFile = helper::SWPath(_T("font.ttf"));
	::RemoveFontResourceEx(strFontFile, FR_PRIVATE, NULL);
	::DeleteFile(strFontFile);
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CSuperWordApp object

CSuperWordApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CSuperWordApp initialization

BOOL CSuperWordApp::InitInstance()
{
	AfxInitRichEdit();
	SetRegistryKey(_T("Timepp soft"));

	PrepareEnv();

	CTime tm = CTime::GetCurrentTime();
	if (tm.GetMonth() == 2 && tm.GetDay() == 14)
	{
		CHappyBirthdayDlg hbdlg;
		hbdlg.DoModal();
	}

#if 1
	NavigateWndCreator * pCreator = NavigateWndCreator::Instance();
	NavigateWnd * pWnd = pCreator->GetCurrentNavigateWnd();
	m_pMainWnd = dynamic_cast<CWnd *>(pWnd);
	pWnd->CreateNavigate();
	return FALSE;
#else
	CSuperWordDlg dlg;
	dlg.DoModal();
	return FALSE;
#endif
}

// 如果一些关键文件丢失的话，就重建它们
void CSuperWordApp::PrepareEnv()
{
	::CreateDirectory(helper::SWPath("img"), NULL);
    ::CreateDirectory(helper::SWPath(helper::IDS(IDSP_COLOR_SCHEME)), NULL);
    ::CreateDirectory(helper::SWPath(helper::IDS(IDSP_WORD_CLASS)), NULL);
    ::CreateDirectory(helper::SWPath(helper::IDS(IDSP_WORD_FILTER)), NULL);
    ::CreateDirectory(helper::SWPath(helper::IDS(IDSP_WORD_CMD)), NULL);
    ::CreateDirectory(helper::SWPath(helper::IDS(IDSP_GLOBAL_CMD)), NULL);
    ::CreateDirectory(helper::SWPath(helper::IDS(IDSP_RECITE_SCHEME)), NULL);
	
	ReCreateFileIfMissing(_T("MeaningTemplate.html"), IDR_HTML_MEANING_TEMPLATE, RT_HTML);
	ReCreateFileIfMissing(_T("chk_right.bmp"), IDIMG_CHK_RIGHT, _T("IMAGE"));
	ReCreateFileIfMissing(_T("chk_wrong.bmp"), IDIMG_CHK_WRONG, _T("IMAGE"));
	ReCreateFileIfMissing(_T("img\\goldfish.bmp"), IDIMG_GOLD_FISH, _T("IMAGE"));
	ReCreateFileIfMissing(_T("img\\heart.gif"), IDIMG_HEART, _T("IMAGE"));

	// 注册字体
	ReCreateFileIfMissing(_T("font.ttf"), IDF_PHONETIC, _T("FONT_DATA"));
	::AddFontResourceEx(helper::SWPath("font.ttf"), FR_PRIVATE, NULL);
}

void CSuperWordApp::ReCreateFileIfMissing(LPCTSTR pszPath, UINT idResource, LPSTR lpType)
{
	CFileFind ff;

	CString strFile = helper::SWPath(pszPath); 
	if (!ff.FindFile(strFile))
	{
		helper::DumpResourceToFile(MAKEINTRESOURCE(idResource), lpType, strFile);
	}

    ff.Close();
}
