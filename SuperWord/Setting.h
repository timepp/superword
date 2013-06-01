 // Setting.h: interface for the CSetting class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SETTING_H__191D86E9_FD57_4CD3_8997_D97F8FDFCBBA__INCLUDED_)
#define AFX_SETTING_H__191D86E9_FD57_4CD3_8997_D97F8FDFCBBA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define IMPLEMENT_OBJSTORE() virtual int ObjSize() const { return sizeof(*this); }

struct Setting  
{
public:
	Setting();
	virtual ~Setting();

	Setting& operator = (const Setting& set);
	BOOL operator == (const Setting& set) const;
	BOOL operator != (const Setting& set) const;

	BOOL LoadSetting(LPCTSTR strSection, LPCTSTR strKey, LPCTSTR pszFile = NULL);
	BOOL SaveSetting(LPCTSTR strSection, LPCTSTR strKey, LPCTSTR pszFile = NULL);

	static CString GetProfileString(UINT nIDSection, UINT nIDKey, LPCSTR pszFile = NULL);
	static BOOL SetProfileString(UINT nIDSection, UINT nIDKey, LPCSTR lpString, LPCSTR pszFile = NULL);
	static UINT  GetProfileInt(UINT nIDSection, UINT nIDKey, LPCSTR pszFile = NULL);
	static BOOL  SetProfileInt(UINT nIDSection, UINT nIDKey, int nVal, LPCSTR pszFile = NULL);
	static inline CString LoadIDS(UINT nID);

protected:
	virtual int ObjSize() const = 0;
private:
	static CString Buf2Str(LPCVOID pBuf, int size);
	static void Str2Buf(LPCSTR psz, LPVOID pBuf, int size);
};

#endif // !defined(AFX_SETTING_H__191D86E9_FD57_4CD3_8997_D97F8FDFCBBA__INCLUDED_)
