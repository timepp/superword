// PopupHelpStyle.h: interface for the CPopupHelpStyle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POPUPHELPSTYLE_H__668ED4D5_40AA_49FF_8FDC_13E862E9AC2A__INCLUDED_)
#define AFX_POPUPHELPSTYLE_H__668ED4D5_40AA_49FF_8FDC_13E862E9AC2A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "WndDecorator.h"

namespace decorate
{

class CPopupHelpStyle : public CWndDecorator  
{
public:
	CPopupHelpStyle();
	virtual ~CPopupHelpStyle();

	virtual int WndProcBeforeOldProc(UINT msg, WPARAM wParam, LPARAM lParam);
	virtual int WndProcAfterOldProc(UINT msg, WPARAM wParam, LPARAM lParam);
	virtual BOOL OnInitDecorator();
};

};

#endif // !defined(AFX_POPUPHELPSTYLE_H__668ED4D5_40AA_49FF_8FDC_13E862E9AC2A__INCLUDED_)
