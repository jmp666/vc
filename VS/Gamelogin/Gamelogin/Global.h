#pragma once
#include "stdafx.h"
#ifndef  _GLOBAL_
#define  _GLOBAL_
#include <map>
using namespace std;
typedef map<DWORD, CString> Map_Str;
typedef struct  tagUSERLONGINMESSAGE 
{
	CString m_UserName;		//用户名
	CString m_PassWord;		//密码
	Map_Str m_GameRepion;				//游戏大区
	Map_Str m_GameServer;				//服务器
	Map_Str m_GameLine;				//线路
	Map_Str m_GameRole;				//角色
}USERLONGINMESSAGE,*PUSERLONGINMESSAGE;

typedef struct tagMyHwnd
{
	OUT HWND hwnd;			//控件的句柄
	IN DWORD WidGetID;		//控件ID
}MyHwnd, *PMyHwnd;
//获取游戏路径
CString GetGamePathdirectory();
#endif
