
// MyDialogDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MyDialog.h"
#include "MyDialogDlg.h"
#include "afxdialogex.h"
#include <stdio.h>
#include<TlHelp32.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyDialogDlg 对话框



CMyDialogDlg::CMyDialogDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MYDIALOG_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyDialogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMyDialogDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CMyDialogDlg::OnBnClickedButtonClose)
END_MESSAGE_MAP()


// CMyDialogDlg 消息处理程序
CListCtrl* Plist;
//获取进程文件路径
BOOL GetMoudlePath(DWORD PID, TCHAR* szbupath)
{
	HANDLE Moudlepath = NULL;
	Moudlepath = ::CreateToolhelp32Snapshot(TH32CS_SNAPALL, PID);
	if (Moudlepath ==INVALID_HANDLE_VALUE)	//获取进程快照失败
	{
		return FALSE;
	}
	MODULEENTRY32 Module32 = { 0 };
	Module32.dwSize = sizeof(MODULEENTRY32);
	BOOL Ret = ::Module32First(Moudlepath, &Module32);
	if (!Ret)
	{
		::CloseHandle(Moudlepath);
		return FALSE;
	}
	memcpy(szbupath, Module32.szExePath, MAX_PATH);
	::CloseHandle(Moudlepath);
	return TRUE;
}
//遍历进程信息插入到列表框
BOOL EnumProceWindow()
{
	HANDLE ProcessHandle = NULL;
	ProcessHandle=::CreateToolhelp32Snapshot(TH32CS_SNAPALL, NULL);
	if (ProcessHandle == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
	PROCESSENTRY32 Pe32 = { 0 };
	Pe32.dwSize = sizeof(PROCESSENTRY32);
	if (!::Process32First(ProcessHandle,&Pe32))
	{
		::CloseHandle(ProcessHandle);
		return FALSE;
	}
	DWORD dwIndex = 0;
	TCHAR szbuffer[MAX_PATH];
	TCHAR szpath[MAX_PATH];
	do 
	{
		memset(szbuffer, 0, MAX_PATH);
		memset(szpath, 0, MAX_PATH);
		swprintf(szbuffer,MAX_PATH, L"%d", Pe32.th32ProcessID);
		Plist->InsertItem(dwIndex, Pe32.szExeFile);
		Plist->SetItemText(dwIndex, 1, szbuffer);
		memset(szbuffer, 0, MAX_PATH);
		GetMoudlePath(Pe32.th32ProcessID, szbuffer);
		memcpy(szpath, szbuffer, MAX_PATH);
		Plist->SetItemText(dwIndex, 2, szpath);
		dwIndex++;
	} while (Process32Next(ProcessHandle,&Pe32));
	return TRUE;
}
//提升权限
BOOL EnablePrivilege(HANDLE hToken, PTCHAR szPrivName)
{

	TOKEN_PRIVILEGES tkp;

	LookupPrivilegeValue(NULL, szPrivName, &tkp.Privileges[0].Luid);//修改进程权限
	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	AdjustTokenPrivileges(hToken, FALSE, &tkp, sizeof tkp, NULL, NULL);//通知系统修改进程权限

	return((GetLastError() == ERROR_SUCCESS));

}
HANDLE	hToken;
BOOL CMyDialogDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	ShowWindow(SW_SHOWNORMAL);
	//提升自身权限
	::OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken);
	EnablePrivilege(hToken, SE_DEBUG_NAME);
// 	BOOL Ret = 
// 	TCHAR szbufferx[0x20];
// 	memset(szbufferx, 0, 0x20);
	//swprintf(szbufferx, 0x20, L"%d", Ret);
	//this->MessageBox(szbufferx);
	Plist = (CListCtrl*)GetDlgItem(IDC_LIST1);
	Plist->InsertColumn(0, TEXT("进程名"),LVCFMT_LEFT,100);
	Plist->InsertColumn(1, TEXT("PID"), LVCFMT_LEFT, 100);
	Plist->InsertColumn(2, TEXT("路径"), LVCFMT_LEFT, 300);
	Plist->SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	EnumProceWindow();
	// TODO: 在此添加额外的初始化代码
	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMyDialogDlg::OnPaint()
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
HCURSOR CMyDialogDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMyDialogDlg::OnBnClickedButtonClose()
{
	// TODO: 在此添加控件通知处理程序代码
	AfxGetMainWnd()->SendMessage(WM_CLOSE);
}
