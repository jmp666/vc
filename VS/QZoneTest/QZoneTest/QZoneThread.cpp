
#include "stdafx.h"
#include "QZoneThread.h"
#include "QZoneTestDlg.h"

CQZoneItem *pQZoneItem = NULL;

///////////////// 辅助函数 ///////////////////////////////////////////
CString GetMidStrByLAndR(CString& strSrc, CString strLeft, CString strRight, BOOL bIncludeStart, BOOL bIncludeEnd)
{
	CString strRet;
	int eIdxBegin = strSrc.Find(strLeft);
	if(eIdxBegin != -1)
	{
		if (!bIncludeStart) {
			eIdxBegin += strLeft.GetLength();
		}

		int eIdxEnd = strSrc.Find(strRight, eIdxBegin+1);
		if (eIdxEnd != -1)
		{
			if (!bIncludeEnd) {
				strRet = strSrc.Mid(eIdxBegin, eIdxEnd-eIdxBegin);
			}else{
				eIdxEnd += strRight.GetLength();
				strRet = strSrc.Mid(eIdxBegin, eIdxEnd-eIdxBegin);
			}
		}
	}

	return strRet;
}

string UTF8ToGBK(const string& strUTF8)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, strUTF8.c_str(), -1, NULL, 0);
	wchar_t *wszGBK = new wchar_t[len + 1];
	memset(wszGBK, 0, (len + 1)*sizeof(wchar_t));
	MultiByteToWideChar(CP_UTF8, 0, strUTF8.c_str(), -1, wszGBK, len);

	len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL);
	char *szGBK = new char[len + 1];
	memset(szGBK, 0, len + 1);
	WideCharToMultiByte(CP_ACP,0, wszGBK, -1, szGBK, len, NULL, NULL);
	//strUTF8 = szGBK;
	string strTemp(szGBK);

	delete[]szGBK;
	delete[]wszGBK;

	return strTemp;
}

string GBKToUTF8(const std::string& strGBK)
{
	string strOutUTF8 = "";
	int n = MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, NULL, 0);
	WCHAR* str1 = new WCHAR[n];
	ZeroMemory(str1, n*sizeof(WCHAR));
	MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, str1, n);
	n = WideCharToMultiByte(CP_UTF8, 0, str1, -1, NULL, 0, NULL, NULL);
	char *str2 = new char[n];
	ZeroMemory(str2, n);
	WideCharToMultiByte(CP_UTF8, 0, str1, -1, str2, n, NULL, NULL);
	strOutUTF8 = str2;
	delete [] str1;
	delete[]str2;

	return strOutUTF8;
}

//based on javascript encodeURIComponent()
string char2hex(char dec)
{
	char dig1 = (dec&0xF0)>>4;
	char dig2 = (dec&0x0F);
	if ( 0<= dig1 && dig1<= 9) dig1+=48;    //0,48inascii
	if (10<= dig1 && dig1<=15) dig1+=97-10; //a,97inascii
	if ( 0<= dig2 && dig2<= 9) dig2+=48;
	if (10<= dig2 && dig2<=15) dig2+=97-10;

	string r;
	r.append(&dig1, 1);
	r.append(&dig2, 1);
	return r;
}

string urlencode(const string &c)
{
	string escaped="";
	int max = c.length();
	for(int i = 0; i < max; i++)
	{
		if ((48 <= c[i] && c[i] <= 57) ||//0-9
			(65 <= c[i] && c[i] <= 90) ||//abc...xyz
			(97 <= c[i] && c[i] <= 122) || //ABC...XYZ
			(c[i]=='~' || c[i]=='!' || c[i]=='*' || c[i]=='(' || c[i]==')' || c[i]=='\''))
		{
			escaped.append(&c[i], 1);
		}
		else
		{
			escaped.append("%");
			escaped.append(char2hex(c[i]));//converts char 255 to string "ff"
		}
	}
	return escaped;
}

//////////////////////////////////////////////////////////////////////////////

