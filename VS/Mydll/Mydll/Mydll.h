// Mydll.h : Mydll DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMydllApp
// �йش���ʵ�ֵ���Ϣ������� Mydll.cpp
//

class CMydllApp : public CWinApp
{
public:
	CMydllApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
