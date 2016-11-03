

#include "JsManager.h"


Ctx_Map m_jsCtxMap;

////////////////////////////////////////////////////////////////////////////////

CJsArray::CJsArray(CJsManager *pMgr)
{
	m_jsMgr = pMgr;
	m_arrVal.clear();
}

CJsArray::~CJsArray()
{
}

jsval *CJsArray::getArrayData()
{
	return (m_arrVal.size() > 0) ? &m_arrVal[0]: NULL;
}

unsigned int CJsArray::getArrayLength()
{
	return m_arrVal.size();
}

void CJsArray::pushElement(int obj)
{
	jsval vp = INT_TO_JSVAL(obj);
	m_arrVal.push_back(vp);
}

void CJsArray::pushElement(double obj)
{
	jsval vp = DOUBLE_TO_JSVAL(obj);
	m_arrVal.push_back(vp);
}

bool CJsArray::pushElement(LPCTSTR obj)
{
	if (!obj || _tcslen(obj) <= 0) return false;

	USES_CONVERSION;
	char *strObj = T2A(obj);
	JSString *jsString = JS_NewStringCopyZ(m_jsMgr->m_ctx, strObj);
	jsval vp = STRING_TO_JSVAL(jsString);
	m_arrVal.push_back(vp);

	return true;
}

bool CJsArray::FormatElements(TCHAR *fmt, ...)
{
	TCHAR c, ch;
	va_list ap = NULL;

	va_start(ap, fmt);
	while((c = *fmt))
	{
		switch(c)
		{
		case '%':
			ch = *++fmt;
			switch(ch)
			{
			case 'd':
			case 'x':
				{
					int n = va_arg(ap, int);
					pushElement(n);
					break;
				}
			case 'f':
				{
					double f = va_arg(ap, double);
					pushElement(f);
					break;
				}
			case 'c':
				{
					TCHAR chr = va_arg(ap, TCHAR);
					TCHAR szChar[2] = {chr};
					pushElement(szChar);
					break;
				}
			case 's':
				{
					TCHAR *p = va_arg(ap, TCHAR*);
					pushElement(p);
					break;
				}

			default:return false;
			}
			break;
		default:return false;
		}
		fmt++;
	}
	va_end(ap);

	return true;
}

////////////////////////////////////////////////////////////////////////////////

static JSClass global_class = {
	"global", JSCLASS_GLOBAL_FLAGS,
	JS_PropertyStub, JS_PropertyStub, JS_PropertyStub, JS_StrictPropertyStub,
	JS_EnumerateStub, JS_ResolveStub, JS_ConvertStub, JS_FinalizeStub,
	JSCLASS_NO_OPTIONAL_MEMBERS
};

void report_error(JSContext *cx, const char *message, JSErrorReport *report)
{
	char pBuffer[2048] = {0};
	sprintf_s(pBuffer, 2048, "%s:%u:%s\n",
		report->filename ? report->filename : "<no filename>",
		(unsigned int)report->lineno,
		message);

	Ctx_Map::iterator itor = m_jsCtxMap.find(cx);
	if(itor != m_jsCtxMap.end())
	{
		CJsManager *pJsMgr = itor->second;
		if (pJsMgr)
		{
			pJsMgr->m_lastErrorString = pBuffer;
		}
	}
}

CJsManager::CJsManager(void)
{
	m_rt = NULL;
	m_ctx = NULL;
	m_gObj = NULL;
	m_bInitOk = false;
}


CJsManager::~CJsManager(void)
{
	Ctx_Map::iterator itor;
	itor = m_jsCtxMap.find(m_ctx);
	if(itor != m_jsCtxMap.end())
	{
		m_jsCtxMap.erase(itor);
	}

	if (m_ctx) JS_DestroyContext(m_ctx);
	if (m_rt) JS_DestroyRuntime(m_rt);
	JS_ShutDown();
}

bool CJsManager::initGlobalContext(unsigned int contextSize, unsigned int runTimeSize)
{
	bool bError = false;
	do 
	{
		m_rt = JS_NewRuntime(runTimeSize);
		if (m_rt == NULL){
			bError = true;
			break;
		} 

		m_ctx = JS_NewContext(m_rt, contextSize);
		if (m_ctx == NULL){
			bError = true;
			break;
		}

		JS_SetOptions(m_ctx, JSOPTION_VAROBJFIX);
		JS_SetErrorReporter(m_ctx, report_error);

		m_gObj = JS_NewCompartmentAndGlobalObject(m_ctx, &global_class, NULL);
		if (m_gObj == NULL){
			bError = true;
			break;
		}

		if (!JS_InitStandardClasses(m_ctx, m_gObj)){
			bError = true;
			break;
		}

	} while (0);

	if (false != bError)
	{
		if (m_ctx) JS_DestroyContext(m_ctx);
		if (m_rt) JS_DestroyRuntime(m_rt);
		JS_ShutDown();
		return false;
	}

	m_bInitOk = true;
	m_jsCtxMap[m_ctx] = this;
	return true;
}

