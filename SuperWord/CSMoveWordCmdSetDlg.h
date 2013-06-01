#pragma once

#include "CSRootDlg.h"
#include "afxwin.h"

// CCSMoveWordCmdSetDlg dialog
namespace compdlg
{


class CCSMoveWordCmdSetDlg : public CCSRootDlg
{

public:
	CCSMoveWordCmdSetDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCSMoveWordCmdSetDlg();

// Dialog Data
	enum { IDD = IDD_CS_MOVEWORD_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnInitDialog();
protected:
    virtual void OnOK();
public:
    CComboBox m_cbMoveWordCmd;
};

}