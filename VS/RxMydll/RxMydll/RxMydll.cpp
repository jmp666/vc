// RxMydll.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "RxMydll.h"
#include "Mydlg.h"
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

// CRxMydllApp

BEGIN_MESSAGE_MAP(CRxMydllApp, CWinApp)
END_MESSAGE_MAP()


// CRxMydllApp ����
CRxMydllApp::CRxMydllApp()
{
	// TODO:  �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CRxMydllApp ����

CRxMydllApp theApp;


// CRxMydllApp ��ʼ��
CMydlg* Pdlg = new CMydlg;
DWORD WINAPI ShowDialog(LPVOID lprame)
{
	Pdlg->DoModal();
	delete Pdlg;
	FreeLibraryAndExitThread(theApp.m_hInstance, 0);
	return TRUE;
}
BOOL CRxMydllApp::InitInstance()
{
	CWinApp::InitInstance();
	::CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ShowDialog, NULL, NULL, NULL);
	return TRUE;
}
