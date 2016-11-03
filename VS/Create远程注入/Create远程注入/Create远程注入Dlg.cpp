
// Create远程注入Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Create远程注入.h"
#include "Create远程注入Dlg.h"
#include "afxdialogex.h"
#include <Windows.h>
#include<afx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCreate远程注入Dlg 对话框



CCreate远程注入Dlg::CCreate远程注入Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CREATE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCreate远程注入Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCreate远程注入Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_ZR, &CCreate远程注入Dlg::OnBnClickedButtonZr)
	ON_BN_CLICKED(IDC_BUTTON_CS, &CCreate远程注入Dlg::OnBnClickedButtonCs)
END_MESSAGE_MAP()


// CCreate远程注入Dlg 消息处理程序

BOOL CCreate远程注入Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	ShowWindow(SW_MINIMIZE);

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCreate远程注入Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCreate远程注入Dlg::OnQueryDragIcon()
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
	MainHwnd = FindWindow("QQ炫舞", "QQ炫舞");
	if (MainHwnd != NULL)
	{
		GetWindowThreadProcessId(MainHwnd, &ProcessID);
		if (ProcessID != NULL)
		{
			ProceHwnd = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessID);
			//判断路径
			if (strlen(DllPath)>0)
			{
				size_t outsize = 0;
				CString str;
				str.Format(_T("%s\\Mydll.dll"), DllPath);
				::MessageBox(NULL, str, TEXT("提示"), MB_OK);
				//为loadlibaray的函数的参数申请内存把需要注入的模块的路径存在远程进程空间中
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
					::MessageBox(NULL, _T("dll模块路径写入失败！"), _T("提示"), MB_OK);
				}
			}

		}
	}
	return FALSE;
}

void CCreate远程注入Dlg::OnBnClickedButtonZr()
{
	// TODO: 在此添加控件通知处理程序代码
	::CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ThreadProc, NULL, NULL, NULL);
}


void CCreate远程注入Dlg::OnBnClickedButtonCs()
{
	// TODO: 在此添加控件通知处理程序代码
	TCHAR DllPath[_MAX_PATH] = { 0 };
	::SHGetSpecialFolderPath(NULL, DllPath, 21, FALSE);
	CString str;
	str.Format(_T("%s\\Mydll.dll"), DllPath);
	::MessageBox(NULL, str, TEXT("提示"), MB_OK);
}
