#pragma once
#include "stdafx.h"
#ifndef  _GLOBAL_
#define  _GLOBAL_
#include <map>
using namespace std;
typedef map<DWORD, CString> Map_Str;
typedef struct  tagUSERLONGINMESSAGE 
{
	CString m_UserName;		//�û���
	CString m_PassWord;		//����
	Map_Str m_GameRepion;				//��Ϸ����
	Map_Str m_GameServer;				//������
	Map_Str m_GameLine;				//��·
	Map_Str m_GameRole;				//��ɫ
}USERLONGINMESSAGE,*PUSERLONGINMESSAGE;

typedef struct tagMyHwnd
{
	OUT HWND hwnd;			//�ؼ��ľ��
	IN DWORD WidGetID;		//�ؼ�ID
}MyHwnd, *PMyHwnd;
//��ȡ��Ϸ·��
CString GetGamePathdirectory();
#endif
