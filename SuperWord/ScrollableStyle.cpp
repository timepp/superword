// ScrollableStyle.cpp: implementation of the CScrollableStyle class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "superword.h"
#include "ScrollableStyle.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

using decorate::CScrollableStyle;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CScrollableStyle::CScrollableStyle()
{

}

CScrollableStyle::~CScrollableStyle()
{

}

void CScrollableStyle::ResetResizeInfo()
{
	SCROLLINFO si;
	si.cbSize = sizeof(SCROLLINFO);
	si.fMask = SIF_ALL; 
	si.nMin = 0;
	si.nMax = m_rcOriginalRect.Height();
	si.nPage = m_nCurHeight;
	si.nPos = 0;
	m_pWnd->SetScrollInfo(SB_VERT, &si, TRUE);
}

void CScrollableStyle::OnVScroll(UINT nSBCode, UINT nPos)
{
	// �����������λ��
	int nMaxPos = m_rcOriginalRect.Height() - m_nCurHeight;
	// �ɵ�λ�ú��µ�λ��
	int nOldScrollPos = m_nScrollPos;
	int nNewScrollPos = m_nScrollPos;

	switch (nSBCode)
	{
	case SB_LINEDOWN:
		nNewScrollPos += 10;
		break;
		
	case SB_LINEUP:
		nNewScrollPos -= 10;
		break;

	case SB_PAGEDOWN:
		nNewScrollPos += m_nCurHeight;
		break;

	case SB_PAGEUP:
		nNewScrollPos -= m_nCurHeight;
		break;

	case SB_THUMBTRACK:
	case SB_THUMBPOSITION:
		nNewScrollPos = (int)nPos;
		break;	
		
	default:
		return;
	}

	// ������λ��
	if (nNewScrollPos < 0) nNewScrollPos = 0;
	if (nNewScrollPos > nMaxPos) nNewScrollPos = nMaxPos;

	// �¾�λ�ò�һ���Ļ�����������������ƶ�����
	if (nNewScrollPos != nOldScrollPos)
	{
		m_pWnd->SetScrollPos(SB_VERT, nNewScrollPos, TRUE);
		m_pWnd->ScrollWindow(0, nOldScrollPos - nNewScrollPos);

		m_nScrollPos = nNewScrollPos;
	}
}

BOOL CScrollableStyle::OnInitDecorator()
{
	m_pWnd->GetWindowRect(&m_rcOriginalRect);
	m_nScrollPos = 0;

	return TRUE;
}

int CScrollableStyle::WndProcAfterOldProc(UINT msg, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(wParam);

	if (msg == WM_SIZE)
	{
		m_nCurHeight = HIWORD(lParam);
		ResetResizeInfo();
	}
	
	
	return RETURN_DEFAULT;
}

int CScrollableStyle::WndProcBeforeOldProc(UINT msg, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);

	if (msg == WM_VSCROLL)
	{
		OnVScroll(LOWORD(wParam), HIWORD(wParam));
	}
	if (msg == WM_COMMAND)
	{
		if (wParam == IDOK || wParam == IDCANCEL)
			return DONT_CALL_OLD_PROC;
	}
	return RETURN_DEFAULT;
}

