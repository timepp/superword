// PractiseResultDlg.cpp : implementation file
//

#include "stdafx.h"
#include "superword.h"
#include "PractiseResultDlg.h"
#include ".\practiseresultdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define IDTIMER_SHOW_WINDOW		1010
/////////////////////////////////////////////////////////////////////////////
// CPractiseResultDlg dialog


CPractiseResultDlg::CPractiseResultDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPractiseResultDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPractiseResultDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_hBmpWrong = NULL;
	m_hBmpRight = NULL;
	m_hRgn = NULL;
	m_bCapturing = FALSE;
}

CPractiseResultDlg::~CPractiseResultDlg()
{
	if (m_hBmpRight != NULL)
	{
		::DeleteObject(m_hBmpRight);
		m_hBmpRight = NULL;
	}
	if (m_hBmpWrong != NULL)
	{
		::DeleteObject(m_hBmpWrong);
		m_hBmpWrong = NULL;
	}
	if (m_hRgn == NULL)
	{
		::DeleteObject(m_hRgn);
		m_hRgn = NULL;
	}
}


//	BitmapToRegion :Create a region from the "non-transparent" pixels of a bitmap
//	hBmp :			Source bitmap
//	cTransparentColor :	Color base for the "transparent" pixels (default is black)
//	cTolerance :		Color tolerance for the "transparent" pixels
//
//	A pixel is assumed to be transparent if the value of each of its 3 components (blue, green and red) is
//	greater or equal to the corresponding value in cTransparentColor and is lower or equal to the
//	corresponding value in cTransparentColor + cTolerance
HRGN CPractiseResultDlg::BitmapToRegion(HBITMAP hBmp, 
										COLORREF cTransparentColor /* = 0 */, 
										COLORREF cTolerance /* = 0x101010 */)
{
	HRGN hRgn = NULL;

	ASSERT(hBmp);
	if (hBmp)
	{
		// Create a memory DC inside which we will scan the bitmap conten
		HDC hMemDC = CreateCompatibleDC(NULL);
		ASSERT(hMemDC);
		if (hMemDC)
		{
			// Get bitmap siz
			BITMAP bm;
			GetObject(hBmp, sizeof(bm), &bm);

			// Create a 32 bits depth bitmap and select it into the memory DC
			BITMAPINFOHEADER RGB32BITSBITMAPINFO = {
				sizeof(BITMAPINFOHEADER),	// biSize
					bm.bmWidth,					// biWidth;
					bm.bmHeight,				// biHeight;
					1,							// biPlanes;
					32,							// biBitCount
					BI_RGB,						// biCompression;
					0,							// biSizeImage;
					0,							// biXPelsPerMeter;
					0,							// biYPelsPerMeter;
					0,							// biClrUsed;
					0							// biClrImportant;
			};
			VOID * pbits32;
			HBITMAP hbm32 = CreateDIBSection(hMemDC, (BITMAPINFO *)&RGB32BITSBITMAPINFO, DIB_RGB_COLORS, &pbits32, NULL, 0);
			ASSERT(hbm32);
			if (hbm32)
			{
				HBITMAP holdBmp = (HBITMAP)SelectObject(hMemDC, hbm32);

				// Create a DC just to copy the bitmap into the memory D
				HDC hDC = CreateCompatibleDC(hMemDC);
				ASSERT(hDC);
				if (hDC)
				{
					// Get how many bytes per row we have for the bitmap bits (rounded up to 32 bits
					BITMAP bm32;
					VERIFY(GetObject(hbm32, sizeof(bm32), &bm32));
					while (bm32.bmWidthBytes % 4)
						bm32.bmWidthBytes++;

					// Copy the bitmap into the memory D
					HBITMAP holdBmp = (HBITMAP)SelectObject(hDC, hBmp);
					VERIFY(BitBlt(hMemDC, 0, 0, bm.bmWidth, bm.bmHeight, hDC, 0, 0, SRCCOPY));

					// For better performances, we will use the ExtCreateRegion() function to create the
					// region. This function take a RGNDATA structure on entry. We will add rectangles b
					// amount of ALLOC_UNIT number in this structure
					const int ALLOC_UNIT = 100;
					DWORD maxRects = ALLOC_UNIT;
					HANDLE hData = GlobalAlloc(GMEM_MOVEABLE, sizeof(RGNDATAHEADER) + (sizeof(RECT) * maxRects));
					RGNDATA *pData = (RGNDATA *)GlobalLock(hData);
					pData->rdh.dwSize = sizeof(RGNDATAHEADER);
					pData->rdh.iType = RDH_RECTANGLES;
					pData->rdh.nCount = pData->rdh.nRgnSize = 0;
					SetRect(&pData->rdh.rcBound, MAXLONG, MAXLONG, 0, 0);

					// Keep on hand highest and lowest values for the "transparent" pixel
					BYTE lr = GetRValue(cTransparentColor);
					BYTE lg = GetGValue(cTransparentColor);
					BYTE lb = GetBValue(cTransparentColor);
					BYTE hr = min(0xff, lr + GetRValue(cTolerance));
					BYTE hg = min(0xff, lg + GetGValue(cTolerance));
					BYTE hb = min(0xff, lb + GetBValue(cTolerance));

					// Scan each bitmap row from bottom to top (the bitmap is inverted vertically
					BYTE *p32 = (BYTE *)bm32.bmBits + (bm32.bmHeight - 1) * bm32.bmWidthBytes;
					for (int y = 0; y < bm.bmHeight; y++)
					{
						// Scan each bitmap pixel from left to righ
						for (int x = 0; x < bm.bmWidth; x++)
						{
							// Search for a continuous range of "non transparent pixels"
							int x0 = x;
							LONG *p = (LONG *)p32 + x;
							while (x < bm.bmWidth)
							{
								BYTE b = GetRValue(*p);
								if (b >= lr && b <= hr)
								{
									b = GetGValue(*p);
									if (b >= lg && b <= hg)
									{
										b = GetBValue(*p);
										if (b >= lb && b <= hb)
											// This pixel is "transparent"
											break;
									}
								}
								p++;
								x++;
							}

							if (x > x0)
							{
								// Add the pixels (x0, y) to (x, y+1) as a new rectangle in the regio
								if (pData->rdh.nCount >= maxRects)
								{
									GlobalUnlock(hData);
									maxRects += ALLOC_UNIT;
									VERIFY(hData = GlobalReAlloc(hData, sizeof(RGNDATAHEADER) + (sizeof(RECT) * maxRects), GMEM_MOVEABLE));
									pData = (RGNDATA *)GlobalLock(hData);
									ASSERT(pData);
								}
								RECT *pr = (RECT *)&pData->Buffer;
								SetRect(&pr[pData->rdh.nCount], x0, y, x, y+1);
								if (x0 < pData->rdh.rcBound.left)
									pData->rdh.rcBound.left = x0;
								if (y < pData->rdh.rcBound.top)
									pData->rdh.rcBound.top = y;
								if (x > pData->rdh.rcBound.right)
									pData->rdh.rcBound.right = x;
								if (y+1 > pData->rdh.rcBound.bottom)
									pData->rdh.rcBound.bottom = y+1;
								pData->rdh.nCount++;

								// On Windows98, ExtCreateRegion() may fail if the number of rectangles is to
								// large (ie: > 4000). Therefore, we have to create the region by multiple steps
								if (pData->rdh.nCount == 2000)
								{
									HRGN h = ExtCreateRegion(NULL, sizeof(RGNDATAHEADER) + (sizeof(RECT) * maxRects), pData);
									ASSERT(h);
									if (hRgn)
									{
										CombineRgn(hRgn, hRgn, h, RGN_OR);
										DeleteObject(h);
									}
									else
										hRgn = h;
									pData->rdh.nCount = 0;
									SetRect(&pData->rdh.rcBound, MAXLONG, MAXLONG, 0, 0);
								}
							}
						}

						// Go to next row (remember, the bitmap is inverted vertically
						p32 -= bm32.bmWidthBytes;
					}

					// Create or extend the region with the remaining rectangle
					HRGN h = ExtCreateRegion(NULL, sizeof(RGNDATAHEADER) + (sizeof(RECT) * maxRects), pData);
					ASSERT(h);
					if (hRgn)
					{
						CombineRgn(hRgn, hRgn, h, RGN_OR);
						DeleteObject(h);
					}
					else
						hRgn = h;

					// Clean u
					SelectObject(hDC, holdBmp);
					DeleteDC(hDC);
				}

				DeleteObject(SelectObject(hMemDC, holdBmp));
			}

			DeleteDC(hMemDC);
		}
	}

	return hRgn;
}



void CPractiseResultDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPractiseResultDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BOOL CPractiseResultDlg::ShowWindow(int nCmdShow)
{/*
	if (nCmdShow == SW_HIDE)
	{
		if (IsWindowVisible())
		{
			BOOL bRet = CWnd::ShowWindow(nCmdShow);
			CRect rc;
			GetWindowRect(&rc);
			GetParent()->ScreenToClient(&rc);
			GetParent()->InvalidateRect(&rc);
			return bRet;
		}
		return FALSE;
	}
	else*/
	{
		return CWnd::ShowWindow(nCmdShow);
	}
}

BOOL CPractiseResultDlg::LoadBitmapsFromFile()
{
	CString strBasePath = helper::SWPath();

	CString strBmpfileRight = strBasePath + _T("\\chk_right.bmp");
	CString strBmpfileWrong = strBasePath + _T("\\chk_wrong.bmp");
	
	if (!m_hBmpRight)
	{
		m_hBmpRight = (HBITMAP)::LoadImage(NULL, strBmpfileRight, IMAGE_BITMAP, 
			0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		if (m_hBmpRight) ::GetObject(m_hBmpRight, sizeof(BITMAP), &m_bmRight);
	}
	if (!m_hBmpWrong)
	{
		m_hBmpWrong = (HBITMAP)::LoadImage(NULL, strBmpfileWrong, IMAGE_BITMAP, 
			0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		if (m_hBmpWrong) ::GetObject(m_hBmpWrong, sizeof(BITMAP), &m_bmWrong);
	}

	return (m_hBmpRight && m_hBmpWrong);;
}

BOOL CPractiseResultDlg::ShowPractiseResult(CPoint ptBottomRight, int nType)
{
	m_ptBottomRight = ptBottomRight;
	m_nShowType = nType;

	ShowWindow(SW_HIDE);
	if (m_hRgn == NULL)
	{
		::DeleteObject(m_hRgn);
	}
	m_hRgn = BitmapToRegion(nType? m_hBmpRight : m_hBmpWrong);
	SetWindowRgn(m_hRgn, FALSE);
	SetTimer(IDTIMER_SHOW_WINDOW, 0, NULL);

	return TRUE;
}


BEGIN_MESSAGE_MAP(CPractiseResultDlg, CDialog)
	//{{AFX_MSG_MAP(CPractiseResultDlg)
	ON_WM_ERASEBKGND()
	ON_WM_SHOWWINDOW()
	ON_WM_SETFOCUS()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPractiseResultDlg message handlers

BOOL CPractiseResultDlg::OnEraseBkgnd(CDC* pDC) 
{
	CRect rc;
	GetClientRect(&rc);
	pDC->FillSolidRect(0, 0, rc.Width(), rc.Height(), RGB(255, 0, 0));

	return TRUE;
}

BOOL CPractiseResultDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// 加载位图
	LoadBitmapsFromFile();
	
	return TRUE;
}

void CPractiseResultDlg::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent == IDTIMER_SHOW_WINDOW)
	{
		KillTimer(nIDEvent);
		
		BITMAP *pBm = (m_nShowType == SPR_WRONG) ? &m_bmWrong : &m_bmRight;

		CPoint ptTopLeft = m_ptBottomRight;
		ptTopLeft.Offset(-pBm->bmWidth, -pBm->bmHeight);
	
		SetWindowPos(NULL, ptTopLeft.x, ptTopLeft.y, pBm->bmWidth, pBm->bmHeight, 
			SWP_SHOWWINDOW | SWP_NOACTIVATE | SWP_NOZORDER);

		SetCapture();
		m_bCapturing = TRUE;
	}
	CDialog::OnTimer(nIDEvent);
}

void CPractiseResultDlg::OnSetFocus(CWnd* pOldWnd) 
{
	CDialog::OnSetFocus(pOldWnd);
	
	// 如果窗口有了输入焦点， 就隐藏
	ShowWindow(SW_HIDE);
	
}

void CPractiseResultDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
//	if (nStatus != 0)
		ShowWindow(SW_HIDE);
}

BOOL CPractiseResultDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: must ignore the first WM_MOUSEMOVE message.
	//       this is a temp solution.
	static int flag = 2;

	if (pMsg->message >= WM_MOUSEFIRST && pMsg->message <= WM_MOUSELAST &&
		m_bCapturing)
	{
		if (--flag == 0)
		{
			ReleaseCapture();
			m_bCapturing = FALSE;
			flag = 2;
			ShowWindow(SW_HIDE);
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}
