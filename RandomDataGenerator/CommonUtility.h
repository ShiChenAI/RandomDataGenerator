#pragma once
#include <vector>
#include "ConvertUtility.h"

using namespace std;

class CCommonUtility
{
public:
	CCommonUtility();
	~CCommonUtility();

	static CString SelectFile();

	static void SaveTextFile(const TCHAR* fileName, const vector<CString> &lines, bool bAppendMode = false);

	static bool LoadTextFile(const TCHAR* fileName, vector<CString> &lines);

	static void StringSplit(const CString &text, const TCHAR* separator, vector<CString> &result, bool bAddEmptyItem = true);
	static void StringSplit(const CString &text, vector<CString> &result);
	static void StringSplit(const CString &text, vector<double> &result);

	static long GetRandomNumber(long start, long end);
	static void GetRandomNumber(long start, long end, long count, vector<long> &result);

	static CString GetCurDirectory(HMODULE hInstance = NULL);

	static CString GetParentDirectory(HMODULE hInstance = NULL);

	static CString GetCurrentFullName(HMODULE hInstance = NULL);
};

