#pragma once
class CUtils
{
public:
	CUtils();
	~CUtils();
public:
	static void ToChars(char* pDim, CString strSrc, const int nSize);
	static CString ToString(char* pSrc, const int nSize);
	static CString GetSubString(CString& srcString, int begin, int nSize);
};
