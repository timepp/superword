#include "concretecondition.h"
#include "Word.h"
#include "LibSrc/greta/regexpr2.h"
#include "helper.h"
#include "WordType.h"
#include "resource.h"
#include "NavigateWnd.h"
#include "NavigateWndCreator.h"

#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace comp;
using namespace comp::cond;
using namespace std;
using namespace regex;
using namespace word;

// AndCondition ----------------------------------------------------------------
// -----------------------------------------------------------------------------

bool AndCondition::CanAddChild(const Composite * pChild) const
{
    return dynamic_cast<const Condition *>(pChild) != NULL;
}

string AndCondition::GetName() const
{
    return "复合条件:与";
}
string AndCondition::GetDescription() const
{
    return GetName();
}

Component * AndCondition::CreateObject() const
{
    return new AndCondition();
}

bool AndCondition::Meet(const void * pTestee) const
{
    Condition * pCond;
    CompositeArray::const_iterator ci;
    for (ci = m_arrComp.begin(); ci != m_arrComp.end(); ++ci)
    {
        pCond = dynamic_cast<Condition *>(*ci);
        if (pCond != NULL && !pCond->Meet(pTestee))
        {
            return false;
        }
    }
    return true;
}

// OrCondition ----------------------------------------------------------------
// -----------------------------------------------------------------------------

bool OrCondition::CanAddChild(const Composite * pChild) const
{
    return dynamic_cast<const Condition *>(pChild) != NULL;
}

string OrCondition::GetName() const
{
    return "复合条件:或";
}
string OrCondition::GetDescription() const
{
    return GetName();
}

Component * OrCondition::CreateObject() const
{
    return new OrCondition();
}

bool OrCondition::Meet(const void * pTestee) const
{
    Condition * pCond;
    CompositeArray::const_iterator ci;
    for (ci = m_arrComp.begin(); ci != m_arrComp.end(); ++ci)
    {
        pCond = dynamic_cast<Condition *>(*ci);
        if (pCond != NULL && pCond->Meet(pTestee))
        {
            return true;
        }
    }
    return false;
}

// NotCondition ----------------------------------------------------------------
// -----------------------------------------------------------------------------

bool NotCondition::CanAddChild(const Composite * pChild) const
{
    return dynamic_cast<const Condition *>(pChild) != NULL;
}

bool NotCondition::HaveRoom() const
{
    return (m_arrComp.size() == 0);
}

bool NotCondition::CheckValid() const
{
	return (m_arrComp.size() == 1);
}

string NotCondition::GetName() const
{
    return "复合条件:非";
}
string NotCondition::GetDescription() const
{
    return GetName();
}

Component * NotCondition::CreateObject() const
{
    return new NotCondition();
}

bool NotCondition::Meet(const void * pTestee) const
{
    Condition * pCond;
    if (m_arrComp.size() > 0)
    {
        pCond = dynamic_cast<Condition *>(*m_arrComp.begin());
        if (pCond != NULL)
        {
            return !pCond->Meet(pTestee);
        }
    }

    return true;
}

// WordCondition ---------------------------------------------------------------
// -----------------------------------------------------------------------------

string WordCondition::GetName() const
{
    return "简单条件:单词";
}

bool WordCondition::CheckValid() const
{
	return (!m_match_str.empty());
}

string WordCondition::GetDescription() const
{
    string str = "单词匹配:";
    str += m_match_str;
    return str;
}

bool WordCondition::Configure(const std::string& str)
{
    m_match_str = str;
    if (m_match_str.empty())
    {
        m_match_str = ".*";
    }

    m_match_pat = rpattern(m_match_str);
    return true;
}

string WordCondition::GetConfiguration() const
{
    return m_match_str;
}

Leaf * WordCondition::CreateObject() const
{
    return new WordCondition();
}

bool WordCondition::Meet(const void * pTestee) const
{
    regex::match_results ret;
    const Word * pWord;
    pWord = reinterpret_cast<const Word *>(pTestee);
    /* TODO Low efficiency */
    return (m_match_pat.match(string(pWord->word()), ret).matched);
}

// MeaningCondition ---------------------------------------------------------------
// -----------------------------------------------------------------------------
MeaningCondition::MeaningCondition()
{
    m_match_detail_meaning = false;
}

bool MeaningCondition::CheckValid() const
{
	return (!m_match_str.empty());
}

string MeaningCondition::GetName() const
{
    return "简单条件:汉意";
}

string MeaningCondition::GetDescription() const
{
    string str = m_match_detail_meaning ? "详细汉意匹配:" : "汉意匹配:";
    str += m_match_str;
    return str;
}

bool MeaningCondition::Configure(const std::string& str)
{
    static regex::rpattern pat("[^ ]+ (.*)");
    regex::match_results ret;

    stringstream ss(str);
    ss >> m_match_detail_meaning;

    pat.match(str, ret);
    m_match_str = ret.backref(1).str();

    if (m_match_str.empty())
    {
        m_match_str = ".*";
    }
    m_match_pat = rpattern(m_match_str);

    return true;
}

string MeaningCondition::GetConfiguration() const
{
    stringstream ss;
    ss << m_match_detail_meaning << " " << m_match_str;
    return ss.str();
}

Leaf * MeaningCondition::CreateObject() const
{
    return new MeaningCondition();
}

bool MeaningCondition::Meet(const void * pTestee) const
{
    regex::match_results ret;
    const Word * pWord;
    pWord = reinterpret_cast<const Word *>(pTestee);
    const char * meaning = 
        m_match_detail_meaning ? pWord->detail_meaning() : pWord->meaning();
    return (m_match_pat.match(string(meaning), ret).matched);
}

// PhoneticCondition ---------------------------------------------------------------
// -----------------------------------------------------------------------------

bool PhoneticCondition::CheckValid() const
{
	return (!m_match_str.empty());
}

string PhoneticCondition::GetName() const
{
    return "简单条件:音标";
}

string PhoneticCondition::GetDescription() const
{
    string str = "音标匹配:";
    str += m_match_str;
    return str;
}

bool PhoneticCondition::Configure(const std::string& str)
{
    m_match_str = str;
    if (m_match_str.empty())
    {
        m_match_str = ".*";
    }

    m_match_pat = rpattern(m_match_str);
    return true;
}

string PhoneticCondition::GetConfiguration() const
{
    return m_match_str;
}

Leaf * PhoneticCondition::CreateObject() const
{
    return new PhoneticCondition();
}

bool PhoneticCondition::Meet(const void * pTestee) const
{
    regex::match_results ret;
    const word::Word * pWord;
    pWord = reinterpret_cast<const word::Word *>(pTestee);
    return (m_match_pat.match(string(pWord->phonetic()), ret).matched);
}

// AccesstimeCondition ---------------------------------------------------------------
// -----------------------------------------------------------------------------
AccesstimeCondition::AccesstimeCondition()
{
    m_use_relative_time = true;
    m_relative_time = 0;
    m_min_time_valid = 1;
    m_min_time = 0;
    m_max_time_valid = 1;
    m_max_time = time(NULL);
}

bool AccesstimeCondition::CheckValid() const
{
	return true;
}

string AccesstimeCondition::GetName() const
{
    return "简单条件:访问时间";
}

string AccesstimeCondition::GetDescription() const
{
    stringstream ss;
    ss << "访问时间";
    if (m_use_relative_time)
    {
        ss << "为";
        switch (m_relative_time)
        {
        case 0:  ss << "今天"; break;
        case 1: ss << "昨天"; break;
        case -1:  ss << "明天"; break;
        default: 
            ss << std::abs(m_relative_time) << (m_relative_time > 0? "天前" : "天后");
            break;
        }
    }
    else
    {
        char buf[32];
		tm s_min_time;
		tm s_max_time;
		localtime_s(&s_min_time, &m_min_time);
		localtime_s(&s_max_time, &m_max_time);

        ss << "在";
        if (!m_min_time_valid)
        {
            strftime(buf, 32, "%Y年%m月%d日之前", &s_min_time);
            ss << buf;
        }
        else if (!m_max_time_valid)
        {
            strftime(buf, 32, "%Y年%m月%d日之后", &s_max_time);
            ss << buf;
        }
        else
        {
            strftime(buf, 32, "%Y年%m月%d日", &s_min_time);
            ss << buf << " 和 ";
            strftime(buf, 32, "%Y年%m月%d日", &s_max_time);
            ss << buf << " 之间";
        }
    }

    return ss.str();
}

bool AccesstimeCondition::Configure(const std::string& str)
{
    stringstream ss(str);
    ss >> m_use_relative_time >> m_relative_time
       >> m_min_time_valid >> m_max_time_valid >> m_min_time >> m_max_time;
    return true;
}

string AccesstimeCondition::GetConfiguration() const
{
    stringstream ss;
    ss << m_use_relative_time << " " << m_relative_time << " "
       << m_min_time_valid << " " << m_max_time_valid << " "
       << m_min_time << " " << m_max_time;
    return ss.str();
}

Leaf * AccesstimeCondition::CreateObject() const
{
    return new AccesstimeCondition();
}

bool AccesstimeCondition::Meet(const void * pTestee) const
{
    const Word * pWord = reinterpret_cast<const Word *>(pTestee);
	time_t at = pWord->access_time();

    if (m_use_relative_time)
    {
        time_t time_cp = time(NULL) - m_relative_time * 86400;
        struct tm tm_access;
        struct tm tm_cp;
		localtime_s(&tm_access, &at);
		localtime_s(&tm_cp, &time_cp);

        return (tm_access.tm_year == tm_cp.tm_year &&
                tm_access.tm_mon == tm_cp.tm_mon &&
                tm_access.tm_mday == tm_cp.tm_mday);
    }
    else
    {
		if (m_min_time_valid && at < m_min_time) return false;
		if (m_max_time_valid && at > m_max_time) return false;
		return true;
    }
}

// ClassCondition ---------------------------------------------------------------
// -----------------------------------------------------------------------------

bool ClassCondition::CheckValid() const
{
	return (m_words.size() > 0);
}

string ClassCondition::GetName() const
{
    return "简单条件:单词类别";
}

string ClassCondition::GetDescription() const
{
    stringstream ss;
    ss << "单词类别为 " << m_class;
    return ss.str();
}

bool ClassCondition::Configure(const std::string& str)
{
    m_class = str;
    InitializeWords();
    return true;
}

string ClassCondition::GetConfiguration() const
{
    return m_class;
}

Leaf * ClassCondition::CreateObject() const
{
    return new ClassCondition();
}

bool ClassCondition::Meet(const void * pTestee) const
{
    const Word * pWord = reinterpret_cast<const Word *>(pTestee);
    return binary_search(m_words.begin(), m_words.end(), string(pWord->word()));
}

bool ClassCondition::HaveChineseChar(const char * str)
{
    while (*str && *str < 0x80) str++;
    return !*str;
}

bool ClassCondition::InitializeWords()
{
    static regex::rpattern word1("^\\s*([A-Za-z\\. -']*[A-Za-z\\.])\\s*$");
    static regex::match_results word;

    // open file
    stringstream ss;
    ss << helper::SWPath(helper::IDS(IDSP_WORD_CLASS)) << "\\" << m_class << ".txt";
    ifstream is(ss.str().c_str());
    if (!is) return FALSE;

    char prev_line[2048] = "";
    char curr_line[2048] = "";
    UserWord uw;
    enum {unknown, read_word, read_meaning} state = unknown;

    m_words.clear();
    while (is.good())
    {
        is.getline(curr_line, sizeof(curr_line));

        switch (state)
        {
        case unknown:
            strcpy_s(prev_line, curr_line);
            state = HaveChineseChar(curr_line) ? read_word : read_meaning;
            break;
        case read_word:
            if (HaveChineseChar(curr_line))
            {
                uw.set_word(prev_line);
                uw.set_meaning(curr_line);
                m_words.push_back(prev_line);
                state = unknown;
            }
            break;
        case read_meaning:
            if (!HaveChineseChar(curr_line))
            {
                uw.set_word(curr_line);
                uw.set_meaning(prev_line);
                m_words.push_back(curr_line);
                state = unknown;
            }
            break;
        default:
            break;
        }
    }

    std::sort(m_words.begin(), m_words.end());
    return TRUE;
}

bool ClassCondition::AddUserWord(const UserWord& uw)
{
    FixedWordsCreator * pFwCreator = FixedWordsCreator::Instance();
    const WordVector * pFwv = pFwCreator->GetWords();
    
    if (std::binary_search(pFwv->begin(), pFwv->end(), &uw, word_less))
    {
        return FALSE;
    }
    
    UserWordsCreator * pUwCreator = UserWordsCreator::Instance();
    WordVector * pUwv = pUwCreator->GetWords();
    WordVector::iterator it = std::lower_bound(pUwv->begin(), pUwv->end(), &uw, word_less);
    if (it != pUwv->end() && strcmp((*it)->word(), uw.word()) == 0)
    {
        (*it)->set_meaning(uw.meaning());
    }
    else
    {
        UserWord * pUw = new UserWord(uw);
        pUwv->insert(it, pUw);
        return TRUE;
    }

    return FALSE;
}

// TypeCondition ---------------------------------------------------------------
// -----------------------------------------------------------------------------

bool TypeCondition::CheckValid() const
{
	return (WordType::Instance()->GetTypeIndex(m_str_type) >= 0);
}

string TypeCondition::GetName() const
{
	return "简单条件:属性";
}

string TypeCondition::GetDescription() const
{
	string str = "单词属性为:";
	str += m_str_type;
	return str;
}

bool TypeCondition::Configure(const std::string& str)
{
	WordType *pWt = WordType::Instance();
	m_str_type = str;
	m_type = static_cast<unsigned short>(pWt->GetTypeIndex(m_str_type));
	return true;
}

string TypeCondition::GetConfiguration() const
{
	return m_str_type;
}

Leaf * TypeCondition::CreateObject() const
{
	return new TypeCondition();
}

bool TypeCondition::Meet(const void * pTestee) const
{
	const word::Word * pWord;
	pWord = reinterpret_cast<const word::Word *>(pTestee);
	return ((pWord->type() & (1 << m_type)) != 0);
}


// MiscCondition ---------------------------------------------------------------
// -----------------------------------------------------------------------------

bool MiscCondition::CheckValid() const
{
	return true;
}

string MiscCondition::GetName() const
{
	return "运行时条件:杂项条件";
}

string MiscCondition::GetDescription() const
{
	return m_cond_desc.empty()? GetName() : m_cond_desc;
}

bool MiscCondition::Configure(const std::string& str)
{
	m_cond_desc = str;
	return true;
}

string MiscCondition::GetConfiguration() const
{
	return m_cond_desc;
}

Leaf * MiscCondition::CreateObject() const
{
	return new MiscCondition();
}

bool MiscCondition::Meet(const void *) const
{
	NavigateWnd *pWnd = NavigateWndCreator::Instance()->GetCurrentNavigateWnd();
	return pWnd->CheckMiscCondition(m_cond_desc);
}
