// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__CB0B6C85_9C22_4C37_8B5E_0E838BD2BEE7__INCLUDED_)
#define AFX_STDAFX_H__CB0B6C85_9C22_4C37_8B5E_0E838BD2BEE7__INCLUDED_

#define _WIN32_WINNT 0x500
#pragma warning(disable: 4786)
#pragma warning(disable: 4100)
//#include <iostream>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT
#include <afxhtml.h>
#include <windowsx.h>
#include "htmlhelp.h"

#define MAX_LINE 1024
#define CL(X) "class"##"X"

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
//}}AFX_INSERT_LOCATION

#endif // !defined(AFX_STDAFX_H__CB0B6C85_9C22_4C37_8B5E_0E838BD2BEE7__INCLUDED_)
