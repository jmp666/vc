
// CreateԶ��ע��.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCreateԶ��ע��App: 
// �йش����ʵ�֣������ CreateԶ��ע��.cpp
//

class CCreateԶ��ע��App : public CWinApp
{
public:
	CCreateԶ��ע��App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CCreateԶ��ע��App theApp;