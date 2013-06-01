// ReciteProgressCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "superword.h"
#include "ReciteProgressCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReciteProgressCtrl

CReciteProgressCtrl::CReciteProgressCtrl()
{
}

CReciteProgressCtrl::~CReciteProgressCtrl()
{
}


BEGIN_MESSAGE_MAP(CReciteProgressCtrl, CGradientProgressCtrl)
	//{{AFX_MSG_MAP(CReciteProgressCtrl)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_NCCREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReciteProgressCtrl message handlers

void CReciteProgressCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CGradientProgressCtrl::OnLButtonDown(nFlags, point);
	
	CRect rc;
	GetClientRect(&rc);
	if (point.x < rc.Width() / 2)
	{
		GetParent()->SendMessage(WM_COMMAND, IDC_PREVWORD);
	}
	else
	{
		GetParent()->SendMessage(WM_COMMAND, IDC_NEXTWORD);
	}
}

void CReciteProgressCtrl::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	CGradientProgressCtrl::OnLButtonDblClk(nFlags, point);

	CRect rc;
	GetClientRect(&rc);
	if (point.x < rc.Width() / 2)
	{
		GetParent()->SendMessage(WM_COMMAND, IDC_FIRSTWORD);
	}
	else
	{
		GetParent()->SendMessage(WM_COMMAND, IDC_LASTWORD);
	}
}

BOOL CReciteProgressCtrl::OnNcCreate(LPCREATESTRUCT lpCreateStruct) 
{

	if (!CGradientProgressCtrl::OnNcCreate(lpCreateStruct))
		return FALSE;
		
	return TRUE;
}

void CReciteProgressCtrl::PreSubclassWindow() 
{
	ModifyStyle(0, CS_DBLCLKS);	
	CGradientProgressCtrl::PreSubclassWindow();
}
