#pragma once

#include "CSRootDlg.h"
#include "afxwin.h"

namespace compdlg
{

	class CCSMiscCondDlg : public CCSRootDlg
	{

	public:
		CCSMiscCondDlg(CWnd* pParent = NULL);   // standard constructor
		virtual ~CCSMiscCondDlg();

		// Dialog Data
		enum { IDD = IDD_CS_MISC_COND_DLG };

	protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

		DECLARE_MESSAGE_MAP()
		virtual void OnOK();
	public:
		virtual BOOL OnInitDialog();
		CComboBox m_cbMiscCond;
	};

}