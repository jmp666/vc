
// CreateԶ��ע��Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CreateԶ��ע��.h"
#include "CreateԶ��ע��Dlg.h"
#include "afxdialogex.h"
#include <Windows.h>
#include<afx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCreateԶ��ע��Dlg �Ի���



CCreateԶ��ע��Dlg::CCreateԶ��ע��Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CREATE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCreateԶ��ע��Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCreateԶ��ע��Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_ZR, &CCreateԶ��ע��Dlg::OnBnClickedButtonZr)
	ON_BN_CLICKED(IDC_BUTTON_CS, &CCreateԶ��ע��Dlg::OnBnClickedButtonCs)
END_MESSAGE_MAP()


// CCreateԶ��ע��Dlg ��Ϣ�������

BOOL CCreateԶ��ע��Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	ShowWindow(SW_MINIMIZE);

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCreateԶ��ע��Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CCreateԶ��ע��Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

DWORD WINAPI ThreadProc(_In_  LPVOID lpParameter)
{
	TCHAR DllPath[_MAX_PATH] = { 0 };
	::SHGetSpecialFolderPath(NULL, DllPath, 21, FALSE);
	HWND MainHwnd = NULL;
	HANDLE ProceHwnd = NULL;
	DWORD ProcessID = 0;
	LPVOID Addressbuffer = NULL;
	HANDLE RemoteThread = NULL;
	DWORD ExitCode = 0;
	MainHwnd = FindWindow("QQ����", "QQ����");
	if (MainHwnd != NULL)
	{
		GetWindowThreadProcessId(MainHwnd, &ProcessID);
		if (ProcessID != NULL)
		{
			ProceHwnd = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessID);
			//�ж�·��
			if (strlen(DllPath)>0)
			{
				size_t outsize = 0;
				CString str;
				str.Format(_T("%s\\Mydll.dll"), DllPath);
				::MessageBox(NULL, str, TEXT("��ʾ"), MB_OK);
				//Ϊloadlibaray�ĺ����Ĳ��������ڴ����Ҫע���ģ���·������Զ�̽��̿ռ���
				Addressbuffer = VirtualAllocEx(ProceHwnd, 0, _MAX_PATH, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
				::WriteProcessMemory(ProceHwnd, Addressbuffer, str, strlen(str) + 1,&outsize);
				if (outsize >= strlen(str))
				{
					RemoteThread =::CreateRemoteThread(ProceHwnd, NULL, 0, (LPTHREAD_START_ROUTINE)LoadLibrary, Addressbuffer, 0, 0);
					WaitForSingleObject(RemoteThread, 0xffffffff);
					GetExitCodeThread(RemoteThread, &ExitCode);
					VirtualFreeEx(ProceHwnd, Addressbuffer, 0, MEM_RELEASE);
					CloseHandle(RemoteThread);
					FreeLibrary((HMODULE)ExitCode);
					CloseHandle(ProceHwnd);
					return TRUE;
				}
				else
				{
					::MessageBox(NULL, _T("dllģ��·��д��ʧ�ܣ�"), _T("��ʾ"), MB_OK);
				}
			}

		}
	}
	return FALSE;
}

void CCreateԶ��ע��Dlg::OnBnClickedButtonZr()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	::CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ThreadProc, NULL, NULL, NULL);
}


void CCreateԶ��ע��Dlg::OnBnClickedButtonCs()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	TCHAR DllPath[_MAX_PATH] = { 0 };
	::SHGetSpecialFolderPath(NULL, DllPath, 21, FALSE);
	CString str;
	str.Format(_T("%s\\Mydll.dll"), DllPath);
	::MessageBox(NULL, str, TEXT("��ʾ"), MB_OK);
}
