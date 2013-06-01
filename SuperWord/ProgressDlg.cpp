// ProgressDlg.cpp : implementation file
//

#include "stdafx.h"
#include "superword.h"
#include "ProgressDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProgressDlg dialog


CProgressDlg::CProgressDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProgressDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProgressDlg)
	//}}AFX_DATA_INIT
}

CProgressDlg * CProgressDlg::Instance()
{
	static CProgressDlg dlg;
	if (!dlg.m_hWnd)
	{
		dlg.Create(IDD_PROGRESS_DLG);
	}

	return &dlg;
}

void CProgressDlg::SetTaskName(LPCTSTR pszTask)
{
	SetWindowText(pszTask);
}

void CProgressDlg::ResetProgress(int nTotal /* = -1 */)
{
	if (nTotal >= 0)
	{
		m_nPercent = nTotal / 100;
		if (m_nPercent == 0)
			m_nPercent = 1;
	}
	m_nPos = 0;
	m_Progress.SetPos(m_nPos);
}

void CProgressDlg::RestartTask(LPCTSTR pszTask, size_t nTotal /* = -1 */)
{
	SetTaskName(pszTask);
	ResetProgress(static_cast<int>(nTotal));
	ShowWindow(SW_SHOWDEFAULT);
}

void CProgressDlg::StepIt()
{
	m_nPos++;
	if (m_nPos % m_nPercent == 0)
		m_Progress.StepIt();
}

void CProgressDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProgressDlg)
	DDX_Control(pDX, IDC_PROGRESS, m_Progress);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProgressDlg, CDialog)
	//{{AFX_MSG_MAP(CProgressDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProgressDlg message handlers

BOOL CProgressDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_Progress.SetStartColor(RGB(0, 0, 192));
	m_Progress.SetEndColor(RGB(255, 255, 255));
	m_Progress.ShowPercent(FALSE);
	m_Progress.SetRange(0, 100);
	m_Progress.SetStep(1);

	return TRUE;
}
