//

#include "stdafx.h"
#include "SuperWord.h"
#include "CSMeaningDlg.h"
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
// CCSMeaningDlg dialog

CCSMeaningDlg::CCSMeaningDlg(CWnd* pParent /*=NULL*/)
	: CCSRootDlg(CCSMeaningDlg::IDD, pParent)
    , m_bMatchDetail(FALSE)
{
	//{{AFX_DATA_INIT(CCSMeaningDlg)
	m_strMatcher = _T("");
	//}}AFX_DATA_INIT
}


void CCSMeaningDlg::DoDataExchange(CDataExchange* pDX)
{
    cond::MeaningCondition * pCond = dynamic_cast<cond::MeaningCondition *>(m_pComp);
    CCSRootDlg::DoDataExchange(pDX);
    if (!pDX->m_bSaveAndValidate)
    {
        regex::rpattern pat("(.*) (.*)");
        regex::match_results ret;
        string str = pCond->GetConfiguration();
        pat.match(str, ret);
        m_bMatchDetail = (ret.backref(1).str().at(0) != '0');
        m_strMatcher = ret.backref(2).str().c_str();
    }

    //{{AFX_DATA_MAP(CCSMeaningDlg)
    DDX_Text(pDX, IDC_EDIT_MATCHER, m_strMatcher);
    DDX_Check(pDX, IDC_CHECK_MATCH_DETAIL_MEANING, m_bMatchDetail);
    //}}AFX_DATA_MAP

    if (pDX->m_bSaveAndValidate)
    {
        stringstream ss;
        ss << m_bMatchDetail << " " << m_strMatcher;
        m_pComp->Configure(ss.str());
    }
    
}


BEGIN_MESSAGE_MAP(CCSMeaningDlg, CCSRootDlg)
	//{{AFX_MSG_MAP(CCSMeaningDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCSMeaningDlg message handlers
