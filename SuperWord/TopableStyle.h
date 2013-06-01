// TopableStyle.h: interface for the CTopableStyle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TOPABLESTYLE_H__EF67FF60_ED43_4075_8980_E4ED4CF22B04__INCLUDED_)
#define AFX_TOPABLESTYLE_H__EF67FF60_ED43_4075_8980_E4ED4CF22B04__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "WndDecorator.h"
#include <map>

namespace decorate
{

class CTopableStyle : public CWndDecorator
{
public:
	CTopableStyle();
	virtual ~CTopableStyle();

private:
	BOOL m_bTopboxLButtonDown;
	BOOL m_bCursorOnTopBox;
	BOOL m_bTopMost;

	inline BOOL TopboxPushLike() const
	{
		return (m_bTopMost || m_bTopboxLButtonDown && m_bCursorOnTopBox);
	}

	CRect GetTopableBoxRect(BOOL bScreenCoordinates);
	void DrawTopableBox();

	virtual int WndProcBeforeOldProc(UINT msg, WPARAM wParam, LPARAM lParam);
	virtual int WndProcAfterOldProc(UINT msg, WPARAM wParam, LPARAM lParam);
	virtual BOOL OnInitDecorator();
};

};

#endif // !defined(AFX_TOPABLESTYLE_H__EF67FF60_ED43_4075_8980_E4ED4CF22B04__INCLUDED_)
