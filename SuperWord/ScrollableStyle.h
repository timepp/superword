// ScrollableStyle.h: interface for the CScrollableStyle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCROLLABLESTYLE_H__C3823DCE_3078_4B51_B84E_2AE5C1756A06__INCLUDED_)
#define AFX_SCROLLABLESTYLE_H__C3823DCE_3078_4B51_B84E_2AE5C1756A06__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "WndDecorator.h"

namespace decorate
{

class CScrollableStyle : public CWndDecorator  
{
public:
	CScrollableStyle();
	virtual ~CScrollableStyle();

	virtual int WndProcBeforeOldProc(UINT msg, WPARAM wParam, LPARAM lParam);
	virtual int WndProcAfterOldProc(UINT msg, WPARAM wParam, LPARAM lParam);
	virtual BOOL OnInitDecorator();

private:
	// save the original size
	CRect m_rcOriginalRect;

	// initial scroll position
	int m_nScrollPos;
	int m_nCurHeight;

	void ResetResizeInfo();
	void OnVScroll(UINT nSBCode, UINT nPos);
};

};

#endif // !defined(AFX_SCROLLABLESTYLE_H__C3823DCE_3078_4B51_B84E_2AE5C1756A06__INCLUDED_)
