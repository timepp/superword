#pragma once

#include "CSRootDlg.h"
#include "afxwin.h"

namespace compdlg
{

	class CCSMiscDlg : public CCSRootDlg
	{

	public:
		CCSMiscDlg(CWnd* pParent = NULL);   // standard constructor
		virtual ~CCSMiscDlg();

		// Dialog Data
		enum { IDD = IDD_CS_MISC_DLG };

	protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

		DECLARE_MESSAGE_MAP()
	public:
		virtual BOOL OnInitDialog();
	protected:
		virtual void OnOK();
	public:
		CString m_strMiscCmd;
		CComboBox m_cbMiscCmd;
	};

}