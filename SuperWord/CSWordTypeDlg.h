#pragma once

#include "CSRootDlg.h"
#include "afxwin.h"

namespace compdlg
{

	class CCSWordTypeDlg : public CCSRootDlg
	{

	public:
		CCSWordTypeDlg(CWnd* pParent = NULL);   // standard constructor
		virtual ~CCSWordTypeDlg();

		// Dialog Data
		enum { IDD = IDD_CS_WORDTYPE_DLG };

	protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

		DECLARE_MESSAGE_MAP()
	public:
		CComboBox m_cbWordType;
		int m_nStyle;
		virtual BOOL OnInitDialog();
	protected:
		virtual void OnOK();
	};

}