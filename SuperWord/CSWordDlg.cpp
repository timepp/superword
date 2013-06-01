// CSWordDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SuperWord.h"
#include "ConcreteCondition.h"
#include "CSWordDlg.h"

#include <iostream>
#include <sstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace compdlg;
using namespace comp;
/////////////////////////////////////////////////////////////////////////////
// CCSWordDlg dialog

CCSWordDlg::CCSWordDlg(CWnd* pParent /*=NULL*/)
	: CCSRootDlg(CCSWordDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCSWordDlg)
	m_strMatcher = _T("");
	//}}AFX_DATA_INIT
}

void CCSWordDlg::DoDataExchange(CDataExchange* pDX)
{
    cond::WordCondition * pCond = dynamic_cast<cond::WordCondition *>(m_pComp);
	CCSRootDlg::DoDataExchange(pDX);
	if (!pDX->m_bSaveAndValidate)
	{
        m_strMatcher = pCond->GetConfiguration().c_str();
	}

	//{{AFX_DATA_MAP(CCSWordDlg)
	DDX_Text(pDX, IDC_EDIT_MATCHER, m_strMatcher);
	//}}AFX_DATA_MAP

	if (pDX->m_bSaveAndValidate)
	{
        pCond->Configure((LPCTSTR)m_strMatcher);
	}
}


BEGIN_MESSAGE_MAP(CCSWordDlg, CCSRootDlg)
	//{{AFX_MSG_MAP(CCSWordDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCSWordDlg message handlers
