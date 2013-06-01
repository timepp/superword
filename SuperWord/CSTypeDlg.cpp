// CSTypeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SuperWord.h"
#include "CSTypeDlg.h"
#include "WordType.h"

#include <sstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace compdlg;
using namespace std;

/////////////////////////////////////////////////////////////////////////////
// CCSTypeDlg dialog


CCSTypeDlg::CCSTypeDlg(CWnd* pParent /*=NULL*/)
	: CCSRootDlg(CCSTypeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCSTypeDlg)
	//}}AFX_DATA_INIT
}


void CCSTypeDlg::DoDataExchange(CDataExchange* pDX)
{
	CCSRootDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCSTypeDlg)
	DDX_Control(pDX, IDC_COMBO_TYPELIST, m_cbType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCSTypeDlg, CCSRootDlg)
	//{{AFX_MSG_MAP(CCSTypeDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCSTypeDlg message handlers

BOOL CCSTypeDlg::OnInitDialog() 
{
	CCSRootDlg::OnInitDialog();
	WordType *wt = WordType::Instance();
	const StringVector& sv = wt->GetAllType();
	int cursel = -1;
	int i;

	std::string str_type = m_pComp->GetConfiguration();

	StringVector::const_iterator ci;
	for (ci = sv.begin(), i = 0; ci != sv.end(); ++ci, i++)
	{
		if (str_type == *ci) cursel = i;
		m_cbType.AddString((*ci).c_str());
	}

	m_cbType.SetCurSel(cursel);
	
	return TRUE;
}

void compdlg::CCSTypeDlg::OnOK()
{
	CString str;
	m_cbType.GetLBText(m_cbType.GetCurSel(), str);
	m_pComp->Configure((LPCTSTR)str);
	
	CCSRootDlg::OnOK();
}
