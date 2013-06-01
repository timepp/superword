// ResizableGrip.h: interface for the CResizableStyle class.
//

#if !defined(AFX_RESIZABLEGRIP_H__INCLUDED_)
#define AFX_RESIZABLEGRIP_H__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <map>
#include "WndDecorator.h"

namespace decorate
{

	// Window Resize Style
#define WRS_LEFT				0x00000001
#define WRS_RIGHT				0x00000002
#define WRS_TOP					0x00000004
#define WRS_BOTTOM				0x00000008

#define WRS_SYNWIDTH			WRS_LEFT | WRS_RIGHT
#define WRS_SYNHEIGHT			WRS_TOP | WRS_BOTTOM

	// Window Resize Measure Sytle
#define WRMS_PIXEL				1
#define WRMS_RATIO				2

#define ORG_SIZE				-1

	class CResizableStyle : public CWndDecorator
	{
	public:
		CResizableStyle();
		virtual ~CResizableStyle();

	public:
		BOOL SetDlgItemResizeInfo(UINT nID, DWORD dwResizeStyle, DWORD dwResizeMeasureStyle = WRMS_PIXEL);
		void DisableVerticalResize();
		void DisableHorizontalResize();

	private:

		CRect m_originalClientRect;
		CRect m_originalFullRect;
		struct ChildResizeInfo
		{
			CRect rcOriginal;
			DWORD dwResizeStyle;
			DWORD dwResizeMeasureStyle;
		};
		typedef std::map<UINT, ChildResizeInfo> ChildResizeInfoMap;
		ChildResizeInfoMap m_criMap;

		BOOL m_bDisableVerticalResize;
		BOOL m_bDisableHorizontalResize;

		void DrawGrip();
		void RecalcLayout();
		void RePlaceChildWnd(UINT nID, const ChildResizeInfo* pCri, const CRect& rcNew);
		BOOL PointOnResizeRgn(int x, int y);

		virtual int WndProcBeforeOldProc(UINT msg, WPARAM wParam, LPARAM lParam);
		virtual int WndProcAfterOldProc(UINT msg, WPARAM wParam, LPARAM lParam);
		virtual BOOL OnInitDecorator();
	};

};

#endif // !defined(AFX_RESIZABLEGRIP_H__INCLUDED_)
