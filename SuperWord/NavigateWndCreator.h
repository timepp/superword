#pragma once

#include "NavigateWnd.h"

class NavigateWndCreator
{
private:
	NavigateWndCreator(void);
	~NavigateWndCreator(void);
	NavigateWndCreator(const NavigateWndCreator&);

public:
	static NavigateWndCreator * Instance(void);

	NavigateWnd * GetCurrentNavigateWnd();
};
