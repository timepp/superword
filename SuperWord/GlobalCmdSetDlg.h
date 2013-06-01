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

// CGlobalCmdSetDlg dialog

class CGlobalCmdSetDlg : public CDialog, public CPopupHelpStyle, public CResizableStyle
{
	DECLARE_DYNAMIC(CGlobalCmdSetDlg)
	DECLARE_MESSAGE_MAP()

public:
	CGlobalCmdSetDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CGlobalCmdSetDlg();

// Dialog Data
	enum { IDD = IDD_GLOBALCMD_SET_DLG };

	BOOL m_bGlobalCmdChanged;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

private:
	void SetChildItemResizeInfo();
	void FillCompInfo();


	CCompositeTreeCtrl m_tcGCmd;
	RootComposite m_rootGlobalCmd;
	std::stringstream m_ssOldGlobalCmd;

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
	virtual BOOL OnInitDialog();
//	afx_msg void OnBnClickedOk();
protected:
	virtual void OnOK();
};