bool CJsManager::runScriptString(LPCTSTR scriptString, jsval& retVal)
{
	if (!m_bInitOk || !scriptString || _tcslen(scriptString) <= 0) return false;

	JSBool jsRet = JS_FALSE;

#ifdef UNICODE
	jsRet = JS_EvaluateUCScript(m_ctx, m_gObj, scriptString, _tcslen(scriptString), NULL, 0, &retVal); 
#else
	jsRet = JS_EvaluateScript(m_ctx, m_gObj, scriptString, _tcslen(scriptString), NULL, 0, &retVal); 
#endif

	if (jsRet == JS_FALSE) return false;

	return true;
}

bool CJsManager::runScriptFile(LPCTSTR jsPath, jsval& retVal)
{
	if (!m_bInitOk || !jsPath || _tcslen(jsPath) <= 0) return false;

	USES_CONVERSION;
	char *pszPath = T2A(jsPath);

	JSObject *scriptObj = JS_CompileFile(m_ctx, m_gObj, pszPath);
	if (scriptObj == NULL) return JS_FALSE; 

	JSBool retBool = JS_ExecuteScript(m_ctx, m_gObj, scriptObj, &retVal);
	if (retBool == JS_FALSE) return false;

	return true;
}

bool CJsManager::evalFunction(LPCTSTR funName, CJsArray* paramArray, jsval& retVal)
{
	USES_CONVERSION;
	char *pszFunName = T2A(funName);

	int iParamCount = 0;
	jsval *paramVal = NULL;
	if (paramArray != NULL)
	{
		iParamCount = paramArray->getArrayLength();
		if (iParamCount > 0)
		{
			paramVal = paramArray->getArrayData();
		}
	}

	JSBool jsRet = JS_CallFunctionName(m_ctx, m_gObj, pszFunName, iParamCount, paramVal, &retVal);
	if (!jsRet)return false;

	return true;
}

//×Ö·û´®·Ö¸îº¯Êý
void split(string str, string pattern, vector<string>& outVector)
{
	string::size_type pos, size;
	str += pattern; //À©Õ¹×Ö·û´®ÒÔ·½±ã²Ù×÷
	size = str.size();

	for(string::size_type i = 0; i < size; ++i)
	{
		pos = str.find(pattern, i);
		if(pos < size)
		{
			string s = str.substr(i, pos-i);
			if (s.size() > 0)
			{
				outVector.push_back(s);
			}

			i = pos + pattern.size() - 1;
		}
	}
}

bool CJsManager::evalObjFunction(LPCTSTR objName, LPCTSTR funName, CJsArray* paramArray, jsval& retVal)
{
	if (!objName || _tcslen(objName) <= 0 || !funName || _tcslen(funName) <= 0) return false;

	USES_CONVERSION;
	char *pObjName = T2A(objName);
	char *pFunName = T2A(funName);

	vector<string> outVector;
	split(pObjName, ".", outVector);

	jsval targetObjVal;
	JSObject *pParentObj = m_gObj;
	size_t objsLen = outVector.size();
	for (size_t idx = 0; idx < objsLen; ++idx)
	{
		string objStep = outVector[idx];

		JSBool jsRet = JS_GetProperty(m_ctx, pParentObj, objStep.c_str(), &targetObjVal);
		if (!jsRet)return false;

		pParentObj = JSVAL_TO_OBJECT(targetObjVal);
	}

	int iParamCount = 0;
	jsval *paramVal = NULL;
	if (paramArray != NULL)
	{
		iParamCount = paramArray->getArrayLength();
		if (iParamCount > 0)
		{
			paramVal = paramArray->getArrayData();
		}
	}

	JSBool jsRet = JS_CallFunctionName(m_ctx, pParentObj, pFunName, iParamCount, paramVal, &retVal);
	if (!jsRet) return false;

	return true;
}

bool CJsManager::jsval_to_int(jsval vp, int *outval)
{
	JSBool jsRet = JS_TRUE;
	jsdouble dp;
	jsRet = JS_ValueToNumber(m_ctx, vp, &dp);
	if (!jsRet) return false;

	*outval = (int)dp;
	return true;
}

bool CJsManager::jsval_to_uint(jsval vp, unsigned int *outval)
{
	JSBool jsRet = JS_TRUE;
	jsdouble dp;
	jsRet = JS_ValueToNumber(m_ctx, vp, &dp);
	if (!jsRet) return false;

	*outval = (unsigned int)dp;
	return true;
}

bool CJsManager::jsval_to_ushort(jsval vp, unsigned short *outval)
{
	JSBool jsRet = JS_TRUE;
	jsdouble dp;
	jsRet = JS_ValueToNumber(m_ctx, vp, &dp);
	if (!jsRet) return false;

	*outval = (unsigned short)dp;
	return true;
}

bool CJsManager::jsval_to_cstring_for_delete(jsval vp, char** outval)
{
	JSString *jsString = JS_ValueToString(m_ctx, vp);
	if (!jsString) return false;

	size_t nLen = JS_GetStringEncodingLength(m_ctx, jsString);
	if (nLen <= 0) return false;
	++nLen;

	*outval = new char[nLen];
	memset(*outval, 0, nLen);

	char *pszString = JS_EncodeString(m_ctx, jsString);
	strcpy_s(*outval, nLen, pszString);
	JS_free(m_ctx, pszString);

	return true;
}

bool CJsManager::jsval_to_string(jsval vp, string &outval)
{
	JSString *jsString = JS_ValueToString(m_ctx, vp);
	if (!jsString) return false;

	char *pszString = JS_EncodeString(m_ctx, jsString);\
	outval = pszString;

	return true;
}