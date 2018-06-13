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
	if (nLen>999999)
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

CString CUtils::ToString(char * pSrc, const int nSize)
{
#ifdef _UNICODE
	char * pBuf = new char[nSize + 1];
	for (int i = 0; i < nSize; i++)
	{
		*(pBuf + i) = *(pSrc + i);
	}
	pBuf[nSize] = NULL;

	//多字节转成宽字节
	int nLen = ::MultiByteToWideChar(CP_ACP, 0, pBuf, -1, NULL, 0);
	wchar_t * pWBuf = new wchar_t[nLen + 1];
	memset(pWBuf, 0, (nLen + 1) * sizeof(wchar_t));
	::MultiByteToWideChar(CP_ACP, 0, pBuf, -1, (LPWSTR)pWBuf, nLen);

	CString str(pWBuf);
	delete[] pWBuf;
	delete[] pBuf;

	pWBuf = NULL;
	pBuf = NULL;

	return str;
#else
	CString str(pSrc);
	return str;
#endif
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