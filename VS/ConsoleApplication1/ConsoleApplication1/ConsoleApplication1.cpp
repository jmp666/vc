// ConsoleApplication1.cpp : �������̨Ӧ�ó������ڵ㡣
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
	//�����ֳ�
	_asm
	{
		pushad
		pushfd
	}
	//��ȡ�Ĵ������ֵ
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
	MessageBox(NULL, szbuffer, "[�Ĵ�������]", MB_OK);
	//�ָ��ֳ�
	_asm
	{
		popfd
		popad
	}
	//ִ��ԭ���Ĵ���
	_asm
	{
		//�����Լ�д
	}
	//��ת��ȥ
	_asm
	{
		jmp 
	}
}

int main()
{
    return 0;
}

