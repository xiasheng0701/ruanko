#include "stdafx.h"
#include "CUtils.h"


CUtils::CUtils()
{
}


CUtils::~CUtils()
{
}

void CUtils::ToChars(char * pDim, CString strSrc, const int nSize)
{
#ifdef _UNICODE
	wchar_t* pSrc = strSrc.GetBuffer(strSrc.GetLength());
	int nLen = ::WideCharToMultiByte(CP_ACP, 0, pSrc, -1, NULL, 0, NULL, NULL);
	char* pBuf = new char(nLen);
	::WideCharToMultiByte(CP_ACP, 0, pSrc, -1, pBuf, nLen, NULL, NULL);
	if (nLen>99999)
	{
		TRACE(" CUtils::ToChar():数组越界");
		return;
	}
	for (int i = 0; i < nLen; i++)
	{
		*(pDim + i) = *(pBuf + i);
	}
	strSrc.ReleaseBuffer();

//	delete[] pBuf;
//	pBuf = NULL;
#else
	pDim = strSrc.GetBuffer(strSrc.GetLength());
	strSrc.ReleaseBuffer();
#endif // _UNICODE

}

CString CUtils::GetSubString(CString & srcString, int begin, int nSize)
{
	CString dstString = _T("");

	if (srcString.IsEmpty())
	{
		return dstString;
	}
	dstString = srcString.Left(nSize);
	srcString.Delete(begin, nSize + 3);
	return dstString;
}
