
// Mydialog_1.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMydialog_1App: 
// �йش����ʵ�֣������ Mydialog_1.cpp
//

class CMydialog_1App : public CWinApp
{
public:
	CMydialog_1App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMydialog_1App theApp;