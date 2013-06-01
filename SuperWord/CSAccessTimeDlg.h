#if !defined(AFX_FSACCESSTIMEDLG_H__19E11666_929D_42E5_8267_B62C0D98FF96__INCLUDED_)
#define AFX_FSACCESSTIMEDLG_H__19E11666_929D_42E5_8267_B62C0D98FF96__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CSAccessTimeDlg.h : header file
//
#include "CSRootDlg.h"
#include "LibSrc/CheckableGroupBox/CheckableGroupBox.h"

namespace compdlg
{

/////////////////////////////////////////////////////////////////////////////
// CCSAccessTimeDlg dialog

class CCSAccessTimeDlg : public CCSRootDlg
{
// Construction
public:
	CCSAccessTimeDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCSAccessTimeDlg)
	enum { IDD = IDD_CS_ACCESSTIME_DLG };
	CButton	m_chkTmMin;
	CButton	m_chkTmMax;
	CDateTimeCtrl	m_dcMin;
	CDateTimeCtrl	m_dcMax;
	BOOL	m_bHasTmMin;
	BOOL	m_bHasTmMax;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCSAccessTimeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void SyncDatePicker();
	CCheckableGroupBox m_cgAbsDate, m_cgRelaDate;
	// Generated message map functions
	//{{AFX_MSG(CCSAccessTimeDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckTmmin();
	afx_msg void OnCheckTmmax();
	afx_msg void OnButtonAllrecited();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
    virtual void OnOK();
private:
    long m_relaTime;
};

};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FSACCESSTIMEDLG_H__19E11666_929D_42E5_8267_B62C0D98FF96__INCLUDED_)
