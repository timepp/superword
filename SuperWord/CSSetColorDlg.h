#pragma once

#include "CSRootDlg.h"
#include "afxwin.h"
#include "LibSrc/ColorBtn/ColorButton.h"

namespace compdlg
{

	class CCSSetColorDlg : public CCSRootDlg
	{

	public:
		CCSSetColorDlg(CWnd* pParent = NULL);   // standard constructor

		// Dialog Data
		enum { IDD = IDD_CS_SETCOLOR_DLG };

	protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

		DECLARE_MESSAGE_MAP()
	public:
		virtual BOOL OnInitDialog();
	private:
		CColorButton m_btnSetColor;
	public:
		CComboBox m_cbColorElem;
	protected:
		virtual void OnOK();
	};

}