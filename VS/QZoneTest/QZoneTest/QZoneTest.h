
// QZoneTest.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CQZoneTestApp:
// �йش����ʵ�֣������ QZoneTest.cpp
//

class CQZoneTestApp : public CWinApp
{
public:
	CQZoneTestApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CQZoneTestApp theApp;