
// RxMyzr.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CRxMyzrApp: 
// �йش����ʵ�֣������ RxMyzr.cpp
//

class CRxMyzrApp : public CWinApp
{
public:
	CRxMyzrApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CRxMyzrApp theApp;