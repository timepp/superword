#pragma once

#include "CSRootDlg.h"
#include "ResizableStyle.h"

namespace compdlg
{

	class CCSReciteSchemeDlg : public CCSRootDlg, public CResizableStyle
	{

	public:
		CCSReciteSchemeDlg(CWnd* pParent = NULL);   // standard constructor
		virtual ~CCSReciteSchemeDlg();

		// Dialog Data
		enum { IDD = IDD_CS_LOAD_RECITE_SCHEME_DLG };

	protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

		DECLARE_MESSAGE_MAP()
	public:
		virtual BOOL OnInitDialog();
	protected:
		virtual void OnOK();
	public:
		CString m_strReciteSchemeFile;
		virtual BOOL PreTranslateMessage(MSG* pMsg);
	};

}