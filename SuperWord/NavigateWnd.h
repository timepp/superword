#pragma once

#include "Composite.h"
#include "Command.h"
#include "Word.h"

#include <vector>
#include <string>

#ifndef interface
#define interface struct
#endif


interface NavigateWnd
{
	virtual ~NavigateWnd(){}

	virtual bool CreateNavigate() = 0;

    // Word Navigate
    enum MoveOp{first = 0, last, prev, next};
    virtual bool MoveWord(MoveOp mo) = 0;
    virtual const word::Word * GetCurrentWord() const = 0;

    // Element Color
    typedef std::vector<std::string> ColorElementArray;
    virtual bool GetColorElement(ColorElementArray& array) = 0;
    virtual bool SetColor(const std::string& color_element, unsigned long cr) = 0;

	// Element Show/hide
	typedef std::vector<std::string> VisualElementArray;
	virtual bool GetVisualElement(VisualElementArray& array) = 0;
	virtual bool ShowElement(const std::string& visual_element, bool show) = 0;

	// Dlg
	typedef std::vector<std::string> DlgNameArray;
	virtual bool GetDialogs(DlgNameArray& array) = 0;
	virtual bool OpenDialog(const std::string& dlg) = 0;

	// Misc
	typedef std::vector<std::string> MiscCommandArray;
	virtual bool GetMiscCommands(MiscCommandArray & array) = 0;
	virtual bool RunMiscCommand(const std::string& cmd) = 0;

	// Set Type
	enum SetTypeStyle{ add, del, toggle };
	virtual bool SetWordType(size_t index, SetTypeStyle style) = 0;

    // Timer Execute
    virtual bool TimerExecute(unsigned long interval, size_t repeat_time, 
		bool bGlobal, const comp::cmd::Command * cmd) = 0;

    // Hotkey
    virtual bool RegHotKey(ACCEL acl, bool bGlobal, const comp::cmd::Command * cmd) = 0;

	// Misc Conditions
	typedef std::vector<std::string> MiscConditionArray;
	virtual bool GetMiscConditions(MiscConditionArray & array) = 0;
	virtual bool CheckMiscCondition(const std::string& cond) = 0;

	virtual bool LoadComposite(const std::string& comp_file) = 0;
};