#pragma once

#include "CSRootDlg.h"
#include "afxwin.h"

namespace compdlg
{

	class CCSShowElementDlg : public CCSRootDlg
	{

	public:
		CCSShowElementDlg(CWnd* pParent = NULL);   // standard constructor
		virtual ~CCSShowElementDlg();

		// Dialog Data
		enum { IDD = IDD_CS_SHOW_ELEMENT_DLG };

	protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

		DECLARE_MESSAGE_MAP()
	public:
		virtual BOOL OnInitDialog();
	protected:
		virtual void OnOK();
	public:
		BOOL m_bShow;
		CComboBox m_cbVisualElement;
	};

}