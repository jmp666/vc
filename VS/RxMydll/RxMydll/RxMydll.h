// RxMydll.h : RxMydll DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CRxMydllApp
// �йش���ʵ�ֵ���Ϣ������� RxMydll.cpp
//

class CRxMydllApp : public CWinApp
{
public:
	CRxMydllApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
