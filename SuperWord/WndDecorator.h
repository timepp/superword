// WndDecorator.h: interface for the CWndDecorator class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WNDDECORATOR_H__8D1A1F4A_BEE8_479B_82DE_603A7C2FEA05__INCLUDED_)
#define AFX_WNDDECORATOR_H__8D1A1F4A_BEE8_479B_82DE_603A7C2FEA05__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <set>
#include <map>

namespace decorate
{

#define RETURN_DEFAULT (-1)
#define DONT_CALL_OLD_PROC (-2)
// 所有修饰窗口类的基类

class CWndDecorator;

typedef std::set<CWndDecorator *> DecoratorSet;
struct DecoratorInfo
{
	WNDPROC oldWndProc;
	DecoratorSet dSet;
};

class CWndDecorator  
{
public:
	CWndDecorator();
	virtual ~CWndDecorator();

protected:
	// 窗口函数，子类实现
	virtual int WndProcBeforeOldProc(UINT msg, WPARAM wParam, LPARAM lParam) = 0;
	virtual int WndProcAfterOldProc(UINT msg, WPARAM wParam, LPARAM lParam) = 0;
	virtual BOOL OnInitDecorator() = 0;
	
	BOOL CreateDecorator(CWnd *pWnd);

	
	typedef std::map<HWND, DecoratorInfo> HandlerMap;
	static HandlerMap s_HandlerMap;
	static LRESULT CALLBACK SubclassWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	//
	static LRESULT m_retOldProc;
	CWnd *m_pWnd;
};

};

#endif // !defined(AFX_WNDDECORATOR_H__8D1A1F4A_BEE8_479B_82DE_603A7C2FEA05__INCLUDED_)
