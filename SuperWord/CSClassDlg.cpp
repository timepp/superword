// CSClassDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SuperWord.h"
#include "CSClassDlg.h"
#include "Composite.h"
#include "ConcreteCondition.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace compdlg;
using namespace comp;
/////////////////////////////////////////////////////////////////////////////
// CCSClassDlg dialog


CCSClassDlg::CCSClassDlg(CWnd* pParent /*=NULL*/)
	: CCSRootDlg(CCSClassDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCSClassDlg)
	m_strWordClass = _T("");
	//}}AFX_DATA_INIT
}


void CCSClassDlg::DoDataExchange(CDataExchange* pDX)
{
	CCSRootDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCSClassDlg)
	DDX_Text(pDX, IDC_EDIT_WORD_CLASS, m_strWordClass);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCSClassDlg, CCSRootDlg)
	//{{AFX_MSG_MAP(CCSClassDlg)
	ON_BN_CLICKED(IDC_BTN_SELECT_WORD_CLASS, OnBtnSelectWordClass)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCSClassDlg message handlers

BOOL CCSClassDlg::OnInitDialog() 
{
    cond::ClassCondition * pCond = dynamic_cast<cond::ClassCondition *>(m_pComp);
	m_strWordClass = pCond->GetConfiguration().c_str();

	CCSRootDlg::OnInitDialog();

	return TRUE;
}

void CCSClassDlg::OnBtnSelectWordClass() 
{
	CString strFile;
	CString strClassSubDir = helper::SWPath(helper::IDS(IDSP_WORD_CLASS));
	strFile.Format(_T("%s\\%s.txt"), strClassSubDir, m_strWordClass);

	CFileDialog dlg(TRUE, _T("txt"), strFile, 
		OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_READONLY,
		_T("单词类别(*.txt)|*.txt||"));
	if (dlg.DoModal() == IDOK)
	{
        CString str = dlg.GetPathName();
        if (_tcsnicmp(str, strClassSubDir, strClassSubDir.GetLength()) != 0)
        {
            AfxMessageBox("您所选择的文件没有在\"单词类别\"目录下");
            return;
        }

        str = str.Right(str.GetLength() - strClassSubDir.GetLength() - 1);
        if (str.Right(4).CompareNoCase(_T(".txt")) != 0)
        {
            AfxMessageBox("您必须选择一个文本(.txt)文件");
            return;
        }

        m_strWordClass = str.Left(str.GetLength() - 4);
		UpdateData(FALSE);
	}
}

void CCSClassDlg::OnOK()
{
    CCSRootDlg::OnOK();

    cond::ClassCondition * pCond = dynamic_cast<cond::ClassCondition *>(m_pComp);
    pCond->Configure((LPCTSTR)m_strWordClass);
}
