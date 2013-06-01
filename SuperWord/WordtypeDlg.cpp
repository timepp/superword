// RSWordtypePage.cpp : implementation file
//

#include "stdafx.h"
#include "superword.h"
#include "WordtypeDlg.h"
#include "WordType.h"
#include "Word.h"
#include "InputDlg.h"
#include "ProgressDlg.h"
#include "Filter.h"

#include <string>
#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWordtypeDlg property page

IMPLEMENT_DYNCREATE(CWordtypeDlg, CDialog)

CWordtypeDlg::CWordtypeDlg() : CDialog(CWordtypeDlg::IDD)
{
	//{{AFX_DATA_INIT(CWordtypeDlg)
	//}}AFX_DATA_INIT
}

CWordtypeDlg::~CWordtypeDlg()
{
}

void CWordtypeDlg::ResetWordType(Word *pw)
{
	int count = m_lbWordList.GetCount();
	WORD wWordType = pw->type();
	WORD newType = 0;
	for (int i = 0; i < count; i++)
	{
		DWORD_PTR oldIndex = m_lbWordList.GetItemData(i);
		if (oldIndex != (DWORD)-1)
		{
			int tp = (wWordType >> oldIndex) & 1;
			newType |= (tp << i);
		}
	}

	pw->set_type(newType);
}

void CWordtypeDlg::RecreateWordType()
{
	CProgressDlg *pDlg = CProgressDlg::Instance();

	// 按列表控件的内容设置单词的属性列表
	pDlg->RestartTask(_T("正在重建属性列表"));

	WordType *pWt = WordType::Instance();
	pWt->m_vTypes.clear();
	int count = m_lbWordList.GetCount();
	for (int i = 0; i < count; i++)
	{
		CString str;
		m_lbWordList.GetText(i, str);
		pWt->m_vTypes.push_back((LPCSTR)str);
	}

	// 更新各个单词的属性标识
	
	const WordVector * pVwFixed = FixedWordsCreator::Instance()->GetWords();
	const WordVector * pVwUser  = UserWordsCreator::Instance()->GetWords();

	pDlg->RestartTask(_T("正在同步单词属性"), pVwFixed->size() + pVwUser->size());

	WordVector::const_iterator ci;
	for (ci = pVwFixed->begin(); ci != pVwFixed->end(); ++ci)
	{
		ResetWordType(*ci);
		pDlg->StepIt();
	}
	for (ci = pVwUser->begin(); ci != pVwUser->end(); ++ci)
	{
		ResetWordType(*ci);
		pDlg->StepIt();
	}

	pDlg->ShowWindow(SW_HIDE);
}

void CWordtypeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWordtypeDlg)
	DDX_Control(pDX, IDC_WORDTYPE_LIST, m_lbWordList);
	//}}AFX_DATA_MAP
}

void CWordtypeDlg::InitWordTypeList()
{
	WordType *pWt = WordType::Instance();
	const StringVector& sv = pWt->GetAllType();

	m_lbWordList.ResetContent();
	int index = 0;
	StringVector::const_iterator ci;
	for (ci = sv.begin(); ci != sv.end(); ++ci, index++)
	{
		m_lbWordList.AddString(ci->c_str());
		m_lbWordList.SetItemData(index, index);
	}
}

BOOL CWordtypeDlg::ExchangeItem(int item1, int item2)
{
	int count = m_lbWordList.GetCount();
	if (item1 < 0 || item2 < 0 || item1 >= count || item2 >= count || item1 == item2)
		return FALSE;
	
	CString strItem1, strItem2;
	DWORD_PTR dwItem1, dwItem2;

	m_lbWordList.GetText(item1, strItem1);
	dwItem1 = m_lbWordList.GetItemData(item1);
	m_lbWordList.GetText(item2, strItem2);
	dwItem2 = m_lbWordList.GetItemData(item2);
	m_lbWordList.DeleteString(item1);
	m_lbWordList.InsertString(item1, strItem2);
	m_lbWordList.SetItemData(item1, dwItem2);
	m_lbWordList.DeleteString(item2);
	m_lbWordList.InsertString(item2, strItem1);
	m_lbWordList.SetItemData(item2, dwItem1);

	return TRUE;
}


BEGIN_MESSAGE_MAP(CWordtypeDlg, CDialog)
	//{{AFX_MSG_MAP(CWordtypeDlg)
	ON_BN_CLICKED(IDC_BTN_MOVEUP, OnBtnMoveup)
	ON_BN_CLICKED(IDC_BTN_MOVEDOWN, OnBtnMovedown)
	ON_BN_CLICKED(IDC_BTN_ADD_WORD_TYPE, OnBtnAddWordType)
	ON_BN_CLICKED(IDC_BTN_DEL_WORD_TYPE, OnBtnDelWordType)
	ON_BN_CLICKED(IDC_BTN_EXCHANGE_SEL, OnBtnExchangeSel)
//	ON_LBN_SELCHANGE(IDC_WORDTYPE_LIST, OnSelchangeWordtypeList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWordtypeDlg message handlers

BOOL CWordtypeDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CPopupHelpStyle::CreateDecorator(this);
	
	InitWordTypeList();	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CWordtypeDlg::OnBtnMoveup() 
{
	int sel = m_lbWordList.GetCurSel();
	if (ExchangeItem(sel, sel - 1))
		m_lbWordList.SetSel(sel - 1);
}

void CWordtypeDlg::OnBtnMovedown() 
{
	int sel = m_lbWordList.GetCurSel();
	if (ExchangeItem(sel, sel + 1))
		m_lbWordList.SetSel(sel + 1);
}

void CWordtypeDlg::OnBtnExchangeSel() 
{
	int selCount = m_lbWordList.GetSelCount();
	if (selCount != 2) return;

	int item[2];
	m_lbWordList.GetSelItems(2, item);
	ExchangeItem(item[0], item[1]);
	m_lbWordList.SetSel(item[0]);
	m_lbWordList.SetSel(item[1]);
}


void CWordtypeDlg::OnBtnAddWordType() 
{
	int count = m_lbWordList.GetCount();
	if (count < WordType::MaxWordTypeCount)
	{
		CInputDlg dlg(_T("请输入单词属性名："));
		if (dlg.DoModal() == IDOK)
		{
			m_lbWordList.AddString(dlg.GetInputString());
			m_lbWordList.SetItemData(count, (DWORD)-1);
		}
	}
}

void CWordtypeDlg::OnBtnDelWordType() 
{
	int *item = new int[WordType::MaxWordTypeCount];
	int count = m_lbWordList.GetSelCount();
	m_lbWordList.GetSelItems(WordType::MaxWordTypeCount, item);
	std::sort(item, item + count);
	for (--count; count >= 0; --count)
	{
		m_lbWordList.DeleteString(item[count]);
	}
	delete [] item;
}

void CWordtypeDlg::OnOK() 
{
	RecreateWordType();
	
	CDialog::OnOK();
}
