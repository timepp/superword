// ColorPage.cpp : implementation file
//

#include "stdafx.h"
#include "SuperWord.h"
#include "ColorPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const TCHAR CColorPage::m_szCSSection[] = _T("Superword配色");
const TCHAR CColorPage::m_szCSKey[] = _T("color");
/////////////////////////////////////////////////////////////////////////////
// CColorPage property page

IMPLEMENT_DYNCREATE(CColorPage, CPropertyPage)

CColorPage::CColorPage() : CPropertyPage(CColorPage::IDD)
{
	//{{AFX_DATA_INIT(CColorPage)
	//}}AFX_DATA_INIT
	
}

CColorPage::~CColorPage()
{
}

void CColorPage::SetColorBtnDefaultColor()
{
	MainColor cr;

	m_btnWordcolor.SetDefaultColor(cr.crWord);
	m_btnWordbk.SetDefaultColor(cr.crWordBk);
	m_btnPracticecolor.SetDefaultColor(cr.crPractise);
	m_btnPracticebk.SetDefaultColor(cr.crPractiseBk);
	m_btnPhoneticscolor.SetDefaultColor(cr.crPhonetic);
	m_btnMeaningcolor.SetDefaultColor(cr.crMeaning);
	m_btnMeaningbk.SetDefaultColor(cr.crMeaningBk);
	m_btnDlgbk.SetDefaultColor(cr.crDlgBk);
	
	m_btnAccesstimecolor.SetDefaultColor(cr.crAccesstime);
	m_btnAccesstimebk.SetDefaultColor(cr.crAccesstimeBk);
	m_btnProgressbk.SetDefaultColor(cr.crProgressBk);
	m_btnProgresscr1.SetDefaultColor(cr.crProgress1);
	m_btnProgresscr2.SetDefaultColor(cr.crProgress2);
	m_btnProgresscolor.SetDefaultColor(cr.crProgressFont);
	m_btnTypeactive.SetDefaultColor(cr.crWordTypeActive);
	m_btnTypebk.SetDefaultColor(cr.crWordTypeInactive);
	m_btnTypeborder.SetDefaultColor(cr.crWordTypeBorder);
	
	m_btnMsFace.SetDefaultColor(cr.crMsFace);
	m_btnMsHighlight.SetDefaultColor(cr.crMsHighlight);
	m_btnMsShadow.SetDefaultColor(cr.crMsShadow);
	m_btnMsArrow.SetDefaultColor(cr.crMsArrow);
	m_btnMsBase.SetDefaultColor(cr.crMsBase);
	m_btnMsDarkshadow.SetDefaultColor(cr.crMsDarkshadow);
}

void CColorPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CColorPage)
	DDX_Control(pDX, IDC_BTN_MS_DARKSHADOW, m_btnMsDarkshadow);
	DDX_Control(pDX, IDC_BTN_MS_SHADOW, m_btnMsShadow);
	DDX_Control(pDX, IDC_BTN_MS_HIGHLIGHT, m_btnMsHighlight);
	DDX_Control(pDX, IDC_BTN_MS_FACE, m_btnMsFace);
	DDX_Control(pDX, IDC_BTN_MS_BASE, m_btnMsBase);
	DDX_Control(pDX, IDC_BTN_MS_ARROW, m_btnMsArrow);
	DDX_Control(pDX, IDC_BTN_PROGRESSCR2, m_btnProgresscr2);
	DDX_Control(pDX, IDC_BTN_TYPEBORDER, m_btnTypeborder);
	DDX_Control(pDX, IDC_BTN_TYPEBK, m_btnTypebk);
	DDX_Control(pDX, IDC_BTN_TYPEACTIVE, m_btnTypeactive);
	DDX_Control(pDX, IDC_BTN_PROGRESSCR1, m_btnProgresscr1);
	DDX_Control(pDX, IDC_BTN_PROGRESSCHAR, m_btnProgresscolor);
	DDX_Control(pDX, IDC_BTN_PROGRESSBK, m_btnProgressbk);
	DDX_Control(pDX, IDC_BTN_ACCESSTIMECOLOR, m_btnAccesstimecolor);
	DDX_Control(pDX, IDC_BTN_ACCESSTIMEBK, m_btnAccesstimebk);
	DDX_Control(pDX, IDC_BTN_WORDCOLOR, m_btnWordcolor);
	DDX_Control(pDX, IDC_BTN_WORDBK, m_btnWordbk);
	DDX_Control(pDX, IDC_BTN_PRICTICECOLOR, m_btnPracticecolor);
	DDX_Control(pDX, IDC_BTN_PRACTICEBK, m_btnPracticebk);
	DDX_Control(pDX, IDC_BTN_PHONETICSCOLOR, m_btnPhoneticscolor);
	DDX_Control(pDX, IDC_BTN_MEANINGCOLOR, m_btnMeaningcolor);
	DDX_Control(pDX, IDC_BTN_MEANINGBK, m_btnMeaningbk);
	DDX_Control(pDX, IDC_BTN_DLGBK, m_btnDlgbk);
	//}}AFX_DATA_MAP

	GlobalSetting *pSet = GlobalSetting::Instance();
	if (pDX->m_bSaveAndValidate)
	{
		// 控件流向成员变量
		pSet->Cr.crWord = m_btnWordcolor.GetColor();
		pSet->Cr.crWordBk = m_btnWordbk.GetColor();
		pSet->Cr.crPractise = m_btnPracticecolor.GetColor();
		pSet->Cr.crPractiseBk = m_btnPracticebk.GetColor();
		pSet->Cr.crPhonetic = m_btnPhoneticscolor.GetColor();
		pSet->Cr.crMeaning = m_btnMeaningcolor.GetColor();
		pSet->Cr.crMeaningBk = m_btnMeaningbk.GetColor();
		pSet->Cr.crDlgBk = m_btnDlgbk.GetColor();

		pSet->Cr.crAccesstime = m_btnAccesstimecolor.GetColor();
		pSet->Cr.crAccesstimeBk = m_btnAccesstimebk.GetColor();
		pSet->Cr.crProgressBk = m_btnProgressbk.GetColor();
		pSet->Cr.crProgress1 = m_btnProgresscr1.GetColor();
		pSet->Cr.crProgress2 = m_btnProgresscr2.GetColor();
		pSet->Cr.crProgressFont = m_btnProgresscolor.GetColor();
		pSet->Cr.crWordTypeActive = m_btnTypeactive.GetColor();
		pSet->Cr.crWordTypeInactive = m_btnTypebk.GetColor();
		pSet->Cr.crWordTypeBorder = m_btnTypeborder.GetColor();
		
		pSet->Cr.crMsFace = m_btnMsFace.GetColor();
		pSet->Cr.crMsHighlight = m_btnMsHighlight.GetColor();
		pSet->Cr.crMsShadow = m_btnMsShadow.GetColor();
		pSet->Cr.crMsArrow = m_btnMsArrow.GetColor();
		pSet->Cr.crMsBase = m_btnMsBase.GetColor();
		pSet->Cr.crMsDarkshadow = m_btnMsDarkshadow.GetColor();
	}
	else
	{
		m_btnWordcolor.SetColor(pSet->Cr.crWord);
		m_btnWordbk.SetColor(pSet->Cr.crWordBk);
		m_btnPracticecolor.SetColor(pSet->Cr.crPractise);
		m_btnPracticebk.SetColor(pSet->Cr.crPractiseBk);
		m_btnPhoneticscolor.SetColor(pSet->Cr.crPhonetic);
		m_btnMeaningcolor.SetColor(pSet->Cr.crMeaning);
		m_btnMeaningbk.SetColor(pSet->Cr.crMeaningBk);
		m_btnDlgbk.SetColor(pSet->Cr.crDlgBk);
		
		m_btnAccesstimecolor.SetColor(pSet->Cr.crAccesstime);
		m_btnAccesstimebk.SetColor(pSet->Cr.crAccesstimeBk);
		m_btnProgressbk.SetColor(pSet->Cr.crProgressBk);
		m_btnProgresscr1.SetColor(pSet->Cr.crProgress1);
		m_btnProgresscr2.SetColor(pSet->Cr.crProgress2);
		m_btnProgresscolor.SetColor(pSet->Cr.crProgressFont);
		m_btnTypeactive.SetColor(pSet->Cr.crWordTypeActive);
		m_btnTypebk.SetColor(pSet->Cr.crWordTypeInactive);
		m_btnTypeborder.SetColor(pSet->Cr.crWordTypeBorder);
		
		m_btnMsFace.SetColor(pSet->Cr.crMsFace);
		m_btnMsHighlight.SetColor(pSet->Cr.crMsHighlight);
		m_btnMsShadow.SetColor(pSet->Cr.crMsShadow);
		m_btnMsArrow.SetColor(pSet->Cr.crMsArrow);
		m_btnMsBase.SetColor(pSet->Cr.crMsBase);
		m_btnMsDarkshadow.SetColor(pSet->Cr.crMsDarkshadow);
	}
}


BEGIN_MESSAGE_MAP(CColorPage, CPropertyPage)
	//{{AFX_MSG_MAP(CColorPage)
	//}}AFX_MSG_MAP
	ON_MESSAGE(CBM_COLORCHANGE, OnColorChange)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorPage message handler

BOOL CColorPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	SetColorBtnDefaultColor();	

	// 弹出窗口的帮助
	CPopupHelpStyle::CreateDecorator(this);
	CScrollableStyle::CreateDecorator(this);
	
	return TRUE;
}

LRESULT CColorPage::OnColorChange(WPARAM wp, LPARAM lp)
{
	CPropertyPage *pp = (CPropertyPage *)GetParent();
	pp->SetModified();

	return 1;
}

void CColorPage::LoadColorscheme() 
{
	CFileDialog dlg(TRUE, _T("swcs"), NULL, 0, _T("Superword配色文件(*.swcs)|*.swcs|所有文件(*.*)|*.*||"));
	dlg.m_ofn.lpstrInitialDir = helper::SWPath(helper::IDS(IDSP_COLOR_SCHEME));
	if (dlg.DoModal() == IDOK)
	{
		CString strFile = dlg.GetPathName();
		GlobalSetting::Instance()->Cr.LoadSetting(m_szCSSection, m_szCSKey, strFile);
		UpdateData(FALSE);
	}		
}

void CColorPage::SaveColorscheme() 
{
	CFileDialog dlg(FALSE, _T("swcs"), NULL, OFN_OVERWRITEPROMPT, _T("Superword配色文件(*.swcs)|*.swcs|所有文件(*.*)|*.*||"));
	dlg.m_ofn.lpstrInitialDir = helper::SWPath(helper::IDS(IDSP_COLOR_SCHEME));
	if (dlg.DoModal() == IDOK)
	{
		CString strFile = dlg.GetPathName();
		GlobalSetting::Instance()->Cr.SaveSetting(m_szCSSection, m_szCSKey, strFile);
	}	
}
