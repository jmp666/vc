#pragma once
#include <string>
using namespace std;
#import "C:\Windows\System64\WinHttp.dll" no_namespace

class CQZoneItem
{
public:
	IWinHttpRequestPtr m_pHttpReq;
	CString m_strQQ;
	CString m_strPass;
	CString m_loginIFrameURL;
	CString m_loginSig;
	CString m_ptur_Ver;
	CString m_jsVer;
	CString m_strVcode;
	CString m_uHex;
	CString m_ptvfSession;
	CString m_appID;
	//以后会添加更多
	CString m_strSKey;
	CString m_strPtSig;

	CQZoneItem(){
		m_pHttpReq = NULL;
	}
};

UINT LoginQZoneFunc(LPVOID pParam);

#define Get_WinHttp_RspString(IWinHttpRequestPtr_Obj, String_Obj){				\
		_variant_t varRspBody = IWinHttpRequestPtr_Obj->GetResponseBody();		\
		ULONG dataLen = varRspBody.parray->rgsabound[0].cElements;				\
		char *pContentBuffer = (char *)varRspBody.parray->pvData;				\
		String_Obj = pContentBuffer;}

inline CString GetMidStrByLAndR(CString& strSrc, CString strLeft, CString strRight, BOOL bIncludeStart = FALSE, BOOL bIncludeEnd = FALSE);