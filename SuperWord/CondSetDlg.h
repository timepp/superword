#pragma once


// CCondSetDlg 对话框

class CCondSetDlg : public CDialog
{
	DECLARE_DYNAMIC(CCondSetDlg)

public:
	CCondSetDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCondSetDlg();

// 对话框数据
	enum { IDD = IDD_CONDSETDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
