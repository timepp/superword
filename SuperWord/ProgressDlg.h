#if !defined(AFX_PROGRESSDLG_H__78D57D3A_77DC_4314_8FCC_9A74B6A310C0__INCLUDED_)
#define AFX_PROGRESSDLG_H__78D57D3A_77DC_4314_8FCC_9A74B6A310C0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProgressDlg.h : header file
//
#include "LibSrc/GradientProgress/GradientProgressCtrl.h"
/////////////////////////////////////////////////////////////////////////////
// CProgressDlg dialog

class CProgressDlg : public CDialog
{
// Construction
public:
	static CProgressDlg * Instance();

	void SetTaskName(LPCTSTR pszTask);
	void ResetProgress(int nTotal = -1);
	void RestartTask(LPCTSTR pszTask, size_t nTotal = -1);
	void StepIt();
// Dialog Data
	//{{AFX_DATA(CProgressDlg)
	enum { IDD = IDD_PROGRESS_DLG };
	CGradientProgressCtrl	m_Progress;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProgressDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	int m_nPos;
	int m_nPercent;

	CProgressDlg(CWnd* pParent = NULL);   // standard constructor
	// Generated message map functions
	//{{AFX_MSG(CProgressDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROGRESSDLG_H__78D57D3A_77DC_4314_8FCC_9A74B6A310C0__INCLUDED_)
