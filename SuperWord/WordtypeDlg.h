#if !defined(AFX_RSWORDTYPEPAGE_H__A54D65B0_A509_4822_9366_1D78A60A9407__INCLUDED_)
#define AFX_RSWORDTYPEPAGE_H__A54D65B0_A509_4822_9366_1D78A60A9407__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSWordtypePage.h : header file
//

#include "GlobalSetting.h"
#include "WordType.h"
#include "Word.h"
#include <map>


#include "PopupHelpStyle.h"
/////////////////////////////////////////////////////////////////////////////
// CWordtypeDlg dialog
using namespace decorate;
using namespace word;
class CWordtypeDlg : public CDialog, public CPopupHelpStyle
{
	DECLARE_DYNCREATE(CWordtypeDlg)

// Construction
public:
	CWordtypeDlg();
	~CWordtypeDlg();

// Dialog Data
	//{{AFX_DATA(CWordtypeDlg)
	enum { IDD = IDD_WORDTYPE_DLG };
	CListBox	m_lbWordList;
	//}}AFX_DATA
	
// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CWordtypeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void InitWordTypeList();
	BOOL ExchangeItem(int item1, int item2);

	// 重新整理所有单词的属性
	void RecreateWordType();
	// 重新设置一个单词的属性
	void ResetWordType(Word *pw);

	// Generated message map functions
	//{{AFX_MSG(CWordtypeDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnMoveup();
	afx_msg void OnBtnMovedown();
	afx_msg void OnBtnAddWordType();
	afx_msg void OnBtnDelWordType();
	afx_msg void OnBtnExchangeSel();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RSWORDTYPEPAGE_H__A54D65B0_A509_4822_9366_1D78A60A9407__INCLUDED_)
