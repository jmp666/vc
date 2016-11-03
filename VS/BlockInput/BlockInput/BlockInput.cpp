// BlockInput.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<windows.h>
void jiance()
{
	::BlockInput(TRUE);
	int i = 0;
	i++;
	::BlockInput(FALSE);
}
typedef   enum   _THREADINFOCLASS {
	ThreadBasicInformation,
	ThreadTimes,
	ThreadPriority,
	ThreadBasePriority,
	ThreadAffinityMask,
	ThreadImpersonationToken,
	ThreadDescriptorTableEntry,
	ThreadEnableAlignmentFaultFixup,
	ThreadEventPair_Reusable,
	ThreadQuerySetWin32StartAddress,
	ThreadZeroTlsCell,
	ThreadPerformanceCount,
	ThreadAmILastThread,
	ThreadIdealProcessor,
	ThreadPriorityBoost,
	ThreadSetTlsArrayAddress,
	ThreadIsIoPending,
	ThreadHideFromDebugger,
	ThreadBreakOnTermination,
	MaxThreadInfoClass
}THREADINFOCLASS;

typedef NTSTATUS(NTAPI* ZwSetInformationThread)(
	_In_ HANDLE          ThreadHandle,
	_In_ THREADINFOCLASS ThreadInformationClass,
	_In_ PVOID           ThreadInformation,
	_In_ ULONG           ThreadInformationLength);
VOID jiance2()
{
	HANDLE hwnd;
	HMODULE hModule;
	hwnd = ::GetCurrentThread();	//获取当前线程的句柄
	hModule = ::LoadLibraryA("ntdll.dll");
	ZwSetInformationThread function;
	function = (ZwSetInformationThread)GetProcAddress(hModule, "ZwSetInformationThread");
	function(hwnd, ThreadHideFromDebugger, NULL, NULL);
}
VOID CALLBACK TimerProc(
	_In_ HWND     hwnd,
	_In_ UINT     uMsg,
	_In_ UINT_PTR idEvent,
	_In_ DWORD    dwTime
	);
int main()
{
	//jiance();
	jiance2();
	::SetTimer(NULL, 0, 1000, NULL);
	system("pause");
    return 0;
}

VOID CALLBACK TimerProc(
	_In_ HWND     hwnd,
	_In_ UINT     uMsg,
	_In_ UINT_PTR idEvent,
	_In_ DWORD    dwTime
	)
{
	if (idEvent=0)
	{
		jiance2();
	}
}