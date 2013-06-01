  // CSPhoneticDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SuperWord.h"
#include "ConcreteCondition.h"
#include "CSPhoneticDlg.h"

#include <iostream>
#include <sstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace compdlg;
using namespace comp;
/////////////////////////////////////////////////////////////////////////////
// CCSPhoneticDlg dialog
char CCSPhoneticDlg::m_szAll[] = ".*|?+^$\\()[]{}BQeAiICJuEZ9`:pbtdkgfvszWTFVmnNhlrwj12345678";
char CCSPhoneticDlg::m_szControl[] = ".*|?+^$\\()[]{}12345678";
char CCSPhoneticDlg::m_szPhonetic[][16] =
{
	"BQeAiICJuEZ9`:",
	"pbtdkgfvszWTFV",
	"mnNhlrwj",
	""
};


CCSPhoneticDlg::CCSPhoneticDlg(CWnd* pParent /*=NULL*/)
	: CCSRootDlg(CCSPhoneticDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCSPhoneticDlg)
	//}}AFX_DATA_INIT
	m_crBorder = RGB(0, 128, 0);
	m_crBack = RGB(0, 0, 0);
	m_crPhonetic = RGB(255, 255, 255);

	m_strPhoneticFontName = "Kingsoft Phonetic Plain";

	m_cfPhonetic = helper::CF(300, 0, 0, 2, 2, m_strPhoneticFontName);
	m_cfControl = helper::CF(300, 0, RGB(0, 0, 255), 3, 34, "Courier New");
}


void CCSPhoneticDlg::DoDataExchange(CDataExchange* pDX)
{
    cond::PhoneticCondition * pCond = dynamic_cast<cond::PhoneticCondition *>(m_pComp);
	CCSRootDlg::DoDataExchange(pDX);

	//{{AFX_DATA_MAP(CCSPhoneticDlg)
	DDX_Control(pDX, IDC_RICHEDIT_MATCHER, m_rdMatcher);
	//}}AFX_DATA_MAP
	if (pDX->m_bSaveAndValidate)
	{
		CString str;
		m_rdMatcher.GetWindowText(str);
        pCond->Configure((LPCTSTR)str);
	}
}


void CCSPhoneticDlg::DrawSelectCell(const CRect& rc, char ch, LPCTSTR pszFont, int nCharSet, int nPitchAndFamily, COLORREF crBack, COLORREF crChar, COLORREF crBorder)
{
	CClientDC dc(this);
	CPen penBorder(PS_SOLID, 1, crBorder);
	CBrush brsBack(crBack);
	CFont font;
	font.CreateFont(rc.Height() - 2, 0, 0, 0, 0, 0, 0, 0, 
		static_cast<BYTE>(nCharSet), 0, 0, 0, 
		static_cast<BYTE>(nPitchAndFamily), pszFont);
	CString str = ch;
	
	CPen *poldPen = dc.SelectObject(&penBorder);
	CBrush *poldBrs = dc.SelectObject(&brsBack);
	CFont *poldFont = dc.SelectObject(&font);

	dc.Rectangle(&rc);
	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(crChar);
	int width = dc.GetTextExtent(str).cx;
	dc.TextOut(rc.left + (rc.Width() - width) / 2, rc.top + 1, CString(ch));

	dc.SelectObject(poldPen);
	dc.SelectObject(poldBrs);
	dc.SelectObject(poldFont);
}

void CCSPhoneticDlg::DrawColorBorder(CRect rc, COLORREF cr)
{
	CClientDC dc(this);
	CPen pen(PS_SOLID, 1, cr);
	dc.SelectStockObject(NULL_BRUSH);
	CPen *poldPen = dc.SelectObject(&pen);

	dc.Rectangle(&rc);

	dc.SelectObject(poldPen);
}

BOOL CCSPhoneticDlg::GetFocusRectChar(CPoint pt, CRect *pRect, char *pChar)
{
	int i, j;

	for (i = 0; m_szPhonetic[i][0] != '\0'; i++)
	{
		for(j = 0; m_szPhonetic[i][j] != '\0'; j++)
		{
			CRect rcTest(j * m_szCell.cx, i * m_szCell.cy, 
                (j + 1) * m_szCell.cx, (i + 1) * m_szCell.cy);
			rcTest.OffsetRect(m_rcPhonetic.left, m_rcPhonetic.top);
			if (rcTest.PtInRect(pt))
			{
				*pRect = rcTest;
				*pChar = m_szPhonetic[i][j];
				return TRUE;
			}
		}
	}

	*pRect = CRect(0, 0, 0, 0);
	*pChar = '\0';
	return FALSE;
}

