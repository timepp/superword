// SuperWordDlg.h : header file
//

#if !defined(AFX_SuperWordDLG_H__098B5DB9_E73F_4B24_8435_AA75ECD04461__INCLUDED_)
#define AFX_SuperWordDLG_H__098B5DB9_E73F_4B24_8435_AA75ECD04461__INCLUDED_

#include "Resource.h"
#include "ReciteProgressCtrl.h"
#include "DetailMeaning.h"
#include "ResizableStyle.h"
#include "TopableStyle.h"
#include "WordManager.h"
#include "GlobalSetting.h"
#include "WordTypeWnd.h"
#include "DateWnd.h"
#include "RgnDlg.h"
#include "PractiseResultDlg.h"
#include "LibSrc/buttonST/BtnST.h"
#include "MeaningCtrl.h"
#include "NavigateWnd.h"

#include <list>
#include <map>


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

using namespace decorate;
using namespace comp;

/*
	Global command and Perword command
	1. Global command will be executed once program is initialized.
	2. Perword command will be executed once user navigate a new word.
	3. Non-immediate command, such as timer command, hotkey command and occasion
	   command, if it isn't global it will end when user navigate a new word.
	4. When user set another different global command, this new command will be 
	   executed immediately.
*/


/////////////////////////////////////////////////////////////////////////////
// CSuperWordDlg dialog

class CSuperWordDlg : public CDialog, public NavigateWnd,
                      public CResizableStyle//, public CTopableStyle
{
// Types
	struct CmdInfo
	{
		const cmd::Command * cmd;
		bool global;
		static bool is_global_cmd(const CmdInfo& ci)
		  { return ci.global; }
		static bool is_perword_cmd(const CmdInfo& ci)
		  { return !ci.global; }
	};
	struct TimerCmdInfo : public CmdInfo
    {
        UINT_PTR timer_id;
		size_t repeat_time;
    };
    typedef std::list<TimerCmdInfo> TimerCmdInfoList;

	struct HotkeyCmdInfo : public CmdInfo
    {
        ACCEL acl;
    };
    typedef std::list<HotkeyCmdInfo> HotkeyCmdInfoList;

	typedef void (CSuperWordDlg::*NoParamCmd)();
	typedef bool (CSuperWordDlg::*NoParamChecker)();
	typedef void (CSuperWordDlg::*SetElemColorCmd)(COLORREF cr);
	typedef void (CSuperWordDlg::*ShowElementCmd)(bool bShow);

	typedef std::map<std::string, SetElemColorCmd> SetColorCmdMap;
	typedef std::map<std::string, NoParamCmd> ActionMap;
	typedef std::map<std::string, ShowElementCmd> ShowElementCmdMap;
	typedef std::map<std::string, NoParamChecker> MiscConditionCmdMap;

// Construction
public:
	CSuperWordDlg(CWnd* pParent = NULL);	// standard constructor
	~CSuperWordDlg();
// Dialog Data
	//{{AFX_DATA(CSuperWordDlg)
	enum { IDD = IDD_SuperWord_DIALOG };
	CReciteProgressCtrl	m_pgWord;
	CDateWnd	m_dtAccess;
	CButtonST	m_btnMenu;
	CWordTypeWnd	m_wndWordType;
	CRichEditCtrl	m_rdPractice;
	CRichEditCtrl	m_rdWord;
	CString	m_strPractice;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSuperWordDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL
// Implementation
public:
    // implement the interface "NavigateWnd"
	virtual bool CreateNavigate();
    virtual const Word * GetCurrentWord() const;
    virtual bool MoveWord(MoveOp mo);

	virtual bool GetColorElement(ColorElementArray& array);
    virtual bool SetColor(const std::string& color_element, unsigned long cr);

	virtual bool GetDialogs(DlgNameArray& array);
	virtual bool OpenDialog(const std::string& dlg);

	virtual bool GetVisualElement(VisualElementArray& array);
	virtual bool ShowElement(const std::string& visual_element, bool show);

	virtual bool GetMiscCommands(MiscCommandArray & array);
	virtual bool RunMiscCommand(const std::string& cmd);

	virtual bool GetMiscConditions(MiscConditionArray & array);
	virtual bool CheckMiscCondition(const std::string& cond);

	virtual bool SetWordType(size_t index, SetTypeStyle style);
    virtual bool TimerExecute(unsigned long interval, size_t repeat_time, 
		bool bGlobal, const cmd::Command * cmd);
    virtual bool RegHotKey(ACCEL acl, bool bGlobal, const cmd::Command * cmd);
	virtual bool LoadComposite(const std::string& comp_file);

private:
    HICON m_hIcon;
    HACCEL m_hAccelGUserHotkey;
	HACCEL m_hAccelWUserHotkey;

	TimerCmdInfoList m_listTimerCmdInfo;
    HotkeyCmdInfoList m_listGHotKeyCmdInfo;
	HotkeyCmdInfoList m_listWHotKeyCmdInfo;
	SetColorCmdMap m_mapSetColorCmd;
	ActionMap m_mapOpenDlg;
	ActionMap m_mapMiscCmd;
	ShowElementCmdMap m_mapShowElementCmd;
	MiscConditionCmdMap m_mapMiscConditionCmd;
	
	Word * m_pw;
	CWordManager m_wm;
	
	GlobalSetting * m_pSet;
	
	CMeaningCtrl m_htmlMeaing;
	CPractiseResultDlg m_prDlg;

	// 初始化各个RichEdit
	void RenewRichEditStyles();
	void SetChildColors();
	void ChangeRicheditColors();

	void RestartRecite();
	void StartWordRecite();

	void ExecuteGlobalCommand();
	void ExecutePerwordCommand();

	void ShowWord(bool bShow);
	void ShowMeaning(bool bShow);
	void ShowAccesstime(time_t tt);

	void ResetElementsColor();

	void ShowPracticeResult();

	bool CheckPractice();

	// Set Element Color Command
	void SetWordColor(COLORREF cr);
	void SetWordBkColor(COLORREF cr);
	/*
	void SetPhoneticColor(COLORREF cr);
	void SetMeaningColor(COLORREF cr);
	void SetMeaningBkColor(COLORREF cr);
	*/

	afx_msg LRESULT OnTranslateAccel(WPARAM wp, LPARAM lp);
    afx_msg void OnUserHotkey(UINT nID);
	afx_msg void OnToggleWordType(UINT nID);
	//{{AFX_MSG(CSuperWordDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnNextword();
	afx_msg void OnPrevword();
	virtual void OnOK();
	afx_msg void OnChangeRicheditPractise();
	afx_msg void OnMsgfilterRicheditPractise(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnClose();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnOption();
	afx_msg void OnManageWordtype();
	afx_msg void OnBtnMenu();
	afx_msg void OnSetAccessTime();
	afx_msg void OnResetColors();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnUnsetAccessTime();
	afx_msg void OnHelp();
	afx_msg void OnToggleWordDetailMeaning();
	afx_msg void OnFirstword();
	afx_msg void OnLastword();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
	afx_msg void OnSetReciteScheme();
public:
    afx_msg void OnSetGlobalCmd();
public:
    afx_msg void OnToogleAccessTime();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SuperWordDLG_H__098B5DB9_E73F_4B24_8435_AA75ECD04461__INCLUDED_)
