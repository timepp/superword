// ReciteSchemeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SuperWord.h"
#include "ReciteSchemeDlg.h"
#include "Helper.h"

#include "ConcreteCondition.h"
#include "ConcreteCommand.h"
#include ".\reciteschemedlg.h"

#include <sstream>
#include <fstream>

using namespace helper;
using namespace comp;
using namespace compdlg;
using namespace std;

IMPLEMENT_DYNAMIC(CReciteSchemeDlg, CDialog)
CReciteSchemeDlg::CReciteSchemeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CReciteSchemeDlg::IDD, pParent)
	, m_nInactiveTreeHeight(4)
	, m_nInactiveTreeWidth(4)
	, m_rootCondition(condition, 1)
	, m_rootPerWordCmd(command, 1)
{
	m_bConditionActive = TRUE;
	m_bPerwordCmdActive = TRUE;
	m_bDragingHorizontalResizer = FALSE;
	m_bFilterChanged = FALSE;
	m_bPerwordCmdChanged = FALSE;
}

CReciteSchemeDlg::~CReciteSchemeDlg()
{
}

void CReciteSchemeDlg::SetChildItemResizeInfo()
{
	DWORD styleCondition  = WRS_TOP | WRS_SYNWIDTH;
	DWORD stylePerwordCmd = WRS_SYNWIDTH | WRS_SYNHEIGHT;

	SetDlgItemResizeInfo(IDC_TREE_CONDITION,            styleCondition);
	SetDlgItemResizeInfo(IDC_TREE_PERWORD_CMD,          stylePerwordCmd);
	SetDlgItemResizeInfo(IDC_STATIC_SEPARATOR,          WRS_SYNWIDTH | WRS_BOTTOM);
	SetDlgItemResizeInfo(IDC_BUTTON_SAVE_RECITE_SCHEME, WRS_RIGHT | WRS_BOTTOM);
	SetDlgItemResizeInfo(IDC_BUTTON_OPEN_RECITE_SCHEME, WRS_RIGHT | WRS_BOTTOM);
	SetDlgItemResizeInfo(IDOK,                          WRS_RIGHT | WRS_BOTTOM);
	SetDlgItemResizeInfo(IDCANCEL,                      WRS_RIGHT | WRS_BOTTOM);
}

void CReciteSchemeDlg::UpdateResizeRect()
{
	CRect rcCondition  = GetDlgItemRect(this, IDC_TREE_CONDITION);
	CRect rcPerwordCmd = GetDlgItemRect(this, IDC_TREE_PERWORD_CMD);

	m_rectHorizontalResizer = rcCondition;
	m_rectHorizontalResizer.top = rcCondition.bottom;
	m_rectHorizontalResizer.bottom = rcPerwordCmd.top;
}

BOOL CReciteSchemeDlg::PointOnDragableHorizontalResizer(POINT pt)
{
	return 	(m_rectHorizontalResizer.PtInRect(pt));
}

void CReciteSchemeDlg::MoveResizerPos(InitPos ipos, int pos)
{
	CRect rcCondition  = GetDlgItemRect(this, IDC_TREE_CONDITION);
	CRect rcPerwordCmd = GetDlgItemRect(this, IDC_TREE_PERWORD_CMD);
	int nTotalTreeHeight = rcCondition.Height() + rcPerwordCmd.Height();

	switch (ipos)
	{
	case begin: break;
	case end: pos += nTotalTreeHeight; break;
	case mid: pos += nTotalTreeHeight / 2; break;
	case cur: pos += rcCondition.Height(); break;
	}

//	if (pos >= m_nInactiveTreeHeight && pos <= nTotalTreeHeight - m_nInactiveTreeHeight)
	{
		rcCondition.bottom = rcCondition.top     + pos;
		rcPerwordCmd.top   = rcPerwordCmd.bottom - (nTotalTreeHeight - pos);
		m_tcCond.MoveWindow(rcCondition);
		m_tcWCmd.MoveWindow(rcPerwordCmd);
	}

	SetChildItemResizeInfo();
	UpdateResizeRect();
}

void CReciteSchemeDlg::FillCompInfo()
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

void CReciteSchemeDlg::SaveSchemeToSingleFile(const string& file_name)
{
	string sep("\n-------------------------------------------------\n");
	ofstream ofs(file_name.c_str());
	if (!ofs) return;

	m_rootCondition.Save(ofs);
	ofs << sep;
	m_rootPerWordCmd.Save(ofs);
}

