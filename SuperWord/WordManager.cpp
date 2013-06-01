 // WordManager.cpp: implementation of the CWordManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SuperWord.h"
#include "WordManager.h"
#include "ProgressDlg.h"
#include "CompositeCreator.h"
#include "Condition.h"

#include <algorithm>
#include <functional>
#include <fstream>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

using namespace comp;

NullWord CWordManager::s_nw;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWordManager::CWordManager() 
: m_nPos(0)
{
	FixedWordsCreator *pCreator = FixedWordsCreator::Instance();
	m_pAllWords = const_cast<WordVector*>(pCreator->GetWords());
	UserWordsCreator * pUwCreator = UserWordsCreator::Instance();
	m_pUserWords = pUwCreator->GetWords();

	ReFilterWords();
}

CWordManager::~CWordManager()
{

}

size_t CWordManager::WordCount() const
{
	return m_useWords.size();
}

BOOL CWordManager::IsFirst() const
{
	return (m_nPos <= 0);
}
BOOL CWordManager::IsLast() const
{
	return (m_nPos >= m_useWords.size() - 1);
}

Word * CWordManager::MovePrev()
{
	if (m_useWords.size() == 0) return &s_nw;

	if (m_nPos > 0) m_nPos--;
	return m_useWords[m_nPos];
}
Word * CWordManager::MoveNext()
{
	if (m_useWords.size() == 0) return &s_nw;

	if (m_nPos < m_useWords.size() - 1) m_nPos++;
	return m_useWords[m_nPos];
}
Word * CWordManager::MoveFirst()
{
	if (m_useWords.size() == 0) return &s_nw;
	
	m_nPos = 0;
	return m_useWords[m_nPos];
}
Word * CWordManager::MoveLast()
{
	if (m_useWords.size() == 0) return &s_nw;

	m_nPos = m_useWords.size() - 1;
	return m_useWords[m_nPos];
}
Word * CWordManager::Current()
{
	if (m_useWords.size() == 0) return &s_nw;

	return m_useWords[m_nPos];
}
size_t CWordManager::GetCurrentPos() const
{
	 return m_nPos + 1;
}

// 查询单个单词，如果查不到返回空，否则返回单词指针
Word * CWordManager::QuerySpecial(LPCTSTR pszWord)
{
	UserWord uw;
	uw.set_word(pszWord);
	WordVector::const_iterator ci;
	// 先在固有单词中查
	ci = std::lower_bound(m_pAllWords->begin(), m_pAllWords->end(), &uw, WordLess);
	if (ci != m_pAllWords->end() && strcmp((*ci)->word(), pszWord) == 0)
	{
		return (*ci);
	}
	// 再在类别中查
	ci = std::lower_bound(m_pUserWords->begin(), m_pUserWords->end(), &uw, WordLess);
	if (ci != m_pUserWords->end() && strcmp((*ci)->word(), pszWord) == 0)
	{
		if ((*ci)->meaning()[0] != '\0')
			return (*ci);
	}

	return NULL;
}

bool CWordManager::WordLess(const Word* pW1, const Word* pW2)
{
	return strcmp(pW1->word(), pW2->word()) < 0;
}
bool CWordManager::WordGreater(const Word* pW1, const Word* pW2)
{
	return strcmp(pW1->word(), pW2->word()) > 0;
}
bool CWordManager::AccessTimeLess(const Word* pW1, const Word* pW2)
{
	return pW1->access_time() < pW2->access_time();
}
bool CWordManager::AccessTimeGreater(const Word* pW1, const Word* pW2)
{
	return pW1->access_time() > pW2->access_time();
}

void CWordManager::SortWords(DWORD dwWordOrder)
{
	int nSortType = dwWordOrder & 0x0f;
	int nSortBy = dwWordOrder & 0xf0;
	bool (*f)(const Word*, const Word*) = NULL;

	switch (nSortType)
	{
	case WO_NOSORT:
		return;
	case WO_RANDOM:
		srand(static_cast<unsigned int>(time(NULL)));
		std::random_shuffle(m_useWords.begin(), m_useWords.end());
		return;
	case WO_ASC:
		switch (nSortBy)
		{
		case WO_BY_WORD:        f = WordLess; break;
		case WO_BY_ACCESS_TIME: f = AccessTimeLess; break;
		default: break;
		}
		break;
	case WO_DESC:
		switch (nSortBy)
		{
		case WO_BY_WORD:        f = WordGreater; break;
		case WO_BY_ACCESS_TIME: f = AccessTimeGreater; break;
		default: break;
		}
		break;
	default:
		break;
	}

	if (f != NULL)
	{
		std::sort(m_useWords.begin(), m_useWords.end(), f);
	}
}


void CWordManager::ReFilterWords()
{
	m_useWords.clear();
    cond::Condition * pCond = CompositeCreator::GetFilter();
	
	CProgressDlg *pDlg = CProgressDlg::Instance();
	pDlg->RestartTask(_T("正在过滤单词..."), m_pAllWords->size() + m_pUserWords->size());

	WordVector::const_iterator ci;
	for (ci = m_pAllWords->begin(); ci != m_pAllWords->end(); ++ci)
	{
		if (pCond == NULL || pCond->Meet(*ci))
		{
			m_useWords.push_back(*ci);
		}
		pDlg->StepIt();
	}
	for (ci = m_pUserWords->begin(); ci != m_pUserWords->end(); ++ci)
	{
		if ((*ci)->meaning()[0] && (pCond == NULL || pCond->Meet(*ci)))
		{
			m_useWords.push_back(*ci);
		}
		pDlg->StepIt();
	}

	pDlg->SetTaskName(_T("正在对单词排序..."));

	GlobalSetting *pSet = GlobalSetting::Instance();
	SortWords(pSet->Ms.dwWordOrder);
	
	pDlg->SetWindowPos(&CWnd::wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	pDlg->ShowWindow(SW_HIDE);
	
//	if (m_useWords.size() == 0)
//		m_nPos = -1;
}

void CWordManager::OutputWordData()
{
	using std::ios;
	std::sort(m_pAllWords->begin(), m_pAllWords->end(), WordLess);
	WordVector vw;
	std::vector<std::string> wow;

	// 取出单词
	UserWord *pUw;
	WordVector::iterator it;
	char w[256], m[256];
	std::ifstream is("E:\\timepp\\program\\SuperWord\\SuperWord\\Product\\WordClass\\add.txt");
	while (is.good())
	{
		pUw = new UserWord;
		is.getline(w, 256);
		do {
			is.getline(m, 256);	
		} while(is.good() && !helper::HavingChineseChar(m));
		if (!is.good()) break;

		pUw->set_word(w);
		pUw->set_meaning(m);
		pUw->set_type(0);
		pUw->set_access_time(0);

		it = std::lower_bound(m_pAllWords->begin(), m_pAllWords->end(), pUw, WordLess);
		bool b_add_new = true;
		bool b_change = false;
		const char * old_word = NULL;
		const char * old_meaning = NULL;
		if (it != m_pAllWords->end())
		{
			old_word = (*it)->word();
			old_meaning = (*it)->meaning();
			if (strcmp(old_word, pUw->word()) == 0)
			{
				b_add_new = false;
				if (strlen(old_meaning) + 4 < strlen(pUw->meaning()))
				{
					b_change = true;
				}
			}
		}

		BOOL bDelete = TRUE;
		if (b_change)
		{
			CString str;
			str.Format("确认修改单词: \n原单词：%s\n中文意思：%s\n新的意思: %s\n", old_word, old_meaning, pUw->meaning());
//			if (AfxMessageBox(str, MB_OKCANCEL) == IDOK)
			{
//				replaced++;
//				*it = pUw;
//				bDelete = FALSE;
			}
		}
		else if (b_add_new)
		{
			CString str;
			str.Format("确认添加单词：\n单词：%s\n中文意思：%s\n", pUw->word(), pUw->meaning());
			if (std::find(wow.begin(), wow.end(), pUw->word()) == wow.end())
			{
//				if (AfxMessageBox(str, MB_OKCANCEL) == IDOK)	
				{
					vw.push_back(pUw);
					wow.push_back(pUw->word());
					bDelete = FALSE;
				}
			}
		}
		if (bDelete) delete pUw;
	}

	for (it = vw.begin(); it != vw.end(); ++it)
		m_pAllWords->push_back(*it);

	std::sort(m_pAllWords->begin(), m_pAllWords->end(), WordLess);
	std::ofstream os("d:\\word.dat", ios::binary | ios::out);
	os.seekp(0x100, ios::beg);
	WordVector::const_iterator ci;
	for (ci = m_pAllWords->begin(); ci != m_pAllWords->end(); ++ci)
	{
		os << *ci;
	}
}