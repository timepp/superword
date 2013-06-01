#include "stdafx.h"
#include "ConcreteCommand.h"
#include "Condition.h"
#include "LibSrc/greta/regexpr2.h"
#include "WordType.h"

#include <sstream>
#include <stdlib.h>
#include <time.h>

using namespace comp;
using namespace comp::cmd;
using namespace std;

// SeriesCommand ---------------------------------------------------------------
// -----------------------------------------------------------------------------

bool SeriesCommand::CanAddChild(const Composite * pChild) const
{
    return dynamic_cast<const Command *>(pChild) != NULL;
}

string SeriesCommand::GetName() const
{
    return "复合命令:命令序列";
}
string SeriesCommand::GetDescription() const
{
	string ret = GetName();
    if (!m_remark.empty())
	{
		ret += " (";
		ret += m_remark;
		ret += ")";
	}

	return ret;
}

bool SeriesCommand::Configure(const std::string& str)
{
	m_remark = str;
	return true;
}

std::string SeriesCommand::GetConfiguration() const
{
	return m_remark;
}

Component * SeriesCommand::CreateObject() const
{
    return new SeriesCommand;
}

bool SeriesCommand::Execute(NavigateWnd * pWnd) const
{
    Command * pCmd;
    CompositeArray::const_iterator ci;
    for (ci = m_arrComp.begin(); ci != m_arrComp.end(); ++ci)
    {
        pCmd = dynamic_cast<Command *>(*ci);
        if (pCmd != NULL)
        {
            pCmd->Execute(pWnd);
        }
    }
    return true;
}

// RandomCommand ---------------------------------------------------------------
// -----------------------------------------------------------------------------

bool RandomCommand::CanAddChild(const Composite * pChild) const
{
    return dynamic_cast<const Command *>(pChild) != NULL;
}

string RandomCommand::GetName() const
{
    return "复合命令:随机命令";
}
string RandomCommand::GetDescription() const
{
    return GetName();
}

Component * RandomCommand::CreateObject() const
{
    return new RandomCommand;
}

bool RandomCommand::Execute(NavigateWnd * pWnd) const
{
    size_t length = m_arrComp.size();
	if (length > 0)
	{
		Command * pCmd = dynamic_cast<Command *>(m_arrComp[rand() % length]);
		if (pCmd != NULL)
		{
			pCmd->Execute(pWnd);
			return true;
		}
	}

    return false;
}

// IfCommand -------------------------------------------------------------------
// -----------------------------------------------------------------------------

bool IfCommand::CanAddChild(const Composite * pChild) const
{
    size_t len = m_arrComp.size();
    if (len == 0)
    {
		return (dynamic_cast<const cond::Condition *>(pChild) != NULL);
    }
    else if (len == 1)
    {
        if (dynamic_cast<const cond::Condition *>(m_arrComp[0]) != NULL)
        {
            return dynamic_cast<const Command *>(pChild) != NULL;
        }
        else
        {
            return dynamic_cast<const cond::Condition *>(pChild) != NULL;
        }
    }
    else
    {
        return false;
    }
}

bool IfCommand::HaveRoom() const
{
    return (m_arrComp.size() < 2);
}

bool IfCommand::CheckValid() const
{
	bool has_cond = false;
	bool has_cmd = false;

	if (m_arrComp.size() != 2) return false;

	(dynamic_cast<const cond::Condition *>(m_arrComp[0]) != NULL) ?
		has_cond = true : has_cmd = true;
	(dynamic_cast<const cond::Condition *>(m_arrComp[1]) != NULL) ?
		has_cond = true : has_cmd = true;

	return (has_cmd && has_cond);
}

string IfCommand::GetName() const
{
    return "复合命令:条件命令";
}
string IfCommand::GetDescription() const
{
    return GetName();
}

Component * IfCommand::CreateObject() const
{
    return new IfCommand;
}

bool IfCommand::Execute(NavigateWnd * pWnd) const
{
    if (m_arrComp.size() >= 2)
    {
        cond::Condition * pCond;
        Command * pCmd;
        pCond = dynamic_cast<cond::Condition *>(m_arrComp[0]);
        if (pCond != NULL)
        {
            pCmd = dynamic_cast<Command *>(m_arrComp[1]);
        }
        else
        {
            pCond = dynamic_cast<cond::Condition *>(m_arrComp[1]);
            pCmd = dynamic_cast<Command *>(m_arrComp[0]);
        }
        
        if (pCond && pCmd && pWnd->GetCurrentWord() != NULL && pCond->Meet(pWnd->GetCurrentWord()))
        {
            pCmd->Execute(pWnd);
        }
    }

    return false;
}


// TimerCommand ----------------------------------------------------------------
// -----------------------------------------------------------------------------

TimerCommand::TimerCommand()
{
    m_interval = 0;
	m_repeat_time = 1;
	m_global = false;
}

bool TimerCommand::CanAddChild(const Composite * pChild) const
{
    return dynamic_cast<const Command *>(pChild) != NULL;
}

bool TimerCommand::HaveRoom() const
{
    return (m_arrComp.size() == 0);
}

bool TimerCommand::CheckValid() const
{
	return (m_arrComp.size() == 1);
}

string TimerCommand::GetName() const
{
    return "复合命令:定时器命令";
}
string TimerCommand::GetDescription() const
{
    stringstream ss;
	if (m_global) ss << "(全局)";
    ss << "定时器:" << "以间隔" << m_interval << "(ms)执行子命令" << m_repeat_time << "次";
    return ss.str();
}

bool TimerCommand::Configure(const std::string& str)
{
    stringstream(str) >> m_interval >> m_repeat_time >> m_global;
	if (m_repeat_time == 0)
	{
		m_repeat_time = 1;
	}
    return true;
}

string TimerCommand::GetConfiguration() const
{
    stringstream ss;
    ss << m_interval << " " << m_repeat_time << " " << m_global;
    return ss.str();
}

Component * TimerCommand::CreateObject() const
{
    return new TimerCommand;
}

bool TimerCommand::Execute(NavigateWnd * pWnd) const
{
    if (m_arrComp.size() > 0)
    {
        Command * pCmd = dynamic_cast<Command *>(*m_arrComp.begin());
        return pWnd->TimerExecute(m_interval, m_repeat_time, m_global, pCmd);
    }
    return false;
}

// HotkeyCommand ----------------------------------------------------------------
// -----------------------------------------------------------------------------

HotkeyCommand::HotkeyCommand()
{
    m_acl.fVirt = 0;
    m_acl.key = 0;
	m_global = false;
}

bool HotkeyCommand::CanAddChild(const Composite * pChild) const
{
    return dynamic_cast<const Command *>(pChild) != NULL;
}

bool HotkeyCommand::HaveRoom() const
{
    return (m_arrComp.size() == 0);
}

bool HotkeyCommand::CheckValid() const
{
	return (m_acl.key > 0 && m_arrComp.size() == 1);
}

string HotkeyCommand::GetName() const
{
    return "复合命令:热键命令";
}
string HotkeyCommand::GetDescription() const
{
	std::string child_cmd("子命令");
	if (m_arrComp.size() > 0)
	{
		child_cmd = m_arrComp[0]->GetDescription();
	}

	std::string key("快捷键");
	if (!m_strAccel.empty())
	{
		key = m_strAccel;
	}

	stringstream ss;
	if (m_global) ss << "(全局)";
	ss << "当按 " << key << " 时执行 " << child_cmd;
	return ss.str();
}

bool HotkeyCommand::Configure(const std::string& str)
{
    static regex::rpattern pat("[^ ]+ [^ ]+ [^ ]+ (.*)");
    regex::match_results ret;

    stringstream ss(str);
    ss >> (int&)m_acl.fVirt >> m_acl.key >> m_global;

    pat.match(str, ret);
    m_strAccel = ret.backref(1).str();
    
    return true;
}

string HotkeyCommand::GetConfiguration() const
{
    stringstream ss;
    ss << (int)m_acl.fVirt << " " << m_acl.key << " " << m_global << " " << m_strAccel;
    return ss.str();
}

Component * HotkeyCommand::CreateObject() const
{
    return new HotkeyCommand;
}

bool HotkeyCommand::Execute(NavigateWnd * pWnd) const
{
    if (m_arrComp.size() > 0)
    {
        Command * pCmd = dynamic_cast<Command *>(*m_arrComp.begin());
        return pWnd->RegHotKey(m_acl, m_global, pCmd);
    }
    return false;
}

// MoveWordCommand -------------------------------------------------------------
// -----------------------------------------------------------------------------

const char MoveWordCommand::ms_arrOp[][32] =
{
    "移到第一个单词",
    "移到最后一个单词",
    "移到上一个单词",
    "移到下一个单词",
    ""
};

MoveWordCommand::MoveWordCommand()
{
    m_op = NavigateWnd::next;
}

bool MoveWordCommand::CheckValid() const
{
	return (m_op <= NavigateWnd::next);
}

string MoveWordCommand::GetName() const
{
    return "单一命令:改变当前单词";
}
string MoveWordCommand::GetDescription() const
{
    return ms_arrOp[m_op];
}
bool MoveWordCommand::Configure(const std::string& str)
{
    for (int i = 0; ms_arrOp[i][0] != '\0'; i++)
    {
        if (str == ms_arrOp[i])
        {
            m_op = static_cast<NavigateWnd::MoveOp>(i);
            return true;
        }
    }

    return false;
}
string MoveWordCommand::GetConfiguration() const
{
    return ms_arrOp[m_op];
}

Leaf * MoveWordCommand::CreateObject() const
{
    return new MoveWordCommand;
}

bool MoveWordCommand::Execute(NavigateWnd * pWnd) const
{
    return pWnd->MoveWord(m_op);
}

// SetColorCommand -------------------------------------------------------------
// -----------------------------------------------------------------------------

SetColorCommand::SetColorCommand()
{
    m_cr = 0;
}

bool SetColorCommand::CheckValid() const
{
	return (!m_color_element.empty());
}

string SetColorCommand::GetName() const
{
    return "单一命令:设置颜色";
}
string SetColorCommand::GetDescription() const
{
    int r, g, b;
    stringstream ss;

    r = m_cr & 0xff;
    g = (m_cr >> 8) & 0xff;
    b = (m_cr >> 16) & 0xff;

    ss << "设置" << m_color_element << "颜色为: RGB("
       << r << "," << g << "," << b << ")";

    return ss.str();
}
bool SetColorCommand::Configure(const std::string& str)
{
    stringstream ss(str);
    ss >> m_color_element >> m_cr;
    return true;
}
string SetColorCommand::GetConfiguration() const
{
    stringstream ss;
	if (!m_color_element.empty())
	{
		ss << m_color_element << " " << m_cr;
	}
    return ss.str();
}

Leaf * SetColorCommand::CreateObject() const
{
    return new SetColorCommand;
}

bool SetColorCommand::Execute(NavigateWnd * pWnd) const
{
    return pWnd->SetColor(m_color_element, m_cr);
}

// OpenDlgCommand -------------------------------------------------------------
// -----------------------------------------------------------------------------

OpenDlgCommand::OpenDlgCommand()
{
}

bool OpenDlgCommand::CheckValid() const
{
	return (!m_dlg_name.empty());
}

string OpenDlgCommand::GetName() const
{
	return "单一命令:打开对话框";
}
string OpenDlgCommand::GetDescription() const
{
	if (m_dlg_name.empty())
	{
		return GetName();
	}
	else
	{
		stringstream ss;
		ss << "打开" << m_dlg_name;
		return ss.str();
	}
}
bool OpenDlgCommand::Configure(const std::string& str)
{
	m_dlg_name = str;
	return true;
}
string OpenDlgCommand::GetConfiguration() const
{
	return m_dlg_name;
}

Leaf * OpenDlgCommand::CreateObject() const
{
	return new OpenDlgCommand;
}

bool OpenDlgCommand::Execute(NavigateWnd * pWnd) const
{
	return pWnd->OpenDialog(m_dlg_name);
}

// ShowElementCommand -------------------------------------------------------------
// -----------------------------------------------------------------------------

ShowElementCommand::ShowElementCommand()
{
	m_show = true;
}

bool ShowElementCommand::CheckValid() const
{
	return (!m_visual_element.empty());
}

string ShowElementCommand::GetName() const
{
	return "单一命令:界面元素显示";
}
string ShowElementCommand::GetDescription() const
{
	stringstream ss;
	ss << (m_show ? "显示" : "隐藏") << m_visual_element;
	return ss.str();
}
bool ShowElementCommand::Configure(const std::string& str)
{
	stringstream ss(str);
	ss >> m_visual_element >> m_show;
	return true;
}
string ShowElementCommand::GetConfiguration() const
{
	stringstream ss;
	if (!m_visual_element.empty())
	{
		ss << m_visual_element << " " << m_show;
	}
	return ss.str();
}

