
// MyDialogDlg.cpp : ʵ���ļ�
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


// CMyDialogDlg �Ի���



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


// CMyDialogDlg ��Ϣ�������
CListCtrl* Plist;
//��ȡ�����ļ�·��
BOOL GetMoudlePath(DWORD PID, TCHAR* szbupath)
{
	HANDLE Moudlepath = NULL;
	Moudlepath = ::CreateToolhelp32Snapshot(TH32CS_SNAPALL, PID);
	if (Moudlepath ==INVALID_HANDLE_VALUE)	//��ȡ���̿���ʧ��
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
//����������Ϣ���뵽�б��
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
//����Ȩ��
BOOL EnablePrivilege(HANDLE hToken, PTCHAR szPrivName)
{

	TOKEN_PRIVILEGES tkp;

	LookupPrivilegeValue(NULL, szPrivName, &tkp.Privileges[0].Luid);//�޸Ľ���Ȩ��
	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	AdjustTokenPrivileges(hToken, FALSE, &tkp, sizeof tkp, NULL, NULL);//֪ͨϵͳ�޸Ľ���Ȩ��

	return((GetLastError() == ERROR_SUCCESS));

}
HANDLE	hToken;
BOOL CMyDialogDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	ShowWindow(SW_SHOWNORMAL);
	//��������Ȩ��
	::OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken);
	EnablePrivilege(hToken, SE_DEBUG_NAME);
// 	BOOL Ret = 
// 	TCHAR szbufferx[0x20];
// 	memset(szbufferx, 0, 0x20);
	//swprintf(szbufferx, 0x20, L"%d", Ret);
	//this->MessageBox(szbufferx);
	Plist = (CListCtrl*)GetDlgItem(IDC_LIST1);
	Plist->InsertColumn(0, TEXT("������"),LVCFMT_LEFT,100);
	Plist->InsertColumn(1, TEXT("PID"), LVCFMT_LEFT, 100);
	Plist->InsertColumn(2, TEXT("·��"), LVCFMT_LEFT, 300);
	Plist->SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	EnumProceWindow();
	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMyDialogDlg::OnPaint()
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
HCURSOR CMyDialogDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMyDialogDlg::OnBnClickedButtonClose()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	AfxGetMainWnd()->SendMessage(WM_CLOSE);
}
