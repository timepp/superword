#pragma once

#include "CSRootDlg.h"
#include "afxwin.h"

// CCSTimerCmdSetDlg dialog

namespace compdlg
{

class CCSTimerCmdSetDlg : public CCSRootDlg
{

public:
	CCSTimerCmdSetDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCSTimerCmdSetDlg();

// Dialog Data
	enum { IDD = IDD_CS_INTERVAL_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
    UINT m_interval;
protected:
    virtual void OnOK();
public:
    virtual BOOL OnInitDialog();
	CComboBox m_cbRepeatTime;
	CString m_strRepeatTime;
	BOOL m_delete_on_word_change;
};

}