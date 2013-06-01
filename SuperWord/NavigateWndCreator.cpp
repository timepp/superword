#include "stdafx.h"
#include "SuperWordDlg.h"
#include ".\navigatewndcreator.h"

NavigateWndCreator::NavigateWndCreator(void)
{
}

NavigateWndCreator::~NavigateWndCreator(void)
{
}

NavigateWndCreator::NavigateWndCreator(const NavigateWndCreator&)
{
}

NavigateWndCreator * NavigateWndCreator::Instance()
{
	static NavigateWndCreator nwc;
	return &nwc;
}

NavigateWnd * NavigateWndCreator::GetCurrentNavigateWnd()
{
	static CSuperWordDlg dlg;
	return &dlg;
}