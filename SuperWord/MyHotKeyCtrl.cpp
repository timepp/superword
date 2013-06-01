// MyHotKeyCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "SuperWord.h"
#include "MyHotKeyCtrl.h"


// CMyHotKeyCtrl

IMPLEMENT_DYNAMIC(CMyHotKeyCtrl, CHotKeyCtrl)
CMyHotKeyCtrl::CMyHotKeyCtrl()
{
}

CMyHotKeyCtrl::~CMyHotKeyCtrl()
{
}

void CMyHotKeyCtrl::SetHotKey(ACCEL acl)
{
    WORD wVirtualKeyCode = acl.key;
    WORD wModifiers = HOTKEYF_EXT;
    if (acl.fVirt & FALT)     wModifiers |= HOTKEYF_ALT;
    if (acl.fVirt & FCONTROL) wModifiers |= HOTKEYF_CONTROL;
    if (acl.fVirt & FSHIFT)   wModifiers |= HOTKEYF_SHIFT;
    __super::SetHotKey(wVirtualKeyCode, wModifiers);
}

void CMyHotKeyCtrl::GetHotKey(ACCEL &acl) const
{
    WORD wVirtualKeyCode;
    WORD wModifiers;
    __super::GetHotKey(wVirtualKeyCode, wModifiers);
    
    acl.key = wVirtualKeyCode;
    acl.fVirt = FNOINVERT | FVIRTKEY;
    if (wModifiers & HOTKEYF_ALT)     acl.fVirt |= FALT;
    if (wModifiers & HOTKEYF_CONTROL) acl.fVirt |= FCONTROL;
    if (wModifiers & HOTKEYF_SHIFT)   acl.fVirt |= FSHIFT;
}


BEGIN_MESSAGE_MAP(CMyHotKeyCtrl, CHotKeyCtrl)
END_MESSAGE_MAP()



// CMyHotKeyCtrl message handlers

