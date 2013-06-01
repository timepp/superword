#if !defined(AFX_FSTYPEDLG_H__C0C773BE_72C8_496C_870D_8DD401FDD5A9__INCLUDED_)
#define AFX_FSTYPEDLG_H__C0C773BE_72C8_496C_870D_8DD401FDD5A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CSTypeDlg.h : header file
//

#include "CSRootDlg.h"
/////////////////////////////////////////////////////////////////////////////
// CCSTypeDlg dialog
namespace compdlg
{

class CCSTypeDlg : public CCSRootDlg
{
// Construction
public:
	CCSTypeDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCSTypeDlg)
	enum { IDD = IDD_CS_TYPE_DLG };
	CComboBox	m_cbType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCSTypeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCSTypeDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
};

};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FSTYPEDLG_H__C0C773BE_72C8_496C_870D_8DD401FDD5A9__INCLUDED_)
