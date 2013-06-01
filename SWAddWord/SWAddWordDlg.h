// SWAddWordDlg.h : header file
//

#if !defined(AFX_SWADDWORDDLG_H__8395F58F_CF20_4D3C_A734_D3FD6A96C1D0__INCLUDED_)
#define AFX_SWADDWORDDLG_H__8395F58F_CF20_4D3C_A734_D3FD6A96C1D0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSWAddWordDlg dialog
#include <iostream>

class CSWAddWordDlg : public CDialog
{
// Construction
public:
	CSWAddWordDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSWAddWordDlg)
	enum { IDD = IDD_SWADDWORD_DIALOG };
	CString	m_strMeaning;
	CString	m_strPhonetic;
	CString	m_strWord;
	CString	m_strWordFileName;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSWAddWordDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	void copy_stream(std::ifstream& is, std::ofstream& os, long size);
	void extract_word(std::ifstream& is, char *word);
	void step_word(std::ifstream& is);

	// Generated message map functions
	//{{AFX_MSG(CSWAddWordDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnSelectfile();
	afx_msg void OnBtnAdd();
	afx_msg void OnBtnDelete();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SWADDWORDDLG_H__8395F58F_CF20_4D3C_A734_D3FD6A96C1D0__INCLUDED_)
