#pragma once


// CCondSetDlg �Ի���

class CCondSetDlg : public CDialog
{
	DECLARE_DYNAMIC(CCondSetDlg)

public:
	CCondSetDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCondSetDlg();

// �Ի�������
	enum { IDD = IDD_CONDSETDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
