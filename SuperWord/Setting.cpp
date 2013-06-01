// Setting.cpp: implementation of the Setting class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SuperWord.h"
#include "Setting.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Setting::Setting()
{

}

Setting::~Setting()
{

}

Setting& Setting::operator = (const Setting& set)
{
	memcpy((LPBYTE)this + 4, (LPBYTE)&set + 4, ObjSize() - 4);
	return *this;
}

BOOL Setting::operator == (const Setting& set) const
{
	return memcmp((LPBYTE)this + 4, (LPBYTE)&set + 4, ObjSize() - 4) == 0;
}

BOOL Setting::operator != (const Setting& set) const
{
	return ! operator==(set);
}

CString Setting::GetProfileString(UINT nIDSection, UINT nIDKey, LPCSTR pszFile /* = NULL */)
{
	if (pszFile != NULL)
	{
		CString tmp;
		::GetPrivateProfileString(LoadIDS(nIDSection), LoadIDS(nIDKey), _T(""), tmp.GetBuffer(256), 256, pszFile);
		tmp.ReleaseBuffer();
		return tmp;
	}
	else
	{
		CWinApp *pApp = AfxGetApp();
		return pApp->GetProfileString(LoadIDS(nIDSection), LoadIDS(nIDKey), _T(""));
	}
}

BOOL Setting::SetProfileString(UINT nIDSection, UINT nIDKey, LPCSTR lpString, LPCSTR pszFile /* = NULL */)
{
	if (pszFile != NULL)
	{
		return ::WritePrivateProfileString(LoadIDS(nIDSection), LoadIDS(nIDKey), lpString, pszFile);
	}
	else
	{
		CWinApp *pApp = AfxGetApp();
		return pApp->WriteProfileString(LoadIDS(nIDSection), LoadIDS(nIDKey), lpString);
	}
}

UINT Setting::GetProfileInt(UINT nIDSection, UINT nIDKey, LPCSTR pszFile /* = NULL */)
{
	if (pszFile != NULL)
	{
		return ::GetPrivateProfileInt(LoadIDS(nIDSection), LoadIDS(nIDKey), 0, pszFile);
	}
	else
	{
		CWinApp *pApp = AfxGetApp();
		return pApp->GetProfileInt(LoadIDS(nIDSection), LoadIDS(nIDKey), 0);
	}
}

BOOL Setting::SetProfileInt(UINT nIDSection, UINT nIDKey, int nVal, LPCSTR pszFile /* = NULL */)
{
	if (pszFile != NULL)
	{
		CString tmp;
		tmp.CString::Format(_T("%d"), nVal);
		return ::WritePrivateProfileString(LoadIDS(nIDSection), LoadIDS(nIDKey), tmp, pszFile);
	}
	else
	{
		CWinApp *pApp = AfxGetApp();
		return pApp->WriteProfileInt(LoadIDS(nIDSection), LoadIDS(nIDKey), nVal);
	}
}

BOOL Setting::LoadSetting(LPCTSTR strSection, LPCTSTR strKey, LPCTSTR pszFile /* = NULL */)
{
	BYTE buf[4096];
	char sz[4096];

	if (pszFile != NULL)
	{
		::GetPrivateProfileString(strSection, strKey, "", sz, 4096, pszFile);
		if (sz[0] == '\0') return FALSE;

		Str2Buf(sz, buf, 4096);
		memcpy((LPBYTE)this + 4, buf, ObjSize() - 4);
	}
	else
	{
		CWinApp *pApp = AfxGetApp();
		CString str = pApp->GetProfileString(strSection, strKey, _T(""));
		if (str.GetLength() == 0) return FALSE;

		Str2Buf(str, buf, 4096);
		memcpy((LPBYTE)this + 4, buf, ObjSize() - 4);
	}
	return TRUE;
}

BOOL Setting::SaveSetting(LPCTSTR strSection, LPCTSTR strKey, LPCTSTR pszFile /* = NULL */)
{
	if (pszFile != NULL)
	{
		::WritePrivateProfileString(strSection, strKey, 
			Buf2Str((LPBYTE)this + 4, ObjSize() - 4), pszFile);
	}
	else
	{
		CWinApp *pApp = AfxGetApp();
		pApp->WriteProfileString(strSection, strKey, //"dfsafdasf");
			Buf2Str((LPBYTE)this + 4, ObjSize() - 4));
	}
	return TRUE;
}

CString Setting::Buf2Str(LPCVOID pBuf, int size)
{
	ASSERT(pBuf != NULL);

	char hex[3];
	CString strRet;
	const BYTE * p = (const BYTE *)pBuf;

	for (int i = 0; i < size; i++)
	{
		sprintf(hex, "%02x", p[i]);
		strRet += hex;
	}

	return strRet;
}

void Setting::Str2Buf(LPCSTR psz, LPVOID pBuf, int size)
{
	ASSERT(psz != NULL && pBuf != NULL);

	BYTE *p = (BYTE *)pBuf;
	char hex[3];
	for (; *psz && --size; psz += 2, p++)
	{
		helper::tstrncpy(hex, psz, 2);
		sscanf(hex, "%02x", p);
	}

	*p = '\0';
}

CString Setting::LoadIDS(UINT nID)
{
	CString tmp;
	tmp.LoadString(nID);
	return tmp;
}
