// DetailMeaning.cpp: implementation of the CDetailMeaning class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SuperWord.h"
#include "DetailMeaning.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDetailMeaning::CDetailMeaning()
{
}

CDetailMeaning::~CDetailMeaning()
{
	// 关闭详细解释的文件
	if (m_fMeaning.m_hFile != CFile::hFileNull)
		m_fMeaning.Close();
}

CString CDetailMeaning::GetDetailedMeaningFromFile(const CString& strWord)
{
	DWORD dwOff_OffStart = 0x000007b8 / 4;
	DWORD dwOff_OffEnd =   0x00036a14 / 4;
	DWORD dwOff_OffMid;
	DWORD dwWordOffset;
	
	BYTE bWordLen;
	WORD wMeaningLen;
	TCHAR szBuf[256];
	char * szMeaning = helper::public_buffer<16384>();
	int nCompare;
	CString strRet;

	if (m_fMeaning.m_hFile == CFile::hFileNull)
	{
		// 打开详细解释的文件
		CString strFilename = helper::SWPath(helper::IDS(IDSFN_DETAIL_MEANING));
		CFileException e;
		if (!m_fMeaning.Open(strFilename, CFile::modeRead | CFile::shareDenyNone, &e))
		{
//			e.ReportError();
			return _T("");
		}
	}

	CFile &f = m_fMeaning;
	while (dwOff_OffStart <= dwOff_OffEnd)
	{
		dwOff_OffMid = (dwOff_OffStart + dwOff_OffEnd) / 2;
		// dwOff_OffMid *= 4; 
		// 得到这个偏移处的单词
		f.Seek(dwOff_OffMid * 4, CFile::begin);
		f.Read(&dwWordOffset, 4);
		f.Seek(dwWordOffset, CFile::begin);
		f.Read(&bWordLen, 1);
		f.Read(szBuf, bWordLen);
		szBuf[bWordLen] = '\0';

		nCompare = _tcscmp(strWord, szBuf);
		if (nCompare == 0)
		{
			f.Read(&wMeaningLen, 2);
			f.Read(szMeaning, wMeaningLen);
			szMeaning[wMeaningLen] = '\0';
			strRet = szMeaning;
//			strRet.Replace(_T("<BR>"), _T("\n"));
			return strRet;
		}
		else if (nCompare > 0)
			dwOff_OffStart = dwOff_OffMid + 1;
		else 
			dwOff_OffEnd = dwOff_OffMid - 1;
	}

	return _T("");
}

CString CDetailMeaning::GetDetailedMeaning(const CString& strWord)
{
	CString strMeaning;
	CString word = strWord;

	// 尝试用四种不同的单词形式查 ①原样②全小写③全大写④首字大写
	strMeaning = GetDetailedMeaningFromFile(word);	
	if (strMeaning.GetLength()) return strMeaning;
	
	word.MakeLower();
	strMeaning = GetDetailedMeaningFromFile(word);
	if (strMeaning.GetLength()) return strMeaning;
	
	word.MakeUpper();
	strMeaning = GetDetailedMeaningFromFile(word);
	if (strMeaning.GetLength()) return strMeaning;
		
	word.MakeLower();
	word.SetAt(0, static_cast<TCHAR>(toupper(word[0])));
	strMeaning = GetDetailedMeaningFromFile(word);
	if (strMeaning.GetLength()) return strMeaning;

	return strMeaning;
}