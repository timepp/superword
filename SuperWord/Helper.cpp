// Helper.cpp: implementation of the CHelper class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SuperWord.h"
#include "Helper.h"
#include <sstream>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRect helper::GetDlgItemRect(CWnd *pWnd, UINT nID)
{
	ASSERT_VALID(pWnd);

	CWnd *pChildWnd = pWnd->GetDlgItem(nID);
	ASSERT_VALID(pChildWnd);

	CRect rc;
	pChildWnd->GetWindowRect(&rc);
	pWnd->ScreenToClient(&rc);

	return rc;
}

// TODO : upgrade from socks5 code
CString helper::GetFileTitle(LPCTSTR szFilePathname)
{
	TCHAR szTitle[_MAX_FNAME];
	_tcscpy_s(szTitle, _tcsrchr(szFilePathname, '\\') + 1);
	const TCHAR * p = _tcsrchr(szTitle, '.');
	szTitle[p - szTitle] = '\0';
	return CString(szTitle);
}

BOOL helper::GetProfileBinary(LPCTSTR lpszSection, LPCTSTR lpszEntry,
	LPBYTE pData, const LPBYTE pDefault, UINT uSize)
{
	LPBYTE pTmpData;
	UINT uBytes;
	CWinApp *pApp = AfxGetApp();

	// 拷贝缺省值
	memcpy(pData, pDefault, uSize);

	if (pApp->GetProfileBinary(lpszSection, lpszEntry, &pTmpData, &uBytes))
	{
		memcpy(pData, pTmpData, uSize);
		delete [] pTmpData;
		return TRUE;
	}
	
	return FALSE;
}

const char * helper::RemoveLeadingSpaces(char * str)
{
	int i;
	for (i = 0; str[i] == ' ' || str[i] == '\t'; i++);
	memmove(str, str + i, strlen(str + i) + 1);
	return str;
}

// 得到last error的文字说明
CString helper::ErrnoToString(DWORD dwErr)
{
	TCHAR szErr[1024];
	::FormatMessage(
		FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, dwErr, 0,
		szErr, 1024, NULL);
	return CString(szErr);
}

CHARFORMAT helper::CF(LONG yHeight, DWORD dwEffects, COLORREF crTextColor, BYTE bCharSet, BYTE bPitchAndFamily, LPCTSTR pszFaceName)
{
	CHARFORMAT cf;
	cf.bCharSet = bCharSet;
	cf.bPitchAndFamily = bPitchAndFamily;
	cf.crTextColor = crTextColor;
	cf.yHeight = yHeight;
	cf.yOffset = 0;
	cf.cbSize = sizeof(CHARFORMAT);
	cf.dwEffects = dwEffects;
	_tcscpy_s(cf.szFaceName, pszFaceName);

	cf.dwMask = CFM_CHARSET | CFM_COLOR | CFM_FACE | CFM_SIZE;
	return cf;
}

// If the parameter pszSubDir == NULL, Get the directory where out program is.
// If the parameter pszSubDir != NULL, then get the sub directory of the program directory.
// There isn't a '\\' at the end of returned string.
const char * helper::SWPath(const char * pszSubPath /* = NULL */, 
							const char * pszSubPath2 /* = NULL */)
{
	static TCHAR szProgramDir[MAX_PATH] = "";
    TCHAR *p;
    static string str;
    stringstream ss;

    ::GetModuleFileName(NULL, szProgramDir, MAX_PATH);
	p = _tcsrchr(szProgramDir, '\\');
	*p = '\0';

    ss << szProgramDir;

    if (pszSubPath != NULL)
    {
		if (*pszSubPath != '\\')
		{
			ss << "\\";
		}
        ss << pszSubPath;
    }
	if (pszSubPath2 != NULL)
	{
		if (*pszSubPath2 != '\\')
		{
			ss << "\\";
		}
		ss << pszSubPath2;
	}

	str = ss.str();
    return str.c_str();
}

char * helper::tstrncpy(char *dest, const char *src, int len)
{
	strncpy(dest, src, len);
	dest[len] = '\0';
	return dest;
}

time_t helper::GetTimet(const CTime& ctm)
{
	struct tm stm;
	stm.tm_year = ctm.GetYear() - 1900;
	stm.tm_mon = ctm.GetMonth() - 1;
	stm.tm_mday = ctm.GetDay();
	stm.tm_hour = ctm.GetHour();
	stm.tm_min = ctm.GetMinute();
	stm.tm_sec = ctm.GetSecond();
	return mktime(&stm);
}

CString helper::GetATempFile()
{
	TCHAR szPath[MAX_PATH];
	TCHAR szFile[MAX_PATH];
	::GetTempPath(MAX_PATH, szPath);
	::GetTempFileName(szPath, _T("SuperWord"), 0, szFile);
	return CString(szFile);
}

LPCTSTR helper::IDS(UINT nIDS)
{
	static TCHAR sz[256];
	if (::LoadString(AfxGetInstanceHandle(), nIDS, sz, 256))
		return sz;
	else
		return NULL;
}

BOOL helper::WriteFormattedStr(CRichEditCtrl& rec, LPCTSTR pszText, CHARFORMAT& cf)
{
	long nSelStart, nSelEnd;
	// 得到选择区并替换
	rec.GetSel(nSelStart, nSelEnd);
	rec.ReplaceSel(pszText);
	//
	nSelEnd = nSelStart + (long)_tcslen(pszText);
	rec.SetSel(nSelStart, nSelEnd);
	rec.SetSelectionCharFormat(cf);

	rec.SetSel(nSelEnd, nSelEnd);
	rec.UpdateWindow();

	return TRUE;
}

void helper::ShowContextHelp(HELPINFO *pHi)
{
	CString str;
	if(str.LoadString(pHi->iCtrlId))
	{
		HH_POPUP hPop;
		memset(&hPop, 0, sizeof(hPop)); 
		
		hPop.cbStruct         = sizeof(hPop);        
		hPop.clrBackground    = (COLORREF)-1;
		hPop.clrForeground    = (COLORREF)-1;
		hPop.rcMargins        = CRect(-1, -1, -1, -1);
		hPop.pt               = pHi->MousePos;
		hPop.pszText          = str;
		hPop.pszFont          = NULL; // Font
		
		//HtmlHelp((HWND)pHi->hItemHandle, NULL, HH_DISPLAY_TEXT_POPUP, (DWORD)&hPop);
	}
}

BOOL helper::HavingChineseChar(const char *str)
{
	for (const char *p = str; *p; p++)
	{
		if (*p > 128 || *p < 0)
		{
			return TRUE;
		}
	}

	return FALSE;
}

long helper::FileLine(LPCTSTR pszFile)
{
	FILE * fp;
	if ((fp = fopen(pszFile, "rb")) == NULL)
	{
		return 0;
	}
	
	long line = 0;
	char buf[4096];
	while (!feof(fp))
	{
		size_t size = fread(buf, 1, 4095, fp);
		for (size_t i = 0; i < size; i++)
		{
			if (buf[i] == '\n') line++;
		}
	}

	fclose(fp);
	return line;
}

BOOL helper::DumpResourceToFile(LPCSTR lpName, LPCSTR lpType, LPCSTR lpFile)
{
	HRSRC hrsRC = ::FindResource(NULL, lpName, lpType);
	HGLOBAL hGlobal = ::LoadResource(NULL, hrsRC);
	LPVOID pData = ::LockResource(hGlobal);
	DWORD dwLen = ::SizeofResource(NULL, hrsRC);
	
	CFile f;
	CFileException e;
	if (!f.Open(lpFile, CFile::modeCreate | CFile::modeWrite, &e))
	{
		e.ReportError();
		return FALSE;
	}

	f.Write(pData, dwLen);
	f.Close();

	return TRUE;
}