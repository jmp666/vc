
// HttptestIDC816.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CHttptestIDC816App: 
// �йش����ʵ�֣������ HttptestIDC816.cpp
//

class CHttptestIDC816App : public CWinApp
{
public:
	CHttptestIDC816App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CHttptestIDC816App theApp;