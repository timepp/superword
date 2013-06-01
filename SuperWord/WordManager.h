// WordManager.h: interface for the CWordManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WORDMANAGER_H__865DFB1E_C04B_4B41_A2B2_257E6B8C6950__INCLUDED_)
#define AFX_WORDMANAGER_H__865DFB1E_C04B_4B41_A2B2_257E6B8C6950__INCLUDED_

#include "Word.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

using namespace word;

class CWordManager  
{
public:
	CWordManager();
	~CWordManager();

	// 查询

	size_t WordCount() const;
	size_t GetCurrentPos() const;
	BOOL IsFirst() const;
	BOOL IsLast() const;

	// 操作

	// 浏览单词
	Word * MovePrev();
	Word * MoveNext();
	Word * MoveFirst();
	Word * MoveLast();
	Word * Current();

	//
	Word * QuerySpecial(LPCTSTR pszWord);

	void ReFilterWords();
	void SortWords(DWORD dwWordOrder);

private:
	size_t m_nPos;
	WordVector * m_pAllWords;
	WordVector * m_pUserWords;
	WordVector m_useWords;

	// 空的Word对象
	static NullWord s_nw;

	// 排序函数
	static inline bool WordLess(const Word* pW1, const Word* pW2);
	static inline bool WordGreater(const Word* pW1, const Word* pW2);
	static inline bool AccessTimeLess(const Word* pW1, const Word* pW2);
	static inline bool AccessTimeGreater(const Word* pW1, const Word* pW2);

	// 测试用
	void OutputWordData();
};

#endif // !defined(AFX_WORDMANAGER_H__865DFB1E_C04B_4B41_A2B2_257E6B8C6950__INCLUDED_)
