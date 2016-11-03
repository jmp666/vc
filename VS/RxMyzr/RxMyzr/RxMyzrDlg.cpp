
// RxMyzrDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "RxMyzr.h"
#include "RxMyzrDlg.h"
#include "afxdialogex.h"
#define GameClass "D3D Window"	//游戏类名
#define GameWinName "YB_OnlineClient"	//游戏标题
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRxMyzrDlg 对话框



CRxMyzrDlg::CRxMyzrDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_RXMYZR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRxMyzrDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_PATH, m_Edit);
}

BEGIN_MESSAGE_MAP(CRxMyzrDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_ZR, &CRxMyzrDlg::OnBnClickedButtonZr)
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CRxMyzrDlg::OnBnClickedButtonOpen)
END_MESSAGE_MAP()


// CRxMyzrDlg 消息处理程序

BOOL EnablePrivilege(HANDLE hToken, PTCHAR szPrivName)
{

	TOKEN_PRIVILEGES tkp;

	LookupPrivilegeValue(NULL, szPrivName, &tkp.Privileges[0].Luid);//修改进程权限
	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	AdjustTokenPrivileges(hToken, FALSE, &tkp, sizeof tkp, NULL, NULL);//通知系统修改进程权限

	return((GetLastError() == ERROR_SUCCESS));

}
BOOL CRxMyzrDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	ShowWindow(SW_SHOWNORMAL);

	//提升自身权限
	HANDLE	hToken;
	::OpenProcessToken(::GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken);
	EnablePrivilege(hToken, SE_DEBUG_NAME);
	// TODO: 在此添加额外的初始化代码
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CRxMyzrDlg::OnPaint()
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
HCURSOR CRxMyzrDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


BOOL InjeCtion(HANDLE Hproce, CString Path)
{
	LPVOID dwAddress = NULL;
	DWORD ThreadID = 0;
	DWORD Sizedw = 0;
	DWORD ExitCode = NULL;
	HANDLE RemoteThread = NULL;
	dwAddress = ::VirtualAllocEx(Hproce, NULL, _MAX_PATH, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (dwAddress!=NULL)
	{
		::WriteProcessMemory(Hproce, dwAddress, Path, Path.GetLength() + 1, &Sizedw);
		if (Sizedw>=Path.GetLength())
		{
			RemoteThread=::CreateRemoteThread(Hproce, NULL, NULL, (LPTHREAD_START_ROUTINE)LoadLibrary, dwAddress, NULL, &ThreadID);
			if (!ThreadID)
			{
				AfxMessageBox("创建远程线程失败了");
				return FALSE;
			}
			::WaitForSingleObject(RemoteThread, 0xffffffff);
			::GetExitCodeThread(RemoteThread, &ExitCode);	//获取线程退出代码
			::VirtualFreeEx(Hproce, dwAddress, 0, MEM_RELEASE);
			::CloseHandle(RemoteThread);
			FreeLibrary((HMODULE)ExitCode);
			CloseHandle(Hproce);
			return TRUE;
		}
		else
		{
			AfxMessageBox("DLL模块路径写入失败！");
		}
	}
	else
	{
		AfxMessageBox("申请内存空间失败了");
		return FALSE;
	}
}
void CRxMyzrDlg::OnBnClickedButtonZr()
{
	HWND GameHwan = NULL;
	GameHwan = ::FindWindow(GameClass, GameWinName);
	CString GamePath;
	DWORD GamePid = 0;
	if (GameHwan)
	{
		::GetWindowThreadProcessId(GameHwan, &GamePid);
		if (GamePid)
		{
			HANDLE GameHandle = NULL;
			GameHandle = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, GamePid);
			if (GameHandle)
			{
				m_Edit.GetWindowText(GamePath);
				if (GamePath!="")
				{
					InjeCtion(GameHandle, GamePath);
				}
				else
				{
					AfxMessageBox("dll模块路径未选择！");
				}
			}
			else
			{
				AfxMessageBox("获取进程句柄失败了!");
			}
		}
		else
		{
			AfxMessageBox("获取进程标识符失败");
		}
	}
	else
	{
		AfxMessageBox("获取窗口句柄失败了！");
	}
	// TODO: 在此添加控件通知处理程序代码

}




void CRxMyzrDlg::OnBnClickedButtonOpen()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "All File(*.dll)|*.dll||", AfxGetMainWnd(), 0, TRUE);
	CString Str;
	if (dlg.DoModal()==IDOK)
	{
		Str = dlg.GetPathName();
		m_Edit.SetWindowText(Str);
	}
	else
	{
		AfxMessageBox("请选择要注入的dll模块！");
	}
}
