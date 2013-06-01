#if !defined(AFX_INPUTDLG_H__6F16FE1F_D1C6_41D7_A267_4C63FBA6DDED__INCLUDED_)
#define AFX_INPUTDLG_H__6F16FE1F_D1C6_41D7_A267_4C63FBA6DDED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InputDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInputDlg dialog

class CInputDlg : public CDialog
{
// Construction
public:
	CInputDlg(LPCTSTR pszPrompt, CWnd* pParent = NULL);   // standard constructor

	CString GetInputString() const;
	
// Dialog Data
	//{{AFX_DATA(CInputDlg)
	enum { IDD = IDD_INPUT_DLG };
	CString	m_strInput;
	CString	m_strPrompt;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInputDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CInputDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INPUTDLG_H__6F16FE1F_D1C6_41D7_A267_4C63FBA6DDED__INCLUDED_)
