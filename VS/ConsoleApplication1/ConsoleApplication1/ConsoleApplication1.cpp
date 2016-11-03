// ConsoleApplication1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>
#include <stdio.h>
struct _REGISTER
{
	DWORD EAX;
	DWORD ECX;
	DWORD EDX;
	DWORD EBX;
	DWORD ESP;
	DWORD EBP;
	DWORD ESI;
	DWORD EDI;
}Register;
_REGISTER Reg = { 0 };
TCHAR szbuffer[0x100] = { 0 };
extern "C" _declspec(naked)VOID HookProc()
{
	//保存现场
	_asm
	{
		pushad
		pushfd
	}
	//获取寄存器里的值
	_asm
	{
		mov Reg.EAX,eax
		mov Reg.ECX,ecx
		mov Reg.EDX,edx
		mov Reg.EBX,ebx
		mov Reg.ESP,esp
		mov Reg.EBP,ebp
		mov Reg.ESI,esi
		mov Reg.EDI,edi
	}
	sprintf(szbuffer, "EAX:%X\nECX:%X\nEDX:%X\nEBX:%X\nESP:%X\nEBP:%X\nESI:%X\nEDI:%X\n", Reg.EAX, Reg.ECX, Reg.EDX, Reg.EBX, Reg.ESP, Reg.EBP, Reg.ESI, Reg.EDI);
	MessageBox(NULL, szbuffer, "[寄存器数据]", MB_OK);
	//恢复现场
	_asm
	{
		popfd
		popad
	}
	//执行原来的代码
	_asm
	{
		//这里自己写
	}
	//跳转回去
	_asm
	{
		jmp 
	}
}

int main()
{
    return 0;
}

