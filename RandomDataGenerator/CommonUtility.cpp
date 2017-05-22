#include "stdafx.h"
#include "CommonUtility.h"


CCommonUtility::CCommonUtility()
{
}


CCommonUtility::~CCommonUtility()
{
}

CString CCommonUtility::SelectFile()
{
	CString strFile = _T("");

	CFileDialog dlgFile(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T("Text Files (*.txt)|*.txt|All Files (*.*)|*.*||"), NULL);

	if (dlgFile.DoModal())
	{
		strFile = dlgFile.GetPathName();
	}

	return strFile;
}

void CCommonUtility::SaveTextFile(const TCHAR * fileName, const vector<CString>& lines, bool bAppendMode)
{
	if (bAppendMode)
	{
		CStdioFile file(fileName, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::typeText);
		file.SeekToEnd();
		file.WriteString(TEXT("\n"));
		for (int i = 0; i < lines.size(); i++)
		{
			file.WriteString(lines[i]);
			if (i < lines.size() - 1)
			{
				file.WriteString(TEXT("\n"));
			}
		}
		file.Close();
	}
	else
	{
		CStdioFile file(fileName, CFile::modeCreate | CFile::modeWrite | CFile::typeText);
		for (int i = 0; i < lines.size(); i++)
		{
			file.WriteString(lines[i]);
			if (i < lines.size() - 1)
			{
				file.WriteString(TEXT("\n"));
			}
		}
		file.Close();
	}
}

bool CCommonUtility::LoadTextFile(const TCHAR * fileName, vector<CString>& lines)
{
	lines.clear();
	if (_taccess(fileName, 0) != -1)
	{
		CStdioFile file(fileName, CFile::modeRead | CFile::typeText);
		CString strLine;
		while (file.ReadString(strLine))
		{
			lines.push_back(strLine);
		}
		return true;
	}
	else
	{
		return false;
	}
}

void CCommonUtility::StringSplit(const CString & text, const TCHAR * separator, vector<CString>& result, bool bAddEmptyItem)
{
	int prev = 0, current = 0;
	CString strCopyText = text;
	strCopyText.TrimRight(TEXT(" "));
	if (strCopyText.Find(separator, 0) < 0)
	{
		if (strCopyText.GetLength() > 0)
		{
			result.push_back(strCopyText);
		}
		return;
	}

	int length = strCopyText.GetLength();
	bool bExit = false;
	while (1)
	{
		current = strCopyText.Find(separator, prev);
		if (current == -1)
		{
			current = length;
			bExit = true;
		}
		CString item = strCopyText.Mid(prev, current - prev);
		if (bAddEmptyItem || item.GetLength() > 0)
		{
			result.push_back(item);
		}

		if (bExit)
		{
			break;
		}
		prev = current + _tcslen(separator);
	}
}

void CCommonUtility::StringSplit(const CString & text, vector<CString>& result)
{
	int prev = 0, current = 0;
	CString strCopyText = text;
	CString separator = TEXT(" ");
	if (strCopyText.Find(separator, 0) < 0)
	{
		if (strCopyText.GetLength() > 0)
		{
			result.push_back(strCopyText);
		}
		return;
	}

	int length = strCopyText.GetLength();
	bool bExit = false;
	while (1)
	{
		current = strCopyText.Find(separator, prev);
		if (current == -1)
		{
			current = length;
			bExit = true;
		}
		CString item = strCopyText.Mid(prev, current - prev);
		if (item.GetLength() > 0)
		{
			result.push_back(item);
		}

		if (bExit)
		{
			break;
		}
		prev = current + _tcslen(separator);
	}
}

void CCommonUtility::StringSplit(const CString & text, vector<double>& result)
{
	int prev = 0, current = 0;
	CString strCopyText = text;
	CString separator = TEXT(" ");
	if (strCopyText.Find(separator, 0) < 0)
	{
		if (strCopyText.GetLength() > 0)
		{
			result.push_back(CConvertUtility::ToDouble(strCopyText));
		}
		return;
	}

	int length = strCopyText.GetLength();
	bool bExit = false;
	while (1)
	{
		current = strCopyText.Find(separator, prev);
		if (current == -1)
		{
			current = length;
			bExit = true;
		}
		CString item = strCopyText.Mid(prev, current - prev);
		if (item.GetLength() > 0)
		{
			result.push_back(CConvertUtility::ToDouble(item));
		}

		if (bExit)
		{
			break;
		}
		prev = current + _tcslen(separator);
	}
}

long CCommonUtility::GetRandomNumber(long start, long end)
{
	return (rand() % (end - start + 1)) + start;
}

void CCommonUtility::GetRandomNumber(long start, long end, long count, vector<long>& result)
{
	result.clear();
	for (int i = 0; i < count; i++)
	{
		while (1)
		{
			long rand = GetRandomNumber(start, end);
			vector<long>::iterator iter;
			iter = find(result.begin(), result.end(), rand);
			if (iter == result.end())
			{
				result.push_back(rand);
				break;
			}
		}
	}
}

CString CCommonUtility::GetCurDirectory(HMODULE hInstance)
{
	TCHAR szPath[256];
	GetModuleFileName(hInstance, szPath, sizeof(szPath));
	*(_tcsrchr(szPath, '\\')) = 0;

	CString strResult = szPath;
	//strResult += "\\";

	return strResult;
}

CString CCommonUtility::GetParentDirectory(HMODULE hInstance)
{
	TCHAR szPath[256];
	GetModuleFileName(hInstance, szPath, sizeof(szPath));
	//*(strrchr(szPath, '\\')) = 0;

	CString strResult = szPath;

	return strResult;
}

CString CCommonUtility::GetCurrentFullName(HMODULE hInstance)
{
	TCHAR szPath[256];
	GetModuleFileName(hInstance, szPath, sizeof(szPath));
	*(_tcsrchr(szPath, '\\')) = 0;
	*(_tcsrchr(szPath, '\\')) = 0;

	CString strResult = szPath;

	return strResult;
}