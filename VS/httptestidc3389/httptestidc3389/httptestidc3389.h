
// httptestidc3389.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Chttptestidc3389App: 
// �йش����ʵ�֣������ httptestidc3389.cpp
//

class Chttptestidc3389App : public CWinApp
{
public:
	Chttptestidc3389App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Chttptestidc3389App theApp;