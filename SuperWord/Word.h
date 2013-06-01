 // Word.h: interface for the CWord class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WORD_H__F479280B_4102_4280_8D54_469EDEE875F6__INCLUDED_)
#define AFX_WORD_H__F479280B_4102_4280_8D54_469EDEE875F6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include "DetailMeaning.h"

#ifndef interface
#define interface struct
#endif

typedef unsigned int uint32_t;

namespace word
{

// -----------------------------------------------------------------------
// ���ʽӿ�
interface Word
{
public:
	virtual ~Word(){}

	virtual const char * word() const = 0;
	virtual const char * phonetic() const = 0;
	virtual const char * meaning() const = 0;
    virtual const char * detail_meaning() const = 0;
	virtual WORD type() const = 0;
	virtual time_t access_time() const = 0;

	virtual bool set_word(const char * w) = 0;
	virtual bool set_phonetic(const char * p) = 0;
	virtual bool set_meaning(const char * m) = 0;
	virtual bool set_type(WORD tp) = 0;
	virtual bool set_access_time(time_t tm) = 0;

protected:
	static CDetailMeaning m_dm;
};

typedef std::vector<Word *> WordVector;
std::ostream & operator << (std::ostream& os, const Word* pW);
bool word_less(const Word * pW1, const Word * pW2);
bool word_greater(const Word * pW1, const Word * pW2);

// -----------------------------------------------------------------------
// NullWord, ʵ��һ���߼���Ϊ�յĵ���
class NullWord : public Word
{
public:
	virtual const char * word() const;
	virtual const char * phonetic() const;
	virtual const char * meaning() const;
    virtual const char * detail_meaning() const;
	virtual WORD type() const;
	virtual time_t access_time() const;

    virtual bool set_word(const char * w) { return false; };
    virtual bool set_phonetic(const char * p) { return false; };
    virtual bool set_meaning(const char * m) { return false; };
    virtual bool set_type(WORD tp) { return false; };
    virtual bool set_access_time(time_t tm) { return false; };

private:
	static const char s_empty[];
};



// -----------------------------------------------------------------------
// FixedWord, �ڲ�ֻ�洢һ����ŵ������ݵĻ����������������ɴ˵�ַת������
class FixedWord : public Word
{
	friend class FixedWordsCreator;

public:
	FixedWord(const FixedWord& fw);
	~FixedWord();

	virtual const char * word() const;
	virtual const char * phonetic() const;
	virtual const char * meaning() const;
    virtual const char * detail_meaning() const;
	virtual WORD type() const;
	virtual time_t access_time() const;

    virtual bool set_word(const char * w) { return false; }
    virtual bool set_phonetic(const char * p){ return false; }
    virtual bool set_meaning(const char * m){ return false; }
	virtual bool set_type(WORD tp);
	virtual bool set_access_time(time_t tm);
private:
	// ��ŵ��ʵĻ�����
	char * m_buf;

	FixedWord();
	// ���ص���ռ�õĻ�������С
	inline size_t size() const;
};

// -----------------------------------------------------------------------
// UserWord
class UserWord : public Word
{
public:
	UserWord();
	UserWord(const UserWord& fw);
	~UserWord();

	virtual inline const char * word() const { return m_word.c_str(); }
	virtual inline const char * phonetic() const { return m_phonetic.c_str(); }
	virtual inline const char * meaning() const { return m_meaning.c_str(); }
    virtual inline const char * detail_meaning() const { return meaning(); }
	virtual inline WORD type() const { return m_type; }
	virtual inline time_t access_time() const { return m_access_time; }

	virtual inline bool set_type(WORD tp) { m_type = tp; return true; }
	virtual inline bool set_access_time(time_t tm) { m_access_time = tm; return true; }
	virtual bool set_word(const char * w) { m_word = w; return true; }
	virtual bool set_phonetic(const char * p) { m_phonetic = p; return true; }
	virtual bool set_meaning(const char * m) { m_meaning = m; return true; }
public:
	bool operator < (const UserWord& uw);
private:
	std::string m_word;
	std::string m_meaning;
	std::string m_phonetic;
	WORD m_type;
	time_t m_access_time;
};

std::istream& operator >> (std::istream& is, UserWord& uw);

// -----------------------------------------------------------------------
// FixedWordCreator��װ�˼��غ��ͷ����õ��ʵĲ�������singletonģʽʵ��
// ͨ���ڴ�ӳ���ļ��ķ������ѵ��ʿ�ֱ�Ӽ��ص����̵ĵ�ַ�ռ�
// ʹ�÷���
#if 0
	vector<Word *> vw;
	FixedWordsCreator *pCreator = FixedWordsCreator::Instance();
	pCreator->GetWords(vw);
	// ����vw�����������й��е���
#endif

class WordsCreator
{

};

class FixedWordsCreator : public WordsCreator
{
public:
	~FixedWordsCreator();

	static FixedWordsCreator* Instance();
	virtual const WordVector * GetWords() const;

private:
	FixedWordsCreator();

	LPVOID m_pMappedAddr;			// �����ļ�ӳ��Ļ���ַ
	FixedWord *m_arrWord;			// ������С����ʡ�������
	WordVector m_vpWord;			// ���ظ����ġ�����ָ�롱
};

class UserWordsCreator : public WordsCreator
{
public:
	~UserWordsCreator();

	static UserWordsCreator* Instance();
	virtual WordVector * GetWords();

private:
	UserWordsCreator();

	DWORD m_dwOriginalCount;		// ����userword.dat�еĵ��ʸ���
	UserWord *m_arrWord;			// ������С����ʽṹ����vector
	WordVector m_vpWord;			// ���ظ����ġ�����ָ�롱
};

};

#endif // !defined(AFX_WORD_H__F479280B_4102_4280_8D54_469EDEE875F6__INCLUDED_)
