#if !defined(AFX_HAPPYBIRTHDAYDLG_H__854F83B5_DA87_480F_809A_226203E5B922__INCLUDED_)
#define AFX_HAPPYBIRTHDAYDLG_H__854F83B5_DA87_480F_809A_226203E5B922__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HappyBirthdayDlg.h : header file
//
#define MAX_FONT 256
class CFlyWord
{
public:
	CFlyWord();
	~CFlyWord();

	void InitState();
	void Move();
	void Draw(CDC *pDC);

	static void SetWorldRect(CRect &rc);

private:
	static void InitFonts();

	static CRect s_rcWorld;
	static int s_rBirth;
	static CFont s_font[];

	double m_fontIndex;
	double m_Angle;
	double m_x;
	double m_y;
	COLORREF m_cr;
	int m_speed;
	double m_font_inc_speed; 
	const char * m_pWord;
};

/////////////////////////////////////////////////////////////////////////////
// CHappyBirthdayDlg dialog
#define MAX_WORD 16
class CHappyBirthdayDlg : public CDialog
{
// Construction
public:
	CHappyBirthdayDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CHappyBirthdayDlg)
	enum { IDD = IDD_HAPPY_BIRTHDAY };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHappyBirthdayDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:	
	CDC m_mDC;
	CDC m_mDC2;
	CBitmap m_mBmp;
	CBitmap m_mBmp2;
	CFlyWord m_fw[MAX_WORD];
	CString m_strInfo;

	BOOL m_bShowInfo;

	BOOL InitialMemDC(CDC *pDC);
	CRect m_rcTip;
	// Generated message map functions
	//{{AFX_MSG(CHappyBirthdayDlg)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HAPPYBIRTHDAYDLG_H__854F83B5_DA87_480F_809A_226203E5B922__INCLUDED_)