void CCSPhoneticDlg::InsertMatcher(char ch)
{
	long startchar, endchar;
	m_rdMatcher.GetSel(startchar, endchar);
	m_rdMatcher.ReplaceSel(CString(ch));
	m_rdMatcher.SetSel(startchar, startchar + 1);

	if (_tcschr(m_szControl, ch) != NULL)
		m_rdMatcher.SetWordCharFormat(m_cfControl);
	else
		m_rdMatcher.SetWordCharFormat(m_cfPhonetic);

	m_rdMatcher.SetSel(startchar + 1, startchar + 1);
}

BEGIN_MESSAGE_MAP(CCSPhoneticDlg, CCSRootDlg)
	//{{AFX_MSG_MAP(CCSPhoneticDlg)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_EN_CHANGE(IDC_RICHEDIT_MATCHER, OnChangeRicheditMatcher)
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCSPhoneticDlg message handlers


void CCSPhoneticDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	int i, j;
	for (i = 0; m_szPhonetic[i][0] != '\0'; i++)
	{
		for (j = 0; m_szPhonetic[i][j] != '\0'; j++)
		{
			CRect rc(j * m_szCell.cx, i * m_szCell.cy, 
                (j + 1) * m_szCell.cx, (i + 1) * m_szCell.cy);
			rc.OffsetRect(m_rcPhonetic.left, m_rcPhonetic.top);
			DrawSelectCell(rc, m_szPhonetic[i][j], m_strPhoneticFontName, 2, 2, m_crBack, m_crPhonetic, m_crBorder);
		}
	}
}

void CCSPhoneticDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	static CRect rcOldFocus = CRect(0, 0, 0, 0);
	COLORREF m_crFocus = RGB(0, 255, 0);
	CRect rcNew = rcOldFocus;
	char chNew;

	GetFocusRectChar(point, &rcNew, &chNew);

	if (rcNew != rcOldFocus)
	{
		DrawColorBorder(rcOldFocus, m_crBorder);
		DrawColorBorder(rcNew, m_crFocus);
		rcOldFocus = rcNew;
	}
	
	CCSRootDlg::OnMouseMove(nFlags, point);
}

void CCSPhoneticDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CRect rc;
	char ch;
	if (GetFocusRectChar(point, &rc, &ch))
	{
		InsertMatcher(ch);
	}

	CCSRootDlg::OnLButtonUp(nFlags, point);
}

BOOL CCSPhoneticDlg::OnInitDialog() 
{
	CCSRootDlg::OnInitDialog();

    std::string s = dynamic_cast<cond::PhoneticCondition *>(m_pComp)->GetConfiguration();

	for (int i = 0; s[i] != '\0'; i++)
		InsertMatcher(s[i]);
	m_rdMatcher.SetEventMask(ENM_CHANGE);
	m_rdMatcher.SetDefaultCharFormat(m_cfPhonetic);

	ModifyStyle(0, DS_CONTEXTHELP);

    // Adjust control
    GetDlgItem(IDC_PHONETIC_AREA)->GetWindowRect(&m_rcPhonetic);
    ScreenToClient(&m_rcPhonetic);
    m_szCell.cx = m_rcPhonetic.Width() / 14;
    m_szCell.cy = m_rcPhonetic.Height() / 3;

    m_rcPhonetic.right = m_rcPhonetic.left + m_szCell.cx * 14;
    m_rcPhonetic.bottom = m_rcPhonetic.top + m_szCell.cy * 3;
    GetDlgItem(IDC_PHONETIC_AREA)->MoveWindow(&m_rcPhonetic);

	return TRUE;
}

void CCSPhoneticDlg::OnChangeRicheditMatcher() 
{
	long nStart, nEnd;
	CString str;
	m_rdMatcher.GetSel(nStart, nEnd);
	m_rdMatcher.GetWindowText(str);
	if (nEnd == 0) return;

	char ch = str.GetAt(nEnd - 1);

	m_rdMatcher.SetSel(nEnd - 1, nEnd);
	m_rdMatcher.ReplaceSel("");

	if (_tcschr(m_szAll, ch) != NULL)
	{
		InsertMatcher(ch);
	}
}