Leaf * ShowElementCommand::CreateObject() const
{
	return new ShowElementCommand;
}

bool ShowElementCommand::Execute(NavigateWnd * pWnd) const
{
	return pWnd->ShowElement(m_visual_element, m_show);
}


// SetWordTypeCommand -------------------------------------------------------------
// -----------------------------------------------------------------------------

SetWordTypeCommand::SetWordTypeCommand()
: m_style(NavigateWnd::add)
{
}

bool SetWordTypeCommand::CheckValid() const
{
	return (WordType::Instance()->GetTypeIndex(m_word_type) != (size_t)-1);
}

string SetWordTypeCommand::GetName() const
{
	return "单一命令:设置单词属性";
}
string SetWordTypeCommand::GetDescription() const
{
	string style;
	switch (m_style)
	{
	case NavigateWnd::add:    style = "设置"; break;
	case NavigateWnd::del:    style = "取消"; break;
	case NavigateWnd::toggle: style = "切换"; break;
	default:break;
	}

	stringstream ss;
	ss << style << "属性为" << m_word_type;
	return ss.str();
}

bool SetWordTypeCommand::Configure(const std::string& str)
{
	regex::rpattern pat("^(.*) ([0-9]+)$");
	regex::match_results ret;

	if (pat.match(str, ret).matched)
	{
		m_word_type = ret.backref(1).str();
		stringstream(ret.backref(2).str()) >> (int&)m_style;
		return true; 
	}
	else
	{
		return false;
	}
}
string SetWordTypeCommand::GetConfiguration() const
{
	stringstream ss;
	ss << m_word_type << " " << m_style;
	return ss.str();
}

Leaf * SetWordTypeCommand::CreateObject() const
{
	return new SetWordTypeCommand;
}

bool SetWordTypeCommand::Execute(NavigateWnd * pWnd) const
{
	size_t index = WordType::Instance()->GetTypeIndex(m_word_type);
	return pWnd->SetWordType(index, m_style);
}


// MiscCommand -------------------------------------------------------------
// -----------------------------------------------------------------------------

MiscCommand::MiscCommand()
{
}

bool MiscCommand::CheckValid() const
{
	return (!m_cmd.empty());
}

string MiscCommand::GetName() const
{
	return "单一命令:杂项命令";
}
string MiscCommand::GetDescription() const
{
	return m_cmd.empty() ? GetName() : m_cmd;
}

bool MiscCommand::Configure(const std::string& str)
{
	m_cmd = str;
	return true;
}
string MiscCommand::GetConfiguration() const
{
	return m_cmd;
}

Leaf * MiscCommand::CreateObject() const
{
	return new MiscCommand;
}

bool MiscCommand::Execute(NavigateWnd * pWnd) const
{
	return pWnd->RunMiscCommand(m_cmd);
}


// LoadCompCommand -------------------------------------------------------------
// -----------------------------------------------------------------------------

LoadCompCommand::LoadCompCommand()
{
}

bool LoadCompCommand::CheckValid() const
{
	CFileFind ff;
	return ff.FindFile(m_composite_file.c_str())? true : false;
}

string LoadCompCommand::GetName() const
{
	return "单一命令:加载背诵方案命令";
}
string LoadCompCommand::GetDescription() const
{
	stringstream ss;
	if (m_composite_file.empty() || !CheckValid())
	{
		ss << GetName();
	}
	else
	{
		ss << "从文件<" 
		   << m_composite_file.substr(m_composite_file.rfind('\\') + 1)
		   << ">中加载背诵方案";
	}
	
	return ss.str();
}

bool LoadCompCommand::Configure(const std::string& str)
{
	m_composite_file = str;
	return true;
}
string LoadCompCommand::GetConfiguration() const
{
	return m_composite_file;
}

Leaf * LoadCompCommand::CreateObject() const
{
	return new LoadCompCommand;
}

bool LoadCompCommand::Execute(NavigateWnd * pWnd) const
{
	return pWnd->LoadComposite(m_composite_file);
}
