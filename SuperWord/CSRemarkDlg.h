#pragma once

#include "CSRootDlg.h"

namespace compdlg
{

	class CCSRemarkDlg : public CCSRootDlg
	{

	public:
		CCSRemarkDlg(CWnd* pParent = NULL);   // standard constructor
		virtual ~CCSRemarkDlg();

		// Dialog Data
		enum { IDD = IDD_CS_REMARK_DLG };

	protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

		DECLARE_MESSAGE_MAP()
	public:
		CString m_strRemark;
		virtual BOOL OnInitDialog();
	protected:
		virtual void OnOK();
	};

}