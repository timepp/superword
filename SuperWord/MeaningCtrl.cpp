// MeaningCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "superword.h"
#include "MeaningCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



//////////////////////////////////////////////////////////////////////////
// CMyIEWnd
IMPLEMENT_DYNAMIC(CMyIEWnd, CWnd)
BEGIN_MESSAGE_MAP(CMyIEWnd, CWnd)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_RBUTTONDBLCLK()
END_MESSAGE_MAP()

void CMyIEWnd::OnRButtonUp(UINT nFlags, CPoint point)
{
	::SendMessage(m_hNotifywnd, WM_COMMAND, ID_TOGGLE_WORD_DETAIL_MEANING, 0);
}

void CMyIEWnd::OnRButtonDblClk(UINT nFlags, CPoint point)
{
}


void CMyIEWnd::SetNotifyWnd(HWND hWnd)
{
	m_hNotifywnd = hWnd;
}

void CMyIEWnd::OnContextMenu(CWnd* pWnd, CPoint pos)
{
}

BOOL CMyIEWnd::PreTranslateMessage(MSG *pMsg)
{
	if (pMsg->message >= WM_KEYFIRST && pMsg->message <= WM_KEYLAST)
	{
		pMsg->hwnd = m_hNotifywnd;
		::SendMessage(m_hNotifywnd, WM_TRANSLATE_ACCEL, 0, (LPARAM)pMsg);
		return TRUE;
	}
	return CWnd::PreTranslateMessage(pMsg);
}

/////////////////////////////////////////////////////////////////////////////
// CMeaningCtrl
WNDPROC CMeaningCtrl::s_oldWndProc = NULL;
HWND CMeaningCtrl::s_hWndParent;

CMeaningCtrl::CMeaningCtrl()
{
	LoadHtmlTemplate();
}

CString CMeaningCtrl::FormatHtmlColor(COLORREF cr)
{
	CString str;
	str.Format(_T("%02x%02x%02x"), GetRValue(cr), GetGValue(cr), GetBValue(cr));
	return str;
}

void CMeaningCtrl::Navigate3(LPCTSTR pszText)
{
	// 先把文本串写成一个文件, 然后调用Navigate2显示这个文件
	CString strFile = helper::SWPath(_T("meaning_temp.html"));
	Stop();
	
	CFile f;
	CFileException fe;
	if (!f.Open(strFile, CFile::modeCreate | CFile::modeWrite, &fe))
	{
		fe.ReportError();
		return;
	}

	f.Write(pszText, (UINT)_tcslen(pszText));
	f.Close();

	Navigate2(strFile);
}

void CMeaningCtrl::SetColors(COLORREF crBk, COLORREF crMeaning, COLORREF crPhonetic)
{
	m_strBk = FormatHtmlColor(crBk);
	m_strMeaning = FormatHtmlColor(crMeaning);
	m_strPhonetic = FormatHtmlColor(crPhonetic);
}

void CMeaningCtrl::ShowMeaning(const Word * pw)
{
	CString strHtml = m_strHtmlTemplate;
	CString strMeaning(pw->meaning());

	MainColor& mc = GlobalSetting::Instance()->Cr;
	strHtml.Replace(_T("背景颜色"), m_strBk);
	strHtml.Replace(_T("汉意颜色"), m_strMeaning);
	strHtml.Replace(_T("音标颜色"), m_strPhonetic);
	strHtml.Replace(_T("音标颜色"), m_strPhonetic);
	strHtml.Replace(_T("滚动条颜色"),      FormatHtmlColor(mc.crMsFace));
	strHtml.Replace(_T("滚动条高亮颜色"),  FormatHtmlColor(mc.crMsHighlight));
	strHtml.Replace(_T("滚动条阴影颜色"),  FormatHtmlColor(mc.crMsShadow));
	strHtml.Replace(_T("滚动条按钮颜色"),  FormatHtmlColor(mc.crMsArrow));
	strHtml.Replace(_T("滚动条基本颜色"),  FormatHtmlColor(mc.crMsBase));
	strHtml.Replace(_T("滚动条暗边框"),    FormatHtmlColor(mc.crMsDarkshadow));
	
	
	strHtml.Replace(_T("音标"), pw->phonetic());
	if (pw->phonetic()[0] == '\0')
	{
		strHtml.Replace(_T("["), _T(""));
		strHtml.Replace(_T("]<br>"), _T(""));
	}

	strHtml.Replace(_T("汉意"), strMeaning);

	if (strcmp(pw->word(), "lina") == 0)
	{
		HRSRC hrsRC = ::FindResource(NULL, MAKEINTRESOURCE(IDR_SCRIPT_FOR_LINA), _T("TXT"));
		HGLOBAL hGlobal = ::LoadResource(NULL, hrsRC);
		LPVOID pData = ::LockResource(hGlobal);
		DWORD dwLen = ::SizeofResource(NULL, hrsRC);
		TCHAR * pText = new TCHAR[dwLen + 1];
		memcpy(pText, pData, dwLen);
		pText[dwLen] = '\0';
		strHtml += pText;
		delete pText;

		COLORREF crBk = GlobalSetting::Instance()->Cr.crMeaningBk;
		int r = GetRValue(crBk);
		int g = GetGValue(crBk);
		int b = GetBValue(crBk);
		if (r + g + b > 384)
		{
			strHtml.Replace(_T("飘动词的颜色"), "000080");
		}
		else
		{
			strHtml.Replace(_T("飘动词的颜色"), "ffff00");
		}
	}

	Navigate3(strHtml);
}

void CMeaningCtrl::LoadHtmlTemplate()
{
	CString strFile = helper::SWPath(_T("MeaningTemplate.html"));
	CFile f;
	CFileException fe;
	if (!f.Open(strFile, CFile::modeRead | CFile::shareDenyNone, &fe))
	{
		fe.ReportError();
		return;
	}

	size_t dwLen = static_cast<size_t>(f.GetLength());
	TCHAR *pBuf = new TCHAR[dwLen + 1];
	f.Read(pBuf, dwLen);
	pBuf[dwLen] = '\0';
	m_strHtmlTemplate = pBuf;
	delete [] pBuf;

	f.Close();
}

#undef SubclassWindow

void CMeaningCtrl::OnNavigateComplete2(LPCTSTR strURL)
{
	HWND hwnd = GetBrowserWindow();
	if (!m_myIEWnd.m_hWnd) 
	{
		m_myIEWnd.SubclassWindow(hwnd);
		m_myIEWnd.SetNotifyWnd(::GetParent(m_hWnd));
	}
}