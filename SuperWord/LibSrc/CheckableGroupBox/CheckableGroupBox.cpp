// CheckableGroupBox.cpp : implementation file
//

#include "stdafx.h"
#include "CheckableGroupBox.h"

#define ID_TITLE	0xFFFF

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCheckableGroupBox
IMPLEMENT_DYNAMIC( CCheckableGroupBox, CButton )


CCheckableGroupBox::CCheckableGroupBox()
{
}

CCheckableGroupBox::~CCheckableGroupBox()
{
}


BEGIN_MESSAGE_MAP(CCheckableGroupBox, CButton)
	//{{AFX_MSG_MAP(CCheckableGroupBox)
	//}}AFX_MSG_MAP
	ON_COMMAND( ID_TITLE , OnClicked)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCheckableGroupBox message handlers


void CCheckableGroupBox::SetTitleStyle(UINT style)
{
	CString strText;
	GetWindowText(strText);

	CClientDC dc(this);
	CFont* pOldFont = dc.SelectObject(GetFont());
	CSize czText = dc.GetTextExtent(strText);
	dc.SelectObject(pOldFont);
	// Add some space for the checkbox and at the end
	czText.cx += 25;

	// Move the checkbox on top of the groupbox
	CRect rc;
	GetWindowRect(rc);	
	this->ScreenToClient(rc);
	rc.left += 5;
	rc.right = rc.left + czText.cx;
	rc.bottom = rc.top + czText.cy;

	if(style == BS_AUTOCHECKBOX || style == BS_AUTORADIOBUTTON)
	{
		m_TitleBox.Create(strText, style | WS_CHILD  | WS_TABSTOP, rc, this, ID_TITLE);
		m_TitleBox.SetFont(GetFont(), true);
		m_TitleBox.ShowWindow(SW_SHOW);
	}
}

/**
* If current m_TitleBox is a radio button, search all controls in current parent
* window, uncheck all other radio buttons if they have the same group id
*/
void CCheckableGroupBox::OnClicked() 
{
	CheckGroupboxControls();
	UINT style = m_TitleBox.GetButtonStyle();
	if(style == BS_AUTORADIOBUTTON)
	{
		CWnd* pWnd = GetParent()->GetWindow(GW_CHILD);
		CRect rcWnd, rcTest;

		while (pWnd)
		{
			if(pWnd->IsKindOf(RUNTIME_CLASS(CCheckableGroupBox)))
			{
				CCheckableGroupBox* pT = (CCheckableGroupBox*)pWnd;
				if(pT->GetGroupID() == m_nGroupID && pT != this)
				{
					pT->SetCheck(0);
				}
			}
			pWnd = pWnd->GetWindow(GW_HWNDNEXT);
		}		
	}
}

void CCheckableGroupBox::CheckGroupboxControls()
{
	int nCheck = m_TitleBox.GetCheck();
	CRect rcGroupbox;
	GetWindowRect(rcGroupbox);

	// Get first child control
	CWnd* pWnd = GetParent()->GetWindow(GW_CHILD);
	
	CRect rcWnd, rcTest;

	while (pWnd)
	{
		pWnd->GetWindowRect(rcWnd);

		if (rcTest.IntersectRect(rcGroupbox, rcWnd) 
				&& pWnd != this && pWnd != &m_TitleBox)
		{
			pWnd->EnableWindow(nCheck == 1);
		}
		pWnd = pWnd->GetWindow(GW_HWNDNEXT);
	}
}

int CCheckableGroupBox::GetCheck() const
{
	return m_TitleBox.GetCheck();
}
void CCheckableGroupBox::SetCheck(int nCheck)
{
	m_TitleBox.SetCheck(nCheck);
	CheckGroupboxControls();
}

void CCheckableGroupBox::SetGroupID(UINT nGroup)
{
	m_nGroupID = nGroup;
}
UINT CCheckableGroupBox::GetGroupID() const
{
	return m_nGroupID;
}