BOOL getLoginIFrameURL(CQZoneItem* pQZoneItem)
{
	try{
		HRESULT hr = pQZoneItem->m_pHttpReq->Open(_T("GET"), _T("http://i.qq.com/"));
		if(FAILED(hr)) return FALSE;

		pQZoneItem->m_pHttpReq->SetRequestHeader(_T("Accept"), _T("text/html, application/xhtml+xml, */*"));
		pQZoneItem->m_pHttpReq->SetRequestHeader(_T("Accept-Language"), _T("zh-CN"));
		pQZoneItem->m_pHttpReq->SetRequestHeader(_T("User-Agent"), _T("Mozilla/5.0 (Windows NT 6.1; WOW64; Trident/7.0; rv:11.0) like Gecko"));
		pQZoneItem->m_pHttpReq->SetRequestHeader(_T("Host"), _T("i.qq.com"));
		pQZoneItem->m_pHttpReq->SetRequestHeader(_T("Connection"), _T("Keep-Alive"));

		hr = pQZoneItem->m_pHttpReq->Send();
		if(FAILED(hr)) return FALSE;

		_variant_t varRspBody = pQZoneItem->m_pHttpReq->GetResponseBody();
		ULONG dataLen = varRspBody.parray->rgsabound[0].cElements;
		char *pContentBuffer = (char *)varRspBody.parray->pvData;

		string strGBK = UTF8ToGBK(pContentBuffer);
		CString strContent;
		strContent = strGBK.c_str();

		CString loginIFrameURL;

		loginIFrameURL = GetMidStrByLAndR(strContent, _T("<iframe id=\"login_frame\" name=\"login_frame\" height=\"100%\" scrolling=\"no\" width=\"100%\" frameborder=\"0\" src=\""), _T("\""));
		if (loginIFrameURL.GetLength() <= 0) return FALSE;

		loginIFrameURL.Replace(_T("&amp;"), _T("&"));
		pQZoneItem->m_appID = GetMidStrByLAndR(loginIFrameURL, _T("appid="), _T("&"));
		pQZoneItem->m_loginIFrameURL = loginIFrameURL;
	}
	catch (...)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL visitLoginIFrameURL(CQZoneItem* pQZoneItem)
{
	try{
		HRESULT hr = pQZoneItem->m_pHttpReq->Open(_T("GET"), (LPCTSTR)pQZoneItem->m_loginIFrameURL);
		if(FAILED(hr)) return FALSE;

		pQZoneItem->m_pHttpReq->SetRequestHeader(_T("Host"), _T("xui.ptlogin2.qq.com"));
		pQZoneItem->m_pHttpReq->SetRequestHeader(_T("Referer"), _T("http://i.qq.com/"));
		pQZoneItem->m_pHttpReq->SetRequestHeader(_T("Cookie"), _T("_qz_referrer=i.qq.com"));
		pQZoneItem->m_pHttpReq->SetRequestHeader(_T("Accept"), _T("text/html, application/xhtml+xml, */*"));
		pQZoneItem->m_pHttpReq->SetRequestHeader(_T("Accept-Language"), _T("zh-CN"));
		pQZoneItem->m_pHttpReq->SetRequestHeader(_T("User-Agent"), _T("Mozilla/5.0 (Windows NT 6.1; WOW64; Trident/7.0; rv:11.0) like Gecko"));
		pQZoneItem->m_pHttpReq->SetRequestHeader(_T("Connection"), _T("Keep-Alive"));

		hr = pQZoneItem->m_pHttpReq->Send();
		if(FAILED(hr)) return FALSE;

		CString strContent;
		Get_WinHttp_RspString(pQZoneItem->m_pHttpReq, strContent);

		_bstr_t allHeader = pQZoneItem->m_pHttpReq->GetAllResponseHeaders();
		CString strAllHeader = allHeader;

		pQZoneItem->m_loginSig = GetMidStrByLAndR(strAllHeader, _T("pt_login_sig="), _T(";"));
		pQZoneItem->m_ptur_Ver = GetMidStrByLAndR(strContent, _T("pt_ver_md5:\""), _T("\""));
		pQZoneItem->m_jsVer = GetMidStrByLAndR(strContent, _T("ptui_version:encodeURIComponent(\""), _T("\""));

		if (pQZoneItem->m_loginSig.IsEmpty() || pQZoneItem->m_ptur_Ver.IsEmpty() || pQZoneItem->m_jsVer.IsEmpty()) return FALSE;
	}
	catch(...){
		return FALSE;
	}

	return TRUE;
}

#include "JsManager.h"
#pragma comment(lib, "./js185_static/lib/JsMgrStaticLib.lib")

BOOL visitVCodeURL(CQZoneItem* pQZoneItem)
{
	try{
		srand((unsigned)time(NULL));
		double randNum = (double)rand()/RAND_MAX;
		CString strNum;
		strNum.Format(_T("%.16lf"), randNum);

		CString strVCodeUrl;
		strVCodeUrl.Format(_T("http://check.ptlogin2.qq.com/check?regmaster=&pt_tea=1&uin=%s&appid=%s&js_ver=%s&js_type=1&login_sig=%s&u1=http%%3A%%2F%%2Fqzs.qq.com%%2Fqzone%%2Fv5%%2Floginsucc.html%%3Fpara%%3Dizone&r=%s"), pQZoneItem->m_strQQ, pQZoneItem->m_appID, pQZoneItem->m_jsVer, pQZoneItem->m_loginSig, strNum);

		HRESULT hr = pQZoneItem->m_pHttpReq->Open(_T("GET"), (LPCTSTR)strVCodeUrl);
		if(FAILED(hr)) return FALSE;

		LPCTSTR js_pgv_pvid = _T("(Math.round(Math.random() * 2147483647) * (new Date().getUTCMilliseconds())) % 10000000000;");
		LPCTSTR js_pgv_info = _T("(Math.round(Math.random() * 2147483647) * (new Date().getUTCMilliseconds())) % 10000000000;");

		CJsManager jsMgr;
		jsMgr.initGlobalContext();

		jsval jsVal;
		BOOL bRet = jsMgr.runScriptString(js_pgv_pvid, jsVal);
		if(!bRet) return FALSE;

		string pgv_pvid, pgv_info, pgv_cookie;
		jsMgr.jsval_to_string(jsVal, pgv_pvid);

		bRet = jsMgr.runScriptString(js_pgv_info, jsVal);
		if(!bRet) return FALSE;
		jsMgr.jsval_to_string(jsVal, pgv_info);

		pgv_cookie = "pgv_pvid=" + pgv_pvid + "; pgv_info=ssid=s" + pgv_info + "; _qz_referrer=i.qq.com";

		pQZoneItem->m_pHttpReq->SetRequestHeader(_T("Host"), _T("check.ptlogin2.qq.com"));
		pQZoneItem->m_pHttpReq->SetRequestHeader(_T("Referer"), (LPCTSTR)pQZoneItem->m_loginIFrameURL);
		pQZoneItem->m_pHttpReq->SetRequestHeader(_T("Accept"), _T("application/javascript, */*;q=0.8"));
		pQZoneItem->m_pHttpReq->SetRequestHeader(_T("Accept-Language"), _T("zh-CN"));
		pQZoneItem->m_pHttpReq->SetRequestHeader(_T("User-Agent"), _T("Mozilla/5.0 (Windows NT 6.1; WOW64; Trident/7.0; rv:11.0) like Gecko"));
		pQZoneItem->m_pHttpReq->SetRequestHeader(_T("Connection"), _T("Keep-Alive"));
		pQZoneItem->m_pHttpReq->SetRequestHeader(_T("Cookie"), pgv_cookie.c_str());

		hr = pQZoneItem->m_pHttpReq->Send();
		if(FAILED(hr)) return FALSE;

		long statusCode = pQZoneItem->m_pHttpReq->GetStatus();
		CString strContent;
		Get_WinHttp_RspString(pQZoneItem->m_pHttpReq, strContent);

		_bstr_t allHeader = pQZoneItem->m_pHttpReq->GetAllResponseHeaders();
		CString strAllHeader = allHeader;

		pQZoneItem->m_strVcode = GetMidStrByLAndR(strContent, _T(",\'"), _T("\',"));
		pQZoneItem->m_uHex = GetMidStrByLAndR(strContent, _T("\\x"), _T("\'"), TRUE);
		pQZoneItem->m_ptvfSession = GetMidStrByLAndR(strAllHeader, _T("ptvfsession="), _T(";"));
	}
	catch(...){
		return FALSE;
	}

	return TRUE;
}

#include <sys/timeb.h>
BOOL getScriptQQPass(CString& strQPass, LPCTSTR uin, LPCTSTR vcode)
{
	CJsManager jsMgr;
	jsMgr.initGlobalContext();

	jsval jsVal;
	jsMgr.runScriptFile(_T("C:\\Users\\Syc\\Desktop\\QQEncryption.js"), jsVal);

	CJsArray arrParam(&jsMgr);

	arrParam.pushElement(strQPass);
	arrParam.pushElement(uin);
	arrParam.pushElement(vcode);
	BOOL bRet = jsMgr.evalFunction(_T("getQQPassString"), &arrParam, jsVal);
	if(!bRet) return FALSE;

	string strText;
	jsMgr.jsval_to_string(jsVal, strText);

	strQPass.Empty();
	strQPass = strText.c_str();

	return TRUE;
}

BOOL loginQZone(CQZoneItem* pQZoneItem)
{
	try{
		struct _timeb timebuuef;
		_ftime_s(&timebuuef);
		__int64 iwMilliseconds = timebuuef.time*1000 + timebuuef.millitm;

		getScriptQQPass(pQZoneItem->m_strPass, pQZoneItem->m_strQQ, pQZoneItem->m_strVcode);

		CString submitUrl;
		submitUrl.Format(_T("http://ptlogin2.qq.com/login?u=%s&verifycode=%s&pt_vcode_v1=0&pt_verifysession_v1=%s&p=%s&pt_randsalt=0&u1=http%%3A%%2F%%2Fqzs.qq.com%%2Fqzone%%2Fv5%%2Floginsucc.html%%3Fpara%%3Dizone&ptredirect=0&h=1&t=1&g=1&from_ui=1&ptlang=2052&action=2-%d-%I64d&js_ver=%s&js_type=1&login_sig=%s&pt_uistyle=32&aid=%s&daid=5&pt_qzone_sig=1&"), pQZoneItem->m_strQQ, pQZoneItem->m_strVcode, pQZoneItem->m_ptvfSession, pQZoneItem->m_strPass, pQZoneItem->m_strPass.GetLength()*2, iwMilliseconds, pQZoneItem->m_jsVer, pQZoneItem->m_loginSig, pQZoneItem->m_appID);

		HRESULT hr = pQZoneItem->m_pHttpReq->Open(_T("GET"), (LPCTSTR)submitUrl);
		if(FAILED(hr)) return FALSE;

		pQZoneItem->m_pHttpReq->SetRequestHeader(_T("Host"), _T("ptlogin2.qq.com"));
		pQZoneItem->m_pHttpReq->SetRequestHeader(_T("Referer"), (LPCTSTR)pQZoneItem->m_loginIFrameURL);
		pQZoneItem->m_pHttpReq->SetRequestHeader(_T("Accept"), _T("application/javascript, */*;q=0.8"));
		pQZoneItem->m_pHttpReq->SetRequestHeader(_T("Accept-Language"), _T("zh-CN"));
		pQZoneItem->m_pHttpReq->SetRequestHeader(_T("User-Agent"), _T("Mozilla/5.0 (Windows NT 6.1; WOW64; Trident/7.0; rv:11.0) like Gecko"));
		pQZoneItem->m_pHttpReq->SetRequestHeader(_T("Connection"), _T("Keep-Alive"));

		CString newCookie;
		newCookie.Format(_T("ptui_loginuin=%s"), pQZoneItem->m_strQQ);
		pQZoneItem->m_pHttpReq->SetRequestHeader(_T("Cookie"), (LPCTSTR)newCookie);

		hr = pQZoneItem->m_pHttpReq->Send();
		if(FAILED(hr)) return FALSE;

		_variant_t varRspBody = pQZoneItem->m_pHttpReq->GetResponseBody();
		ULONG dataLen = varRspBody.parray->rgsabound[0].cElements;
		char *pContentBuffer = (char *)varRspBody.parray->pvData;
		////////////////////////////////////////////////////
		_bstr_t sbAllHeaders = pQZoneItem->m_pHttpReq->GetAllResponseHeaders();
		CString strAllHeader;
		strAllHeader = (LPCTSTR)sbAllHeaders;

		pQZoneItem->m_strSKey = GetMidStrByLAndR(strAllHeader, _T("skey="), _T(";"));
		if(pQZoneItem->m_strSKey.IsEmpty()) return FALSE;
		////////////////////////////////////////////////////

		string strGBK = UTF8ToGBK(pContentBuffer);
		CString strContent;
		strContent = strGBK.c_str();

		CString strLoginSucc;
		strLoginSucc = GetMidStrByLAndR(strContent, _T("http://"), _T("\',"), TRUE);
		pQZoneItem->m_strPtSig = GetMidStrByLAndR(strContent, _T("ptsig="), _T("\',"));

		/////////////////////////////////////////////////////////////////////
		//登陆的后续请求，只是为了获取Cookie
		//http://user.qzone.qq.com/3131593667?ptsig=UGI1mN*0hQcOXoouKD3BiFbblWJal4teMjTU72PHotc_

		CString qzoneUrl;
		qzoneUrl.Format(_T("http://user.qzone.qq.com/%s?ptsig=%s"), pQZoneItem->m_strQQ, pQZoneItem->m_strPtSig);

		hr = pQZoneItem->m_pHttpReq->Open(_T("GET"), (LPCTSTR)qzoneUrl);
		if(FAILED(hr)) return FALSE;

		pQZoneItem->m_pHttpReq->SetRequestHeader(_T("Host"), _T("user.qzone.qq.com"));
		pQZoneItem->m_pHttpReq->SetRequestHeader(_T("Referer"), (LPCTSTR)strLoginSucc);
		pQZoneItem->m_pHttpReq->SetRequestHeader(_T("Accept"), _T("text/html, application/xhtml+xml, */*"));
		pQZoneItem->m_pHttpReq->SetRequestHeader(_T("Accept-Language"), _T("zh-CN"));
		pQZoneItem->m_pHttpReq->SetRequestHeader(_T("User-Agent"), _T("Mozilla/5.0 (Windows NT 6.1; WOW64; Trident/7.0; rv:11.0) like Gecko"));
		pQZoneItem->m_pHttpReq->SetRequestHeader(_T("Connection"), _T("Keep-Alive"));

		hr = pQZoneItem->m_pHttpReq->Send();
		if(FAILED(hr)) return FALSE;

	}
	catch(...){
		return FALSE;
	}

	return TRUE;
}

BOOL PublishTextSS(CQZoneItem* pQZoneItem, CString strText)
{
	if (strText.IsEmpty()) return FALSE;

	try{
		CJsManager jsMgr;
		jsMgr.initGlobalContext();

		jsval jsVal;
		bool ret = jsMgr.runScriptFile(_T("C:\\Users\\Syc\\Desktop\\QQEncryption.js"), jsVal);
		if (!ret) return FALSE;

		CJsArray arrParam(&jsMgr);
		arrParam.pushElement(pQZoneItem->m_strSKey);
		BOOL bRet = jsMgr.evalFunction(_T("genHash"), &arrParam, jsVal);
		if(!bRet) return FALSE;

		string sgtk;
		jsMgr.jsval_to_string(jsVal, sgtk);
		CString strGTK;
		strGTK = sgtk.c_str();

		CString strPubTextUrl, strRealUrl, refererUrl;
		strPubTextUrl.Format(_T("http://user.qzone.qq.com/q/taotao/cgi-bin/emotion_cgi_publish_v6?g_tk=%s"), strGTK);
		strRealUrl.Format(_T("http://taotao.qq.com/cgi-bin/emotion_cgi_publish_v6?g_tk=%s"), strGTK);
		refererUrl.Format(_T("http://user.qzone.qq.com/8260671?ptsig=%s"), pQZoneItem->m_strPtSig);

		HRESULT hr = pQZoneItem->m_pHttpReq->Open(_T("POST"), (LPCTSTR)strPubTextUrl);
		if(FAILED(hr)) return FALSE;

		pQZoneItem->m_pHttpReq->SetRequestHeader(_T("Host"), _T("user.qzone.qq.com"));
		pQZoneItem->m_pHttpReq->SetRequestHeader(_T("Referer"), (LPCTSTR)refererUrl);
		pQZoneItem->m_pHttpReq->SetRequestHeader(_T("Accept"), _T("*/*"));
		pQZoneItem->m_pHttpReq->SetRequestHeader(_T("Accept-Language"), _T("zh-CN"));
		pQZoneItem->m_pHttpReq->SetRequestHeader(_T("User-Agent"), _T("Mozilla/5.0 (Windows NT 6.1; WOW64; Trident/7.0; rv:11.0) like Gecko"));
		pQZoneItem->m_pHttpReq->SetRequestHeader(_T("Connection"), _T("Keep-Alive"));
		pQZoneItem->m_pHttpReq->SetRequestHeader(_T("Content-Type"), _T("application/x-www-form-urlencoded;charset=utf-8"));
		pQZoneItem->m_pHttpReq->SetRequestHeader(_T("X-Real-Url"), (LPCTSTR)strRealUrl);
		pQZoneItem->m_pHttpReq->SetRequestHeader(_T("Pragma"), _T("no-cache"));

		////////////// 获取编码的文本内容 ///////////////////

		USES_CONVERSION;
		string origText = T2A(strText);
		string strUTF8 = GBKToUTF8(origText);
		string text = urlencode(strUTF8);

		CString strCon;
		strCon = text.c_str();
		///////////////////////////////////////////////////
		CString strBody, strQZRefer;
		strQZRefer.Format(_T("http%%3A%%2F%%2Fuser.qzone.qq.com%%2F%s%%3Fptsig%%3D%s"), pQZoneItem->m_strQQ, pQZoneItem->m_strPtSig);
		strBody.Format(_T("syn_tweet_verson=1&paramstr=1&pic_template=&richtype=&richval=&special_url=&subrichtype=&who=1&con=%s&feedversion=1&ver=1&ugc_right=64&to_tweet=0&to_sign=0&hostuin=%s&code_version=1&format=fs&qzreferrer=%s"), strCon, pQZoneItem->m_strQQ, strQZRefer);

		hr = pQZoneItem->m_pHttpReq->Send((LPCTSTR)strBody);
		if(FAILED(hr)) return FALSE;

		CString strContent;
		long statusCode = pQZoneItem->m_pHttpReq->GetStatus();
		Get_WinHttp_RspString(pQZoneItem->m_pHttpReq, strContent);
	}
	catch(...){
		return FALSE;
	}

	return TRUE;
}

UINT LoginQZoneFunc(LPVOID pParam)
{
	CQZoneTestDlg *pQZoneTestDlg = (CQZoneTestDlg*)pParam;
	if (!pQZoneTestDlg) return FALSE;

	CoInitialize(NULL);

	try{
		HRESULT hr = S_FALSE;
		pQZoneItem = new CQZoneItem();
		if (!pQZoneItem->m_pHttpReq) {
			hr = pQZoneItem->m_pHttpReq.CreateInstance(__uuidof(WinHttpRequest));
			if(FAILED(hr)) return FALSE;
		}

		//HTTPREQUEST_PROXY_SETTING HTTPREQUEST_PROXYSETTING_DEFAULT   = 0;
		//HTTPREQUEST_PROXY_SETTING HTTPREQUEST_PROXYSETTING_PRECONFIG = 0;
		//HTTPREQUEST_PROXY_SETTING HTTPREQUEST_PROXYSETTING_DIRECT    = 1;
		//HTTPREQUEST_PROXY_SETTING HTTPREQUEST_PROXYSETTING_PROXY     = 2;

		//hr = pQZoneItem->m_pHttpReq->SetProxy(HTTPREQUEST_PROXYSETTING_PROXY, _T("127.0.0.1:8888"));

		pQZoneItem->m_strQQ = pQZoneTestDlg->m_strQQ;
		pQZoneItem->m_strPass = pQZoneTestDlg->m_strPass;

		BOOL bRet = FALSE;
		bRet = getLoginIFrameURL(pQZoneItem);
		if (!bRet) return FALSE;

		bRet = visitLoginIFrameURL(pQZoneItem);
		if (!bRet) return FALSE;

		bRet = visitVCodeURL(pQZoneItem);
		if (!bRet) return FALSE;

		bRet = loginQZone(pQZoneItem);
		if (!bRet) return FALSE;

		pQZoneTestDlg->SetStateInfo(_T("登陆成功，可以发表说说喽！"));
		pQZoneTestDlg->GetDlgItem(IDC_EDIT_TEXT_PUBLIC)->EnableWindow(TRUE);
		pQZoneTestDlg->GetDlgItem(IDC_EDIT_IMG_PATH)->EnableWindow(TRUE);
		pQZoneTestDlg->GetDlgItem(IDC_BTN_BROWSE)->EnableWindow(TRUE);
		pQZoneTestDlg->GetDlgItem(IDC_BTN_PUBLIC)->EnableWindow(TRUE);
	}
	catch(...){
		return FALSE;
	}

	return TRUE;
}