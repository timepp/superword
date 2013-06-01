// CSAccessTimeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SuperWord.h"
#include "CSAccessTimeDlg.h"
#include "ConcreteCondition.h"
#include <sstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


using namespace compdlg;
using namespace comp;
using namespace std;
/////////////////////////////////////////////////////////////////////////////
// CCSAccessTimeDlg dialog


CCSAccessTimeDlg::CCSAccessTimeDlg(CWnd* pParent /*=NULL*/)
	: CCSRootDlg(CCSAccessTimeDlg::IDD, pParent)
    , m_relaTime(0)
{
	//{{AFX_DATA_INIT(CCSAccessTimeDlg)
	m_bHasTmMin = FALSE;
	m_bHasTmMax = FALSE;
	//}}AFX_DATA_INIT
}


void CCSAccessTimeDlg::DoDataExchange(CDataExchange* pDX)
{
    CCSRootDlg::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(CCSAccessTimeDlg)
    DDX_Control(pDX, IDC_CHECK_TMMIN, m_chkTmMin);
    DDX_Control(pDX, IDC_CHECK_TMMAX, m_chkTmMax);
    DDX_Control(pDX, IDC_DATETIMEPICKER_TMMIN, m_dcMin);
    DDX_Control(pDX, IDC_DATETIMEPICKER_TMMAX, m_dcMax);
    DDX_Check(pDX, IDC_CHECK_TMMAX, m_bHasTmMax);
    DDX_Check(pDX, IDC_CHECK_TMMIN, m_bHasTmMin);
    //}}AFX_DATA_MAP

    DDX_Control(pDX, IDC_STATIC_USEABSDATE, m_cgAbsDate);
    DDX_Control(pDX, IDC_STATIC_USERELADATE, m_cgRelaDate);
    DDX_Text(pDX, IDC_EDIT_DAYBEFORE, m_relaTime);
}


BEGIN_MESSAGE_MAP(CCSAccessTimeDlg, CCSRootDlg)
	//{{AFX_MSG_MAP(CCSAccessTimeDlg)
	ON_BN_CLICKED(IDC_CHECK_TMMIN, OnCheckTmmin)
	ON_BN_CLICKED(IDC_CHECK_TMMAX, OnCheckTmmax)
	ON_BN_CLICKED(IDC_BUTTON_ALLRECITED, OnButtonAllrecited)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCSAccessTimeDlg message handlers

BOOL CCSAccessTimeDlg::OnInitDialog() 
{
    bool bRelative;
    time_t tm_min, tm_max;
    cond::AccesstimeCondition * pCond = dynamic_cast<cond::AccesstimeCondition *>(m_pComp);
    string str = pCond->GetConfiguration();
    stringstream ss(str);

    ss >> bRelative >> m_relaTime >> m_bHasTmMin >> m_bHasTmMax
        >> tm_min >> tm_max;

	CCSRootDlg::OnInitDialog();

	m_cgAbsDate.SetTitleStyle(BS_AUTORADIOBUTTON);
	m_cgRelaDate.SetTitleStyle(BS_AUTORADIOBUTTON);
	m_cgAbsDate.SetGroupID(0);
	m_cgRelaDate.SetGroupID(0);

	m_cgAbsDate.SetCheck(!bRelative);
	m_cgRelaDate.SetCheck(bRelative);
	m_dcMin.SetTime(tm_min);
	m_dcMax.SetTime(tm_max);

    return TRUE;
}

void CCSAccessTimeDlg::OnCheckTmmin() 
{
	if (!m_chkTmMin.GetCheck() && !m_chkTmMax.GetCheck())
	{
		m_chkTmMax.SetCheck(1);
	}
//	SyncDatePicker();
}

void CCSAccessTimeDlg::OnCheckTmmax() 
{
	if (!m_chkTmMin.GetCheck() && !m_chkTmMax.GetCheck())
	{
		m_chkTmMin.SetCheck(1);
	}
//	SyncDatePicker();
}

void CCSAccessTimeDlg::SyncDatePicker()
{
	GetDlgItem(IDC_DATETIMEPICKER_TMMIN)->EnableWindow(m_chkTmMin.GetCheck());
	GetDlgItem(IDC_DATETIMEPICKER_TMMAX)->EnableWindow(m_chkTmMax.GetCheck());
}

void CCSAccessTimeDlg::OnButtonAllrecited() 
{
	// 所有背诵过的单词，指m_tmMin > 2000-1-1, m_tmMax = -1
	m_chkTmMin.SetCheck(1);
	m_chkTmMax.SetCheck(0);
	m_dcMin.SetTime(COleDateTime(2000, 1, 1, 0, 0, 0));
}

void compdlg::CCSAccessTimeDlg::OnOK()
{
    CCSRootDlg::OnOK();
    
    stringstream ss;
    CTime tmMin, tmMax;
    cond::AccesstimeCondition * pCond = dynamic_cast<cond::AccesstimeCondition *>(m_pComp);

    m_dcMin.GetTime(tmMin);
    m_dcMax.GetTime(tmMax);
    ss  << m_cgRelaDate.GetCheck() << " "
        << m_relaTime << " " << m_bHasTmMin << " " << m_bHasTmMax << " " 
        << helper::GetTimet(tmMin) << " " << helper::GetTimet(tmMax);
   
    pCond->Configure(ss.str());
} 
