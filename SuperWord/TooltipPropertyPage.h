#if !defined(AFX_TOOLTIPPROPERTYPAGE_H__44AB4D34_9368_47A2_A90E_A2DFD49D76FB__INCLUDED_)
#define AFX_TOOLTIPPROPERTYPAGE_H__44AB4D34_9368_47A2_A90E_A2DFD49D76FB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TooltipPropertyPage.h : header file
//

#include "LibSrc/OxTooltip/OXToolTipCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CTooltipPropertyPage dialog
// 带工具提示的属性页

class CTooltipPropertyPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CTooltipPropertyPage)

// Construction
public:
	CTooltipPropertyPage();
	CTooltipPropertyPage(UINT nID);
	~CTooltipPropertyPage();

// Dialog Data
	//{{AFX_DATA(CTooltipPropertyPage)
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTooltipPropertyPage)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	COXToolTipCtrl m_tooltip;
	// Generated message map functions
	//{{AFX_MSG(CTooltipPropertyPage)
	virtual BOOL OnInitDialog();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TOOLTIPPROPERTYPAGE_H__44AB4D34_9368_47A2_A90E_A2DFD49D76FB__INCLUDED_)
