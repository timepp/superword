// SWAddWordDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SWAddWord.h"
#include "SWAddWordDlg.h"

#include <fstream>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSWAddWordDlg dialog

CSWAddWordDlg::CSWAddWordDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSWAddWordDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSWAddWordDlg)
	m_strMeaning = _T("");
	m_strPhonetic = _T("");
	m_strWord = _T("");
	m_strWordFileName = _T("");
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSWAddWordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSWAddWordDlg)
	DDX_Text(pDX, IDC_EDIT_MEANING, m_strMeaning);
	DDX_Text(pDX, IDC_EDIT_PNONETIC, m_strPhonetic);
	DDX_Text(pDX, IDC_EDIT_WORD, m_strWord);
	DDX_Text(pDX, IDC_EDIT_WORDFILENAME, m_strWordFileName);
	//}}AFX_DATA_MAP
}

void CSWAddWordDlg::copy_stream(std::ifstream& is, std::ofstream& os, long size)
{
	long remain = size;
	char buf[8192];

	while (remain > 8192)
	{
		is.read(buf, 8192);
		os.write(buf, 8192);
		remain -= 8192;
	}
	if (remain > 0)
	{
		is.read(buf, remain);
		os.write(buf, remain);
	}	
}

void CSWAddWordDlg::extract_word(std::ifstream& is, char *word)
{
	long pos = is.tellg();

	is.seekg(8, ios::cur);
	bool b1 = is.good();

	int c = -1;
	do {
		c++;
		is.read(word + c, 1);
	} while (word[c] != '\0');

	is.seekg(pos, ios::beg);
}

void CSWAddWordDlg::step_word(std::ifstream& is)
{
	long pos = is.tellg();
	BYTE bMeaningOffset;
	char ch;

	is.seekg(1, ios::cur);
	is.read((char *)&bMeaningOffset, 1);

	is.seekg(bMeaningOffset - 2, ios::cur);
	do {
		is.read(&ch, 1);
	} while(ch != '\0');
}

BEGIN_MESSAGE_MAP(CSWAddWordDlg, CDialog)
	//{{AFX_MSG_MAP(CSWAddWordDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_SELECTFILE, OnBtnSelectfile)
	ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)
	ON_BN_CLICKED(IDC_BTN_DELETE, OnBtnDelete)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSWAddWordDlg message handlers

BOOL CSWAddWordDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSWAddWordDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CSWAddWordDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSWAddWordDlg::OnBtnSelectfile() 
{
	CFileDialog dlg(TRUE);
	if (dlg.DoModal())
	{
		m_strWordFileName = dlg.GetPathName();
		SetDlgItemText(IDC_EDIT_WORDFILENAME, m_strWordFileName);
	}
}

void CSWAddWordDlg::OnBtnAdd() 
{
	char buf[8192] = "";
	char word[32];

	UpdateData();

	::MoveFileEx(m_strWordFileName, m_strWordFileName + _T(".bak"), 
		MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH);
	CString strOutFileName = m_strWordFileName;
	m_strWordFileName += _T(".bak");

	ifstream is(m_strWordFileName, ios::in | ios::binary);
	ofstream os(strOutFileName, ios::out | ios::binary);
	BYTE bPhoneticOffset;
	BYTE bMeaningOffset;
	
	is.seekg(0, ios::end);
	long size = is.tellg();

	long pos;
	for(is.seekg(0x100); is.good(); step_word(is))
	{
		extract_word(is, word);
		if (strcmp(m_strWord, word) == 0)
		{
			AfxMessageBox("单词已存在");
			return;
		}
		if (strcmp(m_strWord, word) < 0)
		{
			break;
		}
	}

	pos = is.tellg();
	is.seekg(0, ios::beg);
	copy_stream(is, os, pos);

	bPhoneticOffset = 8 + m_strWord.GetLength() + 1;
	bMeaningOffset = bPhoneticOffset + m_strPhonetic.GetLength() + 1;
	os << bPhoneticOffset;
	os << bMeaningOffset;
	memset(buf, 0, 6);
	os.write(buf, 6);
	os << (LPCTSTR)m_strWord;
	os.write("", 1);
	os << (LPCTSTR)m_strPhonetic;
	os.write("", 1);
	os << (LPCTSTR)m_strMeaning;
	os.write("", 1);

	copy_stream(is, os, size - pos);

	MessageBox("添加完成");
}

void CSWAddWordDlg::OnBtnDelete() 
{
	char word[32];

	UpdateData();

	::MoveFileEx(m_strWordFileName, m_strWordFileName + _T(".bak"), 
		MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH);
	CString strOutFileName = m_strWordFileName;
	m_strWordFileName += _T(".bak");

	ifstream is(m_strWordFileName, ios::in | ios::binary);
	ofstream os(strOutFileName, ios::out | ios::binary);
	
	is.seekg(0, ios::end);
	long size = is.tellg();

	long pos;
	bool found = false;
	for(is.seekg(0x100); is.good(); step_word(is))
	{
		extract_word(is, word);
		if (strcmp(word, "zz") == 0)
		{
			int s = 0;
		}
		if (strcmp(m_strWord, word) == 0)
		{
			found = true;
			break;
		}
		long cur = is.tellg();
	}

	if (!found)
	{
		AfxMessageBox("单词未找到");
		return;
	}

	pos = is.tellg();
	is.seekg(0, ios::beg);
	copy_stream(is, os, pos);

	step_word(is);
	pos = is.tellg();

	copy_stream(is, os, size - pos);

	MessageBox("删除完成");
}
