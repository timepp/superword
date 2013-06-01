// WndDecorator.cpp: implementation of the CWndDecorator class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "superword.h"
#include "WndDecorator.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

using namespace decorate;

CWndDecorator::HandlerMap CWndDecorator::s_HandlerMap;
LRESULT CWndDecorator::m_retOldProc = 0;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWndDecorator::CWndDecorator()
{
	m_pWnd = NULL;
}

CWndDecorator::~CWndDecorator()
{

}

BOOL CWndDecorator::CreateDecorator(CWnd *pWnd)
{
	ASSERT(pWnd != NULL);
	ASSERT(::IsWindow(pWnd->m_hWnd));

	// 注册一个this指针和窗口句柄的映射
	DecoratorInfo& dInfo = s_HandlerMap[pWnd->m_hWnd];
	if (dInfo.dSet.find(this) != dInfo.dSet.end())
		return FALSE;

#pragma warning(disable: 4312 4311)
	WNDPROC oldWndProc = reinterpret_cast<WNDPROC>(::GetWindowLongPtr(pWnd->m_hWnd, GWL_WNDPROC));
	if (oldWndProc != SubclassWindowProc)
	{
		::SetWindowLongPtr(pWnd->m_hWnd, GWL_WNDPROC, LONG(SubclassWindowProc));
		dInfo.oldWndProc = oldWndProc;
	}
#pragma warning(default: 4312 4311)

	m_pWnd = pWnd;
	dInfo.dSet.insert(this);

	OnInitDecorator();

	return TRUE;
}

LRESULT CWndDecorator::SubclassWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	DecoratorInfo& dInfo = s_HandlerMap[hwnd];
	DecoratorSet::const_iterator ci;
	LRESULT lret;
	BOOL bCallOldProc = TRUE;

	m_retOldProc = 0;

	if (msg == WM_NCDESTROY)
	{
#pragma warning(disable: 4311)
		::SetWindowLong(hwnd, GWL_WNDPROC, LONG(dInfo.oldWndProc));
#pragma warning(default: 4311)
	}

	for (ci = dInfo.dSet.begin(); ci != dInfo.dSet.end(); ++ci)
	{
		lret = (*ci)->WndProcBeforeOldProc(msg, wParam, lParam);
		if (lret == DONT_CALL_OLD_PROC) bCallOldProc = FALSE;
	}

	if (bCallOldProc && ::IsWindow(hwnd))
		m_retOldProc = ::CallWindowProc(dInfo.oldWndProc, hwnd, msg, wParam, lParam);

	for (ci = dInfo.dSet.begin(); ci != dInfo.dSet.end(); ++ci)
	{
		lret = (*ci)->WndProcAfterOldProc(msg, wParam, lParam);
		if (lret >= 0) m_retOldProc = lret;
	}

	if (msg == WM_NCDESTROY)
	{
		dInfo.dSet.clear();
	}

	return m_retOldProc;
}
