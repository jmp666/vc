
// QQ_mfc.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CQQ_mfcApp: 
// �йش����ʵ�֣������ QQ_mfc.cpp
//

class CQQ_mfcApp : public CWinApp
{
public:
	CQQ_mfcApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CQQ_mfcApp theApp;