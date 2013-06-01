// Helper.h: interface for the CHelper class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HELPER_H__0D64292D_F766_4F6D_B345_9729362251F5__INCLUDED_)
#define AFX_HELPER_H__0D64292D_F766_4F6D_B345_9729362251F5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>

namespace helper
{
	// 窗口函数
	CRect GetDlgItemRect(CWnd *pWnd, UINT nID);

	CString GetFileTitle(LPCTSTR szFilePathname);
	BOOL GetProfileBinary(LPCTSTR lpszSection, LPCTSTR lpszEntry,
		LPBYTE pData, const LPBYTE pDefault, UINT uSize);

	const char * RemoveLeadingSpaces(char * str);
	CString ErrnoToString(DWORD dwErr);
	CHARFORMAT CF(LONG yHeight, DWORD dwEffects, COLORREF crTextColor, BYTE bCharSet, BYTE bPitchAndFamily, LPCTSTR pszFaceName);

    const char * SWPath(const char * pszSubPath = NULL, const char * pszSubPath2 = NULL);
	// 取得Stirng Table里的nIDS对应的字符串
	LPCTSTR IDS(UINT nIDS);
	time_t GetTimet(const CTime& ctm);
	char * tstrncpy(char *dest, const char *src, int len);
	
	CString GetATempFile();

	BOOL WriteFormattedStr(CRichEditCtrl& rec, LPCTSTR pszText, CHARFORMAT& cf);
	
	template <int size>	char * public_buffer()
	{
		static char buf[size];
		return buf;
	}

	void ShowContextHelp(HELPINFO *pHi);
	BOOL HavingChineseChar(const char *str);

	// 返回文件中行数
	long FileLine(LPCTSTR pszFile);

	BOOL DumpResourceToFile(LPCSTR lpName, LPCSTR lpType, LPCSTR lpFile);
};

#endif // !defined(AFX_HELPER_H__0D64292D_F766_4F6D_B345_9729362251F5__INCLUDED_)
