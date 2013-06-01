 // HappyBirthdayDlg.cpp : implementation file
//

#include "stdafx.h"
#include "superword.h"
#include "HappyBirthdayDlg.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////////
// CFlyWord
#define PI 3.14159265

int CFlyWord::s_rBirth = 100;
CRect CFlyWord::s_rcWorld;
CFont CFlyWord::s_font[MAX_FONT];

CFlyWord::CFlyWord()
{
	srand(static_cast<unsigned int>(time(NULL)));
	if (!s_font[0].m_hObject)
		InitFonts();
}

CFlyWord::~CFlyWord()
{
}

void CFlyWord::InitFonts()
{
	for (int i = 0; i < MAX_FONT; i++)
	{
		if (s_font[i].m_hObject) s_font[i].DeleteObject();
		s_font[i].CreateFont(-i,0, 0,0,400, 0,0,0, 0, 3,2,1, 34, _T("Arial"));
	}
}

void CFlyWord::InitState()
{
	static char word[][16] = 
	{
		"for", "love", "ever"
	};

	m_Angle = (rand() % 360) * 2 * PI / 360;

	int r = 0, g = 0, b = 0;
	while (r + g + b < 96 * 3)
	{
		r = rand() % 256;
		g = rand() % 256;
		b = rand() % 256;
	}
	m_cr = RGB(r, g, b);

	r = rand() % s_rBirth;
	CPoint ptCenter = s_rcWorld.CenterPoint();
	m_x = ptCenter.x + r * cos(m_Angle);
	m_y = ptCenter.y - r * sin(m_Angle);

	m_fontIndex = 8;

	int tmp = rand() % 100;
	if (tmp < 50) m_pWord = word[1];
	else if (tmp < 75) m_pWord = word[0];
	else m_pWord = word[2];

	m_speed = rand() % 5 + 5;
	m_font_inc_speed = m_speed / 2;
}

void CFlyWord::Move()
{
	m_x += m_speed * cos(m_Angle);
	m_y -= m_speed * sin(m_Angle);

	if (m_fontIndex < MAX_FONT - 1)
		m_fontIndex += m_font_inc_speed;

	CRect rc(s_rcWorld);
	rc.InflateRect(100, 100, 100, 100);
	if (!rc.PtInRect(CPoint(static_cast<int>(m_x), static_cast<int>(m_y))))
	{
		InitState();
	}
}

void CFlyWord::Draw(CDC *pDC)
{
	pDC->SelectObject(&s_font[(int)m_fontIndex]);
	pDC->SetTextColor(m_cr);
	pDC->TextOut((int)m_x, (int)m_y, m_pWord);
}

void CFlyWord::SetWorldRect(CRect &rc)
{
	s_rcWorld = rc;
}

/////////////////////////////////////////////////////////////////////////////
// CHappyBirthdayDlg dialog


CHappyBirthdayDlg::CHappyBirthdayDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHappyBirthdayDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHappyBirthdayDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_bShowInfo = TRUE;
	m_strInfo = _T(
		"Ц�͸���,һ��üͷ����ʹ\n"
		"��û�������,ֻ������ĸ���\n"
		"\n"
		"��Ҫ�����ߣ��������Ҳ����\n"
		"��Ϊ������ħ,������ʲô��\n"
		"\n"
		"���ǵ�,���ǹ�,����Ψһ����\n"
		"��ֻ����,you are my super star\n"
		"������,�ҳ��,û�и��õİ취\n"
		"ֻ�ܰ���,you are my super star\n"
		"\n"
		"\n"
		"�ֲ�����,�����������\n"
		"�����С����,����������ת��\n"
		"\n"
		"�뿴����,�������ο�����\n"
		"��Ϊ�㷢�˷�,����뽱����\n"
		"\n"
		"���ǵ�,���ǹ�,����Ψһ����\n"
		"��ֻ����,you are my super star\n"
		"������,�ҳ��,û�и��õİ취\n"
		"ֻ�ܰ���,you are my super star\n"
		"\n"
		"\n"
		"��������,�����ǵ������ּ��\n"
		"���˰���,û������\n"
		"\n"
		"���ǻ�,���ҷ�Խ�ľ�ͷ\n"
		"û���Ҫ����,Ϊʲô��Ҫ����\n"
		"\n"
		"лл�����,һ�����ֵ�����\n"
		"�����������,���æ�ǵ���\n"
		"\n"
		"���ǵ�,���ǹ�,����Ψһ����\n"
		"��ֻ����,you are my super star\n"
		"������,�ҳ��,û�и��õİ취\n"
		"ֻ�ܰ���,You are my Super Star");
	
}


void CHappyBirthdayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHappyBirthdayDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BOOL CHappyBirthdayDlg::InitialMemDC(CDC *pDC)
{
	if (m_mDC.m_hDC)
	{
		m_mDC.DeleteDC();
	}
	if (m_mBmp.m_hObject)
	{
		m_mBmp.DeleteObject();
	}
	if (m_mDC2.m_hDC)
	{
		m_mDC2.DeleteDC();
	}
	if (m_mBmp2.m_hObject)
	{
		m_mBmp2.DeleteObject();
	}

	m_mBmp.CreateCompatibleBitmap(pDC, m_rcTip.Width(), m_rcTip.Height());
	m_mDC.CreateCompatibleDC(pDC);
	m_mDC.SelectObject(&m_mBmp);
	m_mDC.FillSolidRect(&m_rcTip, 0);
	m_mDC.SetBkMode(TRANSPARENT);

	//m_mBmp2.CreateCompatibleBitmap(&m_mDC, m_rcTip.Width(), m_rcTip.Height());
	m_mBmp2.LoadBitmap(IDB_EARTH);
	m_mDC2.CreateCompatibleDC(&m_mDC);
	m_mDC2.SelectObject(&m_mBmp2);
//	m_mDC2.FillSolidRect(&m_rcTip, RGB(255, 255, 255));

	return TRUE;
}

BEGIN_MESSAGE_MAP(CHappyBirthdayDlg, CDialog)
	//{{AFX_MSG_MAP(CHappyBirthdayDlg)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHappyBirthdayDlg message handlers

HBRUSH CHappyBirthdayDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	static CFont font;

	if (!font.m_hObject)
	{
		font.CreateFont(-13,0, 0,0,400, 0,0,0, 134, 1,2,1, 49, _T("Fixedsys"));
	}
	
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pWnd->SetFont(&font);
	}
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CHappyBirthdayDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect rc;
	GetDlgItem(IDC_STATIC_CONGRATULATION)->GetWindowRect(&rc);
	ScreenToClient(&rc);

	rc.DeflateRect(1, 1, 1, 1);
	dc.FillSolidRect(&rc, 0);

	CFont font;
	font.CreateFont(-28,0, 0,0,400, 0,0,0, 134, 3,2,1, 49, _T("����"));

	dc.SelectObject(&font);
	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(RGB(0, 192, 0));
	dc.DrawText(_T("ף���������ճɾ���"), &rc, DT_CENTER | DT_VCENTER);
	dc.SetTextColor(RGB(255, 255, 255));
	rc.OffsetRect(-2, -2);
	dc.DrawText(_T("ף���������ճɾ���"), &rc, DT_CENTER | DT_VCENTER);
}

void CHappyBirthdayDlg::OnTimer(UINT nIDEvent) 
{
	static double nInfoTop = 2000;
	static CFont font;
	static CRgn rgn;
	if (!font.m_hObject)
		font.CreateFont(-16,0, 0,0,400, 0,0,0, 0, 3,2,1, 34,_T("Tahoma"));

	CRect rc;
	CClientDC dc(this);

	if (!m_mDC.m_hDC)
	{
		InitialMemDC(&dc);
	}
	
	m_mDC.BitBlt(0, 0, m_rcTip.Width(), m_rcTip.Height(), &m_mDC2, 0, 0, SRCCOPY);
	for (int i = 0; i < MAX_WORD; i++)
	{
		m_fw[i].Draw(&m_mDC);
		m_fw[i].Move();
	}

	CRect rcInfo;
	GetDlgItem(IDC_STATIC_INFO)->GetWindowRect(&rcInfo);
	GetDlgItem(IDC_STATIC_FLY)->ScreenToClient(&rcInfo);

	if (m_bShowInfo)
	{
		nInfoTop-=0.4;
		if (nInfoTop > rcInfo.bottom || nInfoTop < -700) 
			nInfoTop = rcInfo.bottom;
		rc = rcInfo;
		rc.bottom = 50000; 
		rc.OffsetRect(0, (int)nInfoTop);
		if (!rgn.m_hObject) rgn.CreateRectRgn(rcInfo.left, rcInfo.top + 2, 
			rcInfo.right, rcInfo.bottom - 2);
		m_mDC.SelectClipRgn(&rgn, RGN_COPY);
		m_mDC.SelectObject(&font);
		m_mDC.SetTextColor(RGB(255, 255, 255));
		m_mDC.DrawText(m_strInfo, &rc, DT_LEFT);
		m_mDC.SelectClipRgn(NULL);
	}
	
	GetDlgItem(IDC_STATIC_FLY)->GetWindowRect(&rc);
	ScreenToClient(&rc);

	dc.BitBlt(rc.left + 1, rc.top + 1, m_rcTip.Width(), m_rcTip.Height(), &m_mDC, 0, 0, SRCCOPY);

	CDialog::OnTimer(nIDEvent);
}

BOOL CHappyBirthdayDlg::OnInitDialog() 
{
	static CFont font;
	if (!font.m_hObject)
		font.CreateFont(-13,0, 0,0,400, 0,0,0, 0, 3,2,1, 34,_T("Tahoma"));

	CDialog::OnInitDialog();

	GetDlgItem(IDC_STATIC_FLY)->GetClientRect(&m_rcTip);
	CFlyWord::SetWorldRect(m_rcTip);
	for (int i = 0; i < MAX_WORD; i++) m_fw[i].InitState();

	SetFont(&font);
	SetTimer(1001, 50, NULL);
	
	return TRUE;
}

void CHappyBirthdayDlg::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	CRect rc;
	GetDlgItem(IDC_STATIC_INFO)->GetWindowRect(&rc);
	ScreenToClient(&rc);
	if (rc.PtInRect(point))
	{
		m_bShowInfo = !m_bShowInfo;
	}

	CDialog::OnLButtonDblClk(nFlags, point);
}