void CReciteSchemeDlg::LoadSchemeFromSingleFile(const string& file_name)
{
	ifstream ifs(file_name.c_str());
	if (!ifs) return;

	m_rootCondition.Read(ifs);
	m_rootPerWordCmd.Read(ifs);
	m_tcCond.Refresh();
	m_tcWCmd.Refresh();
}

void CReciteSchemeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE_CONDITION, m_tcCond);
	DDX_Control(pDX, IDC_TREE_PERWORD_CMD, m_tcWCmd);
}


BEGIN_MESSAGE_MAP(CReciteSchemeDlg, CDialog)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON_OPEN_RECITE_SCHEME, OnBnClickedButtonOpenReciteScheme)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_RECITE_SCHEME, OnBnClickedButtonSaveReciteScheme)
END_MESSAGE_MAP()


// CReciteSchemeDlg message handlers

BOOL CReciteSchemeDlg::OnInitDialog()
{
	__super::OnInitDialog();

	CPopupHelpStyle::CreateDecorator(this);
	CResizableStyle::CreateDecorator(this);

	// Set Resize Info
	SetChildItemResizeInfo();
	UpdateResizeRect();

	// Initialize Tree control
	FillCompInfo();
	
	m_tcCond.InitTree(&m_civ, &m_rootCondition, SWPath(IDS(IDSP_WORD_FILTER)), _T("flt"));
	m_tcCond.LoadComposite(SWPath(IDS(IDSFN_WORD_FILTER)));
	m_tcWCmd.InitTree(&m_civ, &m_rootPerWordCmd, SWPath(IDS(IDSP_WORD_CMD)), _T("cmd"));
	m_tcWCmd.LoadComposite(SWPath(IDS(IDSFN_WORD_CMD)));

	m_rootCondition.Save(m_ssOldCondition);
	m_rootPerWordCmd.Save(m_ssOldPerwordCmd);

	return TRUE;
}

void CReciteSchemeDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_bDragingHorizontalResizer)
	{
		MoveResizerPos(cur, point.y - m_ptOldDrag.y);
		m_ptOldDrag = point;
	}
	else
	{
		if (PointOnDragableHorizontalResizer(point))
			::SetCursor(::LoadCursor(NULL, IDC_SIZENS));
	}

	__super::OnMouseMove(nFlags, point);
}

void CReciteSchemeDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (PointOnDragableHorizontalResizer(point))
	{
		m_bDragingHorizontalResizer = TRUE;
		m_ptOldDrag = point;
		::SetCursor(::LoadCursor(NULL, IDC_SIZENS));
		SetCapture();
	}

	__super::OnLButtonDown(nFlags, point);
}

void CReciteSchemeDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	ReleaseCapture();
	m_bDragingHorizontalResizer = FALSE;
	__super::OnLButtonUp(nFlags, point);
}

void CReciteSchemeDlg::OnOK()
{
	stringstream ssCondition;
	stringstream ssPerwordCmd;

	m_rootCondition.Save(ssCondition);
	m_rootPerWordCmd.Save(ssPerwordCmd);

	if (m_ssOldCondition.str() != ssCondition.str())
	{
		m_bFilterChanged = TRUE;
		m_tcCond.SaveComposite(SWPath(IDS(IDSFN_WORD_FILTER)));
	}
	if (m_ssOldPerwordCmd.str() != ssPerwordCmd.str())
	{
		m_bPerwordCmdChanged = TRUE;
		m_tcWCmd.SaveComposite(SWPath(IDS(IDSFN_WORD_CMD)));
	}
	
	__super::OnOK();
}


void CReciteSchemeDlg::OnBnClickedButtonOpenReciteScheme()
{
	CFileDialog dlg(TRUE, "rs", 0, 0, "背诵方案文件(*.rs)|*.rs||");
	dlg.m_ofn.lpstrInitialDir = SWPath(IDS(IDSP_RECITE_SCHEME));
	if (dlg.DoModal() == IDOK)
	{
		LoadSchemeFromSingleFile((LPCTSTR)dlg.GetPathName());
	}
}

void CReciteSchemeDlg::OnBnClickedButtonSaveReciteScheme()
{
	CFileDialog dlg(FALSE, "rs", 0, 0, "背诵方案文件(*.rs)|*.rs||");
	dlg.m_ofn.lpstrInitialDir = SWPath(IDS(IDSP_RECITE_SCHEME));
	if (dlg.DoModal() == IDOK)
	{
		SaveSchemeToSingleFile((LPCTSTR)dlg.GetPathName());
	}
}
