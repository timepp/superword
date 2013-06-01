#pragma once

#include "PopupHelpStyle.h"
#include "ResizableStyle.h"
#include "afxwin.h"
#include "afxcmn.h"

#include "CSWordDlg.h"
#include "CSPhoneticDlg.h"
#include "CSMeaningDlg.h"
#include "CSClassDlg.h"
#include "CSAccessTimeDlg.h"
#include "CSTypeDlg.h"
#include "CSTimerCmdSetDlg.h"
#include "CSMoveWordCmdSetDlg.h"
#include "CSSetColorDlg.h"
#include "CSHotKeySetDlg.h"
#include "CSOpenDlgDlg.h"
#include "CSRemarkDlg.h"
#include "CSShowElementDlg.h"
#include "CSWordTypeDlg.h"
#include "CSMiscDlg.h"
#include "CSAccelDlg.h"
#include "CSReciteSchemeDlg.h"
#include "MiscCondDlg.h"

#include "RootComposite.h"
#include "CompositeTreeCtrl.h"

#include <sstream>
using namespace decorate;

class CReciteSchemeDlg : public CDialog, public CPopupHelpStyle, public CResizableStyle
{
	DECLARE_DYNAMIC(CReciteSchemeDlg)
	DECLARE_MESSAGE_MAP()
public:
	CReciteSchemeDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CReciteSchemeDlg();

// Dialog Data
	enum { IDD = IDD_RECITE_SCHEME };

	BOOL m_bFilterChanged;
	BOOL m_bPerwordCmdChanged;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

private:
	void SetChildItemResizeInfo();

	void FillCompInfo();

	enum Orientation { honrizontal, vertical };
	enum InitPos { begin, mid, end, cur };
	void MoveResizerPos(InitPos ipos, int pos);
	void UpdateResizeRect();
	BOOL PointOnDragableHorizontalResizer(POINT pt);

	void SaveSchemeToSingleFile(const std::string& file_name);
	void LoadSchemeFromSingleFile(const std::string& file_name);

	virtual BOOL OnInitDialog();

private:
	CButton m_chkShowCondition;
	CButton m_chkShowPerwordCmd;
	CCompositeTreeCtrl m_tcCond;
	CCompositeTreeCtrl m_tcWCmd;
	RootComposite m_rootCondition;
	RootComposite m_rootPerWordCmd;
	std::stringstream m_ssOldCondition;
	std::stringstream m_ssOldPerwordCmd;
	BOOL m_bConditionActive;
	BOOL m_bPerwordCmdActive;
	CRect m_rectHorizontalResizer;
	BOOL m_bDragingHorizontalResizer;
	CPoint m_ptOldDrag;

	const int m_nInactiveTreeWidth;
	const int m_nInactiveTreeHeight;

	CompInfoVector m_civ;
	CCSWordDlg m_dlgWord;
	CCSPhoneticDlg m_dlgPhonetic;
	CCSMeaningDlg m_dlgMeaning;
	CCSTimerCmdSetDlg m_dlgTimerCmd;
	CCSHotkeySetDlg m_dlgHotKey;
	CCSMoveWordCmdSetDlg m_dlgMoveWord;
	CCSAccessTimeDlg m_dlgAccesstime;
	CCSClassDlg m_dlgClass;
	CCSTypeDlg m_dlgType;
	CCSSetColorDlg m_dlgSetColor;
	CCSRemarkDlg m_dlgRemark;
	CCSOpenDlgDlg m_dlgOpenDlg;
	CCSShowElementDlg m_dlgShowElement;
	CCSWordTypeDlg m_dlgWordType;
	CCSMiscDlg m_dlgMisc;
	CCSAccelDlg m_dlgAccel;
	CCSReciteSchemeDlg m_dlgReciteScheme;
	CCSMiscCondDlg m_dlgMiscCond;

	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	virtual void OnOK();
	afx_msg void OnBnClickedButtonOpenReciteScheme();
	afx_msg void OnBnClickedButtonSaveReciteScheme();
};
