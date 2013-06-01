#if !defined(AFX_TRANSIMGDLG_H__3932BCD8_F76A_4ED5_A24B_8264EDFD2D2D__INCLUDED_)
#define AFX_TRANSIMGDLG_H__3932BCD8_F76A_4ED5_A24B_8264EDFD2D2D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TransImgDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTransImgDlg dialog

class CTransImgDlg : public CDialog
{
// Construction
public:
	CTransImgDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTransImgDlg)
	enum { IDD = IDD_TRANS_IMG_DLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTransImgDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTransImgDlg)
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRANSIMGDLG_H__3932BCD8_F76A_4ED5_A24B_8264EDFD2D2D__INCLUDED_)
