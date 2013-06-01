// SWAddWord.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "SWAddWord.h"
#include "SWAddWordDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSWAddWordApp

BEGIN_MESSAGE_MAP(CSWAddWordApp, CWinApp)
	//{{AFX_MSG_MAP(CSWAddWordApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSWAddWordApp construction

CSWAddWordApp::CSWAddWordApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CSWAddWordApp object

CSWAddWordApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CSWAddWordApp initialization

BOOL CSWAddWordApp::InitInstance()
{
	// Standard initialization

	CSWAddWordDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
