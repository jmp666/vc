
#pragma once
#include <tchar.h>
#include <atlconv.h>

#include <string>
#include <map>
#include <vector>
using namespace std;

#define XP_WIN
#define STATIC_JS_API
#pragma comment(lib, "Winmm.lib")

#include <jsapi.h>

#define JSMGR_DLL_API

class CJsManager;
class JSMGR_DLL_API CJsArray
{
public:
	CJsArray(CJsManager *pMgr);
	~CJsArray(void);

public:
	jsval *getArrayData();
	unsigned int getArrayLength();
	void pushElement(int obj);
	void pushElement(double obj);
	bool pushElement(LPCTSTR obj);
	bool FormatElements(TCHAR *fmt, ...);

private:
	vector <jsval> m_arrVal;
	CJsManager *m_jsMgr;
};

////////////////////////////////////////////////////////////////////////////////

class JSMGR_DLL_API CJsManager
{
public:
	CJsManager(void);
	~CJsManager(void);

public:
	bool initGlobalContext(unsigned int contextSize = 8L * 1024, unsigned int runTimeSize = 8L * 1024L * 1024L);

	bool runScriptString(LPCTSTR scriptString, jsval& retVal);
	bool runScriptFile(LPCTSTR jsPath, jsval& retVal);

	bool evalFunction(LPCTSTR funName, CJsArray* paramArray, jsval& retVal);
	bool evalObjFunction(LPCTSTR objName, LPCTSTR funName, CJsArray* paramArray, jsval& retVal);

	bool jsval_to_int(jsval vp, int* outval);
	bool jsval_to_uint(jsval vp, unsigned int* outval);
	bool jsval_to_ushort(jsval vp, unsigned short* outval);
	bool jsval_to_cstring_for_delete(jsval vp, char** outval);
	bool jsval_to_string(jsval vp, string &outval);

public:
	JSRuntime *m_rt;
	JSContext *m_ctx;
	JSObject *m_gObj;
	string m_lastErrorString;

	bool m_bInitOk;
};

typedef map<JSContext*,CJsManager*> Ctx_Map;