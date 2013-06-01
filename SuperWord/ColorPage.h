#if !defined(AFX_COLORPAGE_H__46D95463_CD7C_43F0_9244_BC47FCDB2427__INCLUDED_)
#define AFX_COLORPAGE_H__46D95463_CD7C_43F0_9244_BC47FCDB2427__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ColorPage.h : header file
//
#include "PopupHelpStyle.h"
#include "ScrollableStyle.h"
#include "LibSrc/ColorBtn/ColorButton.h"
/////////////////////////////////////////////////////////////////////////////
// CColorPage dialog
using namespace decorate;
class CColorPage : public CPropertyPage, public CPopupHelpStyle, public CScrollableStyle
{
	DECLARE_DYNCREATE(CColorPage)

// Construction
public:

	CColorPage();
	~CColorPage();
	void LoadColorscheme();
	void SaveColorscheme();

// Dialog Data
	//{{AFX_DATA(CColorPage)
	enum { IDD = IDD_COLOR_PAGE };
	CColorButton	m_btnMsDarkshadow;
	CColorButton	m_btnMsShadow;
	CColorButton	m_btnMsHighlight;
	CColorButton	m_btnMsFace;
	CColorButton	m_btnMsBase;
	CColorButton	m_btnMsArrow;
	CColorButton	m_btnProgresscr2;
	CColorButton	m_btnTypeborder;
	CColorButton	m_btnTypebk;
	CColorButton	m_btnTypeactive;
	CColorButton	m_btnProgresscr1;
	CColorButton	m_btnProgresscolor;
	CColorButton	m_btnProgressbk;
	CColorButton	m_btnAccesstimecolor;
	CColorButton	m_btnAccesstimebk;
	CColorButton	m_btnWordcolor;
	CColorButton	m_btnWordbk;
	CColorButton	m_btnPracticecolor;
	CColorButton	m_btnPracticebk;
	CColorButton	m_btnPhoneticscolor;
	CColorButton	m_btnMeaningcolor;
	CColorButton	m_btnMeaningbk;
	CColorButton	m_btnDlgbk;
	//}}AFX_DATA

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CColorPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void SetColorBtnDefaultColor();

	MainColor m_Cr;
	CRect m_crScroll;
	CRect m_crWindow;


	static const TCHAR m_szCSSection[];
	static const TCHAR m_szCSKey[];

	LRESULT OnColorChange(WPARAM wp, LPARAM lp);
	// Generated message map functions
	//{{AFX_MSG(CColorPage)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORPAGE_H__46D95463_CD7C_43F0_9244_BC47FCDB2427__INCLUDED_)
