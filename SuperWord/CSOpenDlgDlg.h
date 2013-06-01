#pragma once

#include "CSRootDlg.h"
#include "afxwin.h"

namespace compdlg
{

	class CCSOpenDlgDlg : public CCSRootDlg
	{

	public:
		CCSOpenDlgDlg(CWnd* pParent = NULL);   // standard constructor
		virtual ~CCSOpenDlgDlg();

		// Dialog Data
		enum { IDD = IDD_CS_OPENDLG_DLG };

	protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

		DECLARE_MESSAGE_MAP()
	public:
		virtual BOOL OnInitDialog();
	protected:
		virtual void OnOK();
	public:
		CComboBox m_cbDlgs;
	};

}