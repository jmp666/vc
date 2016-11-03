// ��������.cpp : �������̨Ӧ�ó������ڵ㡣
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

	// ��Ŀ������л�ȡ���н��̵�snapshot
	hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPALL, dwPID);
	if (hModuleSnap == INVALID_HANDLE_VALUE)
	{
		HANDLE hProcess = NULL;
		hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPID);
		//�õ��ý��̵�ȫ·��
		TCHAR procPath[_MAX_PATH] = { 0 };
		GetModuleFileNameEx(hProcess, NULL, procPath, _MAX_PATH);
		//OutputDebugStringF("����IDΪ��%d\n",dwPID);
		return(FALSE);
	}

	// ����MODULEENTRY32���ݽṹ��С�ֶ�
	me32.dwSize = sizeof(MODULEENTRY32);

	//������һ��ģ�����Ϣ�����ɹ��򷵻�
	if (!Module32First(hModuleSnap, &me32))
	{
		//wprintf(L"%s\n", me32.szExePath);
		//OutputDebugStringF("����IDΪ��%d\n",dwPID); // ��ʾ����ʧ��
		CloseHandle(hModuleSnap);    // ����������
		return(FALSE);
	}

	// ��me32�еõ���ַ
	// ������������ģ��������
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

