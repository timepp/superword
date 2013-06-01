 // Word.cpp: implementation of the CWord class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SuperWord.h"
#include "Word.h"
#include <vector>
#include <fstream>
#include <algorithm>
#include "LibSrc/greta/regexpr2.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

using namespace word;
//////////////////////////////////////////////////////////////////////
// Word
//////////////////////////////////////////////////////////////////////
CDetailMeaning Word::m_dm;

bool word::word_less(const Word * pW1, const Word * pW2)
{
	return strcmp(pW1->word(), pW2->word()) < 0;
}

bool word::word_greater(const Word * pW1, const Word * pW2)
{
	return strcmp(pW1->word(), pW2->word()) > 0;
}

std::ostream & word::operator << (std::ostream& os, const Word* pW)
{
	BYTE bPhoneticOffset = static_cast<BYTE>(8 + strlen(pW->word()) + 1);
	BYTE bMeaningOffset = static_cast<BYTE>(bPhoneticOffset + strlen(pW->phonetic()) + 1);
	os << bPhoneticOffset;
	os << bMeaningOffset;
	WORD tp = pW->type();
	time_t tm = pW->access_time();
	os.write((char *)&tp, 2);
	os.write((char *)&tm, 4);
	os << pW->word();
	os.seekp(1, std::ios::cur);
	os << pW->phonetic();
	os.seekp(1, std::ios::cur);
	os << pW->meaning();
	// os.seekp(1, ios::cur);
	os.write("", 1);	
	return os;
}


//////////////////////////////////////////////////////////////////////////
// NullWord
//////////////////////////////////////////////////////////////////////////
const char NullWord::s_empty[] = "";

time_t NullWord::access_time() const { return 0; }
WORD NullWord::type() const { return 0; }
const char * NullWord::word() const { return s_empty; }
const char * NullWord::meaning() const { return s_empty; }
const char * NullWord::detail_meaning() const { return s_empty; }
const char * NullWord::phonetic() const { return s_empty; }


//////////////////////////////////////////////////////////////////////////
// FixedWord
//////////////////////////////////////////////////////////////////////////

FixedWord::FixedWord()
{
	m_buf = NULL;
}
FixedWord::FixedWord(const FixedWord& fw)
{
	m_buf = fw.m_buf;
}
FixedWord::~FixedWord()
{
}

const char * FixedWord::word() const
{
	return m_buf + 8;
}
const char * FixedWord::phonetic() const
{
	return m_buf + (BYTE)m_buf[0];
}
const char * FixedWord::meaning() const
{
	return m_buf + (BYTE)m_buf[1];
}

const char * FixedWord::detail_meaning() const
{
    CString str = m_dm.GetDetailedMeaning(word());
    if (str.GetLength() > 0)
    {
        char *s = helper::public_buffer<16384>();
        helper::tstrncpy(s, str, 16383);
        return s;
    }
    else
    {
        return meaning();
    }
}

WORD FixedWord::type() const
{
	return *(WORD *)(m_buf + 2);
}
time_t FixedWord::access_time() const
{
	return *(uint32_t *)(m_buf + 4);
}

bool FixedWord::set_type(WORD tp)
{
	*(WORD *)(m_buf + 2) = tp; 
	return true;
}
bool FixedWord::set_access_time(time_t tm)
{
	*(uint32_t *)(m_buf + 4) = tm; 
	return true;
}

size_t FixedWord::size() const
{
	 return (BYTE)m_buf[1] + strlen(m_buf + (BYTE)m_buf[1]) + 1;
}

// -----------------------------------------------------------------------
// UserWord
UserWord::UserWord()
{
	m_type = 0;
	m_access_time = 0;
}

UserWord::~UserWord(){}

UserWord::UserWord(const UserWord& fw)
{
	m_word = fw.m_word;
	m_meaning = fw.m_meaning;
	m_phonetic = fw.m_phonetic;
	m_type = fw.m_type;
	m_access_time = fw.m_access_time;
}

bool UserWord::operator < (const UserWord& uw)
{
	return m_word < uw.m_word;
}

std::istream& word::operator >> (std::istream& is, UserWord& uw)
{
	BYTE bPhoneticOffset;
	BYTE bMeaningOffset;
	WORD tp;
	DWORD tm;
	char *p;
	char word[256];
	char meaning[2048];
	char phonetic[256];

	std::ios::iostate old_stat = is.exceptions();
	is.exceptions(std::ios::eofbit);
	try
	{
		is.read((char *)&bPhoneticOffset, 1);
		is.read((char *)&bMeaningOffset, 1);
		is.read((char *)&tp, 2);
		is.read((char *)&tm, 4);
		is.read(word, bPhoneticOffset - 8);
		is.read(phonetic, bMeaningOffset - bPhoneticOffset);
		p = meaning;
		do 
		{
			is.read(p, 1);
		} while(*p++ != '\0');
	}
	catch(...)
	{
		is.exceptions(old_stat);
		throw;
	}


	uw.set_word(word);
	uw.set_phonetic(phonetic);
	uw.set_meaning(meaning);
	uw.set_type(tp);
	uw.set_access_time(tm);

	return is;
}


// -----------------------------------------------------------------------
// FixedWordsCreator

// 建立文件映射，初始化单词缓冲区
FixedWordsCreator::FixedWordsCreator() 
	:m_pMappedAddr(NULL), m_arrWord(NULL)
{
	CString strErr;
	DWORD dwFileSize;

	TCHAR szWordfile[MAX_PATH + 16];
	wsprintf(szWordfile, _T("%s\\word.dat"), helper::SWPath());

	HANDLE hWordFile = ::CreateFile(szWordfile, GENERIC_READ | GENERIC_WRITE, 0, 
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hWordFile == INVALID_HANDLE_VALUE)
	{
		strErr.Format(_T("打开内置单词库文件%s失败：\n%s"), 
			szWordfile, helper::ErrnoToString(::GetLastError()));
		AfxMessageBox(strErr);
		return;
	}
	dwFileSize = ::GetFileSize(hWordFile, NULL);
	
	HANDLE hFileMappingObject = ::CreateFileMapping(hWordFile, NULL, PAGE_READWRITE,
		0, 0, _T("SuperWord的文件映射"));
	if (hFileMappingObject == NULL)
	{
		strErr.Format(_T("为单词库文件%s创建内存映射失败：\n%s"), 
			szWordfile, helper::ErrnoToString(::GetLastError()));
		AfxMessageBox(strErr);
		return;
	}
	::CloseHandle(hWordFile);

	m_pMappedAddr = ::MapViewOfFile(hFileMappingObject, 
		FILE_MAP_READ | FILE_MAP_WRITE,	0, 0, 0);
	if (m_pMappedAddr == NULL)
	{
		strErr.Format(_T("为单词库文件%s创建内存映射失败：\n%s"), 
			szWordfile, helper::ErrnoToString(::GetLastError()));
		AfxMessageBox(strErr);
		return;
	}
	::CloseHandle(hFileMappingObject);

	// 构造单词缓冲池
		// 先得到单词总数
	FixedWord fw;
	size_t fixedWordCount = 0;
	size_t i;
	LPBYTE pAddr = (LPBYTE)m_pMappedAddr;
	for (pAddr += 0x100; pAddr < (LPBYTE)m_pMappedAddr + dwFileSize; pAddr += fw.size())
	{
		fw.m_buf = (char *)pAddr;
		if (fw.size() <= 1) break;
		fixedWordCount++;
	}
		// 再分配内存,存入缓冲池
	m_arrWord = new FixedWord[fixedWordCount];
	pAddr = (LPBYTE)m_pMappedAddr + 0x100;
	for (i = 0; i < fixedWordCount; i++)
	{
		m_arrWord[i].m_buf = (char *)pAddr;
		pAddr += m_arrWord[i].size();
	}

	// 构造m_vpWord
	for (i = 0; i < fixedWordCount; i++)
	{
		m_vpWord.push_back(m_arrWord + i);
	}
}

FixedWordsCreator::~FixedWordsCreator()
{
	// 刷新修改
	if (m_pMappedAddr != NULL)
	{
		::FlushViewOfFile(m_pMappedAddr, 0);
		::UnmapViewOfFile(m_pMappedAddr);
	}
	delete [] m_arrWord;
    m_vpWord.clear();
}

FixedWordsCreator * FixedWordsCreator::Instance()
{
	static FixedWordsCreator fwc;
	return &fwc;
}

const WordVector * FixedWordsCreator::GetWords() const
{
	return &m_vpWord;
}

// -----------------------------------------------------------------------
// UserWordsCreator


UserWordsCreator::UserWordsCreator()
{
	// 从自定义单词文件里把所有的用户自定义单词读出来
	std::string user_word_file = helper::SWPath(helper::IDS(IDSFN_USER_WORD));
	std::ifstream is(user_word_file.c_str(), std::ios::in | std::ios::binary);
	if (!is) return;

	DWORD i;
	m_dwOriginalCount = 0;
	UserWord uw;
	while (is.good())
	{
		try
		{
			is >> uw;
		}
		catch (...) 
		{
			break;
		}
		m_dwOriginalCount++;
	}
	m_arrWord = new UserWord[m_dwOriginalCount];
	is.seekg(0);
	for (i = 0; is.good(); i++)
	{
		try
		{
			is >> m_arrWord[i];
		}
		catch (...) 
		{
			break;
		}
	}

	for (i = 0; i < m_dwOriginalCount; i++)
	{
		m_vpWord.push_back(m_arrWord + i);
	}

	std::sort(m_vpWord.begin(), m_vpWord.end(), word_less);
}

UserWordsCreator::~UserWordsCreator()
{
	// 把用户自定义单词写入单词文件
	std::string user_word_file = helper::SWPath(helper::IDS(IDSFN_USER_WORD));
	std::ofstream os(user_word_file.c_str(), std::ios::out | std::ios::binary);

	DWORD i = 0;
	WordVector::const_iterator ci;
	for (ci = m_vpWord.begin(); ci != m_vpWord.end(); ++ci, i++)
	{
		UserWord * pUw = dynamic_cast<UserWord *>(const_cast<Word *>(*ci));
		pUw->set_phonetic("");
		pUw->set_meaning("");
		os << pUw;
		if (i >= m_dwOriginalCount)
			delete pUw;
	}
	delete [] m_arrWord;
}

UserWordsCreator * UserWordsCreator::Instance()
{
	static UserWordsCreator uwc;
	return &uwc;
}

WordVector * UserWordsCreator::GetWords()
{
	return &m_vpWord;
}
