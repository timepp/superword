// TestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "superword.h"
#include "TestDlg.h"

#include <fstream>
#include ".\testdlg.h"

#include "CSWordDlg.h"
#include "CSPhoneticDlg.h"
#include "CSTypeDlg.h"
#include "CSMeaningDlg.h"
#include "CSAccessTimeDlg.h"
#include "CSClassDlg.h"

#include "composite.h"
#include "ConcreteCondition.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace comp;

/////////////////////////////////////////////////////////////////////////////
// CTestDlg dialog


CTestDlg::CTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestDlg)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_TESTTREE, m_tree);
}


BEGIN_MESSAGE_MAP(CTestDlg, CDialog)
	//{{AFX_MSG_MAP(CTestDlg)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
    ON_WM_CLOSE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestDlg message handlers

int CTestDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	
	return 0;
}

BOOL CTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

    static CompInfoVector civ;
    static CCSWordDlg dlgWord;
    static CCSPhoneticDlg dlgPhonetic;
    static CCSMeaningDlg dlgMeaning;

    civ.clear();

	return TRUE;
}

void CTestDlg::OnClose()
{
    std::ofstream os("c:\\test1.txt");
    m_pComp->Save(os);
    delete m_pComp;

    CDialog::OnClose();
}
