#if !defined(AFX_MEANINGCTRL_H__5F4602E6_E814_4541_9A2D_D3F8B92F820A__INCLUDED_)
#define AFX_MEANINGCTRL_H__5F4602E6_E814_4541_9A2D_D3F8B92F820A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MeaningCtrl.h : header file
//
#include "Word.h"
#include "LibSrc/HtmlCtrl/HtmlCtrl.h"


#define WM_TRANSLATE_ACCEL		WM_USER+0x121

using word::Word;
/////////////////////////////////////////////////////////////////////////////
// CMeaningCtrl window
////////////////////////////
class CMyIEWnd : public CWnd {
public:
	CMyIEWnd() { }
	~CMyIEWnd() { }
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint pos);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);

	void SetNotifyWnd(HWND hWnd);
private:
	HWND m_hNotifywnd;

	DECLARE_MESSAGE_MAP();
	DECLARE_DYNAMIC(CMyIEWnd)
};

class CMeaningCtrl : public CHtmlCtrl
{
public:
	CMeaningCtrl();
	void ShowMeaning(const Word * pw);
	void SetColors(COLORREF crBk, COLORREF crMeaning, COLORREF crPhonetic);
	void SetWndprocHook();

private:
	void Navigate3(LPCTSTR pszText);
	void LoadHtmlTemplate();
	CString FormatHtmlColor(COLORREF cr);

	CString m_strBk, m_strMeaning, m_strPhonetic;
	CString m_strHtmlTemplate;
	static WNDPROC s_oldWndProc;
	static HWND s_hWndParent;

	CMyIEWnd m_myIEWnd;
	virtual void OnNavigateComplete2(LPCTSTR strURL);

	static LRESULT CALLBACK NewWndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MEANINGCTRL_H__5F4602E6_E814_4541_9A2D_D3F8B92F820A__INCLUDED_)
