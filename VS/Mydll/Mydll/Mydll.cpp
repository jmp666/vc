// Mydll.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "Mydll.h"
#include "Cmydialogbox.h"
#include <Windows.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO:  ����� DLL ����� MFC DLL �Ƕ�̬���ӵģ�
//		��Ӵ� DLL �������κε���
//		MFC �ĺ������뽫 AFX_MANAGE_STATE ����ӵ�
//		�ú�������ǰ�档
//
//		����: 
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// �˴�Ϊ��ͨ������
//		}
//
//		�˺������κ� MFC ����
//		������ÿ��������ʮ����Ҫ��  ����ζ��
//		��������Ϊ�����еĵ�һ�����
//		���֣������������ж������������
//		������Ϊ���ǵĹ��캯���������� MFC
//		DLL ���á�
//
//		�й�������ϸ��Ϣ��
//		����� MFC ����˵�� 33 �� 58��
//

// CMydllApp

BEGIN_MESSAGE_MAP(CMydllApp, CWinApp)
END_MESSAGE_MAP()


// CMydllApp ����

CMydllApp::CMydllApp()
{
	// TODO:  �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CMydllApp ����

CMydllApp theApp;

Cmydialogbox* PmydIg;
// CMydllApp ��ʼ��
DWORD WINAPI ThreadProc(_In_  LPVOID lpParameter)
{
	PmydIg= new Cmydialogbox;
	PmydIg->DoModal();
	delete PmydIg;
	FreeLibraryAndExitThread(theApp.m_hInstance, 1);
	return TRUE;
}
BOOL CMydllApp::InitInstance()
{
	CWinApp::InitInstance();
	::CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProc, 0, NULL, NULL);
	return TRUE;
}
