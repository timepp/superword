// GlobalCmdSetDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SuperWord.h"
#include "GlobalCmdSetDlg.h"

#include "Helper.h"

#include "ConcreteCondition.h"
#include "ConcreteCommand.h"

#include <sstream>
#include <fstream>

using namespace helper;
using namespace comp;
using namespace compdlg;
using namespace std;

// CGlobalCmdSetDlg dialog

IMPLEMENT_DYNAMIC(CGlobalCmdSetDlg, CDialog)

CGlobalCmdSetDlg::CGlobalCmdSetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGlobalCmdSetDlg::IDD, pParent)
		, m_rootGlobalCmd(command, 1)
{

}

CGlobalCmdSetDlg::~CGlobalCmdSetDlg()
{
}

void CGlobalCmdSetDlg::SetChildItemResizeInfo()
{
	SetDlgItemResizeInfo(IDC_TREE_GLOBAL_CMD,   WRS_SYNWIDTH | WRS_SYNHEIGHT);
	SetDlgItemResizeInfo(IDOK,                  WRS_RIGHT | WRS_BOTTOM);
	SetDlgItemResizeInfo(IDCANCEL,              WRS_RIGHT | WRS_BOTTOM);
}

void CGlobalCmdSetDlg::FillCompInfo()
{
	m_civ.clear();

	m_civ.push_back(CompInfo(cond::AndCondition().GetName(), IDI_AND));
	m_civ.push_back(CompInfo(cond::OrCondition().GetName(), IDI_OR));
	m_civ.push_back(CompInfo(cond::NotCondition().GetName(), IDI_NOT));
	m_civ.push_back(CompInfo(cmd::SeriesCommand().GetName(), IDI_SERIES_CMD, &m_dlgRemark));
	m_civ.push_back(CompInfo(cmd::RandomCommand().GetName(), IDI_RANDOM_CMD, &m_dlgRemark));
	m_civ.push_back(CompInfo(cmd::IfCommand().GetName(), IDI_IF_CMD));
	m_civ.push_back(CompInfo(cmd::TimerCommand().GetName(), IDI_TIMER_CMD, &m_dlgTimerCmd));
	m_civ.push_back(CompInfo(cmd::HotkeyCommand().GetName(), IDI_HOTKEY_CMD, &m_dlgAccel));

	m_civ.push_back(CompInfo("", IDI_NOT));

	m_civ.push_back(CompInfo(cond::WordCondition().GetName(), IDI_WORD, &m_dlgWord));
	m_civ.push_back(CompInfo(cond::MeaningCondition().GetName(), IDI_MEANING, &m_dlgMeaning));
	m_civ.push_back(CompInfo(cond::PhoneticCondition().GetName(), IDI_PHONETIC, &m_dlgPhonetic));
	m_civ.push_back(CompInfo(cond::AccesstimeCondition().GetName(), IDI_ACCESS_TIME, &m_dlgAccesstime));
	m_civ.push_back(CompInfo(cond::ClassCondition().GetName(), IDI_CLASS, &m_dlgClass));
	m_civ.push_back(CompInfo(cond::TypeCondition().GetName(), IDI_TYPE, &m_dlgType));
	m_civ.push_back(CompInfo(cond::MiscCondition().GetName(), IDI_MISC_CMD, &m_dlgMiscCond));
	m_civ.push_back(CompInfo(cmd::MoveWordCommand().GetName(), IDI_MOVEWORD_CMD, &m_dlgMoveWord));
	m_civ.push_back(CompInfo(cmd::SetColorCommand().GetName(), IDI_SETCOLOR_CMD, &m_dlgSetColor));
	m_civ.push_back(CompInfo(cmd::OpenDlgCommand().GetName(), IDI_OPENDLG_CMD, &m_dlgOpenDlg));
	m_civ.push_back(CompInfo(cmd::ShowElementCommand().GetName(), IDI_SHOWELEMENT_CMD, &m_dlgShowElement));
	m_civ.push_back(CompInfo(cmd::SetWordTypeCommand().GetName(), IDI_SETWORDTYPE_CMD, &m_dlgWordType));
	m_civ.push_back(CompInfo(cmd::MiscCommand().GetName(), IDI_MISC_CMD, &m_dlgMisc));
	m_civ.push_back(CompInfo(cmd::LoadCompCommand().GetName(), IDI_LOADCOMP_CMD, &m_dlgReciteScheme));
}

void CGlobalCmdSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE_GLOBAL_CMD, m_tcGCmd);
}


BEGIN_MESSAGE_MAP(CGlobalCmdSetDlg, CDialog)
//	ON_BN_CLICKED(IDOK, &CGlobalCmdSetDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CGlobalCmdSetDlg message handlers

BOOL CGlobalCmdSetDlg::OnInitDialog()
{
	__super::OnInitDialog();

	// TODO:  Add extra initialization here
	CPopupHelpStyle::CreateDecorator(this);
	CResizableStyle::CreateDecorator(this);

	SetChildItemResizeInfo();
	FillCompInfo();

	m_tcGCmd.InitTree(&m_civ, &m_rootGlobalCmd, SWPath(IDS(IDSP_GLOBAL_CMD)), _T("cmd"));
	m_tcGCmd.LoadComposite(SWPath(IDS(IDSFN_GLOBAL_CMD)));

	m_rootGlobalCmd.Save(m_ssOldGlobalCmd);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CGlobalCmdSetDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	stringstream ssGlobalCmd;
	m_rootGlobalCmd.Save(ssGlobalCmd);

	if (m_ssOldGlobalCmd.str() != ssGlobalCmd.str())
	{
		m_bGlobalCmdChanged = TRUE;
		m_tcGCmd.SaveComposite(SWPath(IDS(IDSFN_GLOBAL_CMD)));
	}

	__super::OnOK();
}
