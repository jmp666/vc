// 遍历进程.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<Windows.h>
#include<tlhelp32.h>
#include<Psapi.h>
#include<wchar.h>
#pragma comment(lib,"Psapi.lib")
BOOL getProcessAddr(DWORD dwPID, DWORD& baseAddr, DWORD& baseSize, TCHAR* module)
{
	HANDLE hModuleSnap = INVALID_HANDLE_VALUE;
	MODULEENTRY32 me32;

	// 在目标进程中获取所有进程的snapshot
	hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPALL, dwPID);
	if (hModuleSnap == INVALID_HANDLE_VALUE)
	{
		HANDLE hProcess = NULL;
		hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPID);
		//得到该进程的全路径
		TCHAR procPath[_MAX_PATH] = { 0 };
		GetModuleFileNameEx(hProcess, NULL, procPath, _MAX_PATH);
		//OutputDebugStringF("进程ID为：%d\n",dwPID);
		return(FALSE);
	}

	// 设置MODULEENTRY32数据结构大小字段
	me32.dwSize = sizeof(MODULEENTRY32);

	//检索第一个模块的信息，不成功则返回
	if (!Module32First(hModuleSnap, &me32))
	{
		//wprintf(L"%s\n", me32.szExePath);
		//OutputDebugStringF("进程ID为：%d\n",dwPID); // 显示调用失败
		CloseHandle(hModuleSnap);    // 清除句柄对象
		return(FALSE);
	}

	// 从me32中得到基址
	// 别忘了最后清除模块句柄对象
	wcscpy_s(module,MAX_MODULE_NAME32 + 1,me32.szModule);
	baseAddr = (DWORD)me32.modBaseAddr;
	baseSize = (DWORD)me32.modBaseSize;
	CloseHandle(hModuleSnap);
	return(TRUE);
};
int main()
{
	DWORD arr[1024] = { 0 };
	DWORD size, length, base = 0, basize = 0;
	unsigned int i;
	EnumProcesses(arr, sizeof(arr), &size);
	length = size / sizeof(DWORD);
	TCHAR szmodule[MAX_MODULE_NAME32 + 1] = { 0 };
	for (i = 0; i < length; i++)
	{
		getProcessAddr(arr[i], base, basize, szmodule);
		wprintf_s(L"PID:%x base:%x basize%x\n", arr[i], base, basize);
		wprintf_s(L"%ws\n", (szmodule));
	}
	getchar();
	return 0;
}

