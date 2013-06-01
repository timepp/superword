#if !defined(AFX_RSMISCPAGE_H__05A90CD7_F4C2_4D10_A8D5_C1121584EC86__INCLUDED_)
#define AFX_RSMISCPAGE_H__05A90CD7_F4C2_4D10_A8D5_C1121584EC86__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSMiscPage.h : header file
//

#include "GlobalSetting.h"
#include "PopupHelpStyle.h"

/////////////////////////////////////////////////////////////////////////////
// CRSMiscPage dialog
using namespace decorate;
class CRSMiscPage : public CPropertyPage, public CPopupHelpStyle
{
	DECLARE_DYNCREATE(CRSMiscPage)

// Construction
public:
	CRSMiscPage();
	~CRSMiscPage();

// Dialog Data
	//{{AFX_DATA(CRSMiscPage)
	enum { IDD = IDD_RS_MISC_PAGE };
	CComboBox	m_cbMarkAccesstimeMode;
	int		m_nWordOrderBase;
	int		m_nWordOrder;
	//}}AFX_DATA

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CRSMiscPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void UpdateControlState();
	// Generated message map functions
	//{{AFX_MSG(CRSMiscPage)
	afx_msg void OnSelchangeCbMarkAccesstimeMode();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RSMISCPAGE_H__05A90CD7_F4C2_4D10_A8D5_C1121584EC86__INCLUDED_)
