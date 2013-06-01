// PopupHelpStyle.cpp: implementation of the CPopupHelpStyle class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "superword.h"
#include "PopupHelpStyle.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

using decorate::CPopupHelpStyle;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPopupHelpStyle::CPopupHelpStyle()
{

}

CPopupHelpStyle::~CPopupHelpStyle()
{

}

BOOL CPopupHelpStyle::OnInitDecorator()
{
	LONG style = ::GetWindowLong(m_pWnd->m_hWnd, GWL_EXSTYLE);
	style |= WS_EX_CONTEXTHELP;
	::SetWindowLong(m_pWnd->m_hWnd, GWL_EXSTYLE, style);

	return TRUE;
}

int CPopupHelpStyle::WndProcBeforeOldProc(UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_HELP)
	{
		helper::ShowContextHelp((HELPINFO *)lParam);
		return DONT_CALL_OLD_PROC;
	}
	// 用户按下鼠标右键就会弹出帮助框，
	// 调试模式会引发一个assertion: wincore.cpp 875
	//else if (msg == WM_RBUTTONUP)
	else if (0)
	{
		CPoint pt(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		
		HELPINFO hi = {sizeof(HELPINFO)};
		hi.dwContextId = HELPINFO_WINDOW;
		hi.MousePos = pt;
		m_pWnd->ScreenToClient(&pt);
		CWnd *pWnd = m_pWnd->ChildWindowFromPoint(pt);
		if (pWnd != NULL)
		{
			hi.hItemHandle = pWnd->m_hWnd;
			hi.iCtrlId = pWnd->GetDlgCtrlID();
			helper::ShowContextHelp(&hi);
			return DONT_CALL_OLD_PROC;
		}
	}

	return RETURN_DEFAULT;
}

int CPopupHelpStyle::WndProcAfterOldProc(UINT msg, WPARAM wParam, LPARAM lParam)
{

	return RETURN_DEFAULT;
}