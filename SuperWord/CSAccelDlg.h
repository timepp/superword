#pragma once

#include "CSRootDlg.h"
#include "afxwin.h"

namespace compdlg
{
	class CCSAccelDlg : public CCSRootDlg
	{
		// Types
		struct VkInfo
		{
			int state;
			char name[32];
		};

	public:
		CCSAccelDlg(CWnd* pParent = NULL);   // standard constructor
		virtual ~CCSAccelDlg();

		// Dialog Data
		enum { IDD = IDD_CS_ACCEL_DLG };

	protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

		DECLARE_MESSAGE_MAP()
	private:
		BOOL m_bAlt;
		BOOL m_bControl;
		BOOL m_bShift;
		CComboBox m_cbVirtualKey;
		static VkInfo m_infoVk[256];
		static const int NORM;
		static const int HIDE;
		static const int ESTP;
	public:
		virtual BOOL OnInitDialog();
	protected:
		virtual void OnOK();
	public:
		virtual BOOL PreTranslateMessage(MSG* pMsg);
		BOOL m_bGlobal;
	};

}