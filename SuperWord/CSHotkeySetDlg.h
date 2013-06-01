#pragma once

#include "CSRootDlg.h"
#include "afxcmn.h"
#include "MyHotkeyCtrl.h"

// CCSHotkeySetDlg dialog

namespace compdlg
{


class CCSHotkeySetDlg : public CCSRootDlg
{

public:
	CCSHotkeySetDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCSHotkeySetDlg();

// Dialog Data
	enum { IDD = IDD_CS_HOTKEY_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
    CMyHotKeyCtrl m_hotkey;
public:
    virtual BOOL OnInitDialog();
protected:
    virtual void OnOK();
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

}