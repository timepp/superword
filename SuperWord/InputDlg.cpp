// InputDlg.cpp : implementation file
//

#include "stdafx.h"
#include "superword.h"
#include "InputDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInputDlg dialog


CInputDlg::CInputDlg(LPCTSTR pszPrompt, CWnd* pParent /*=NULL*/)
	: CDialog(CInputDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInputDlg)
	m_strInput = _T("");
	m_strPrompt = _T("");
	//}}AFX_DATA_INIT

	m_strPrompt = pszPrompt;
}


void CInputDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInputDlg)
	DDX_Text(pDX, IDC_EDIT, m_strInput);
	DDX_Text(pDX, IDC_PROMPT, m_strPrompt);
	//}}AFX_DATA_MAP
}

CString CInputDlg::GetInputString() const
{
	return m_strInput;
}


BEGIN_MESSAGE_MAP(CInputDlg, CDialog)
	//{{AFX_MSG_MAP(CInputDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInputDlg message handlers
