#if !defined(AFX_OPTIONSHEET_H__62B97836_3F0B_4F5B_A15E_AAAB2F85526A__INCLUDED_)
#define AFX_OPTIONSHEET_H__62B97836_3F0B_4F5B_A15E_AAAB2F85526A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptionSheet.h : header file
//

#include "RSColorPage.h"
#include "RSMiscPage.h"
#include "PopupHelpStyle.h"

/////////////////////////////////////////////////////////////////////////////
// COptionSheet
using namespace decorate;
class COptionSheet : public CPropertySheet, public CPopupHelpStyle
{
	DECLARE_DYNAMIC(COptionSheet)

// Construction
public:
	COptionSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	COptionSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
protected:
	CRSColorPage m_cp;
	CRSMiscPage m_rmp;

	void AddPages();
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COptionSheet)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COptionSheet();

	// Generated message map functions
protected:
	//{{AFX_MSG(COptionSheet)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONSHEET_H__62B97836_3F0B_4F5B_A15E_AAAB2F85526A__INCLUDED_)
