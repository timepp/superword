// CondSetDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SuperWord.h"
#include "CondSetDlg.h"


// CCondSetDlg 对话框

IMPLEMENT_DYNAMIC(CCondSetDlg, CDialog)
CCondSetDlg::CCondSetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCondSetDlg::IDD, pParent)
{
}

CCondSetDlg::~CCondSetDlg()
{
}

void CCondSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCondSetDlg, CDialog)
END_MESSAGE_MAP()


// CCondSetDlg 消息处理程序
