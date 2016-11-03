
// RxMyzrDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "RxMyzr.h"
#include "RxMyzrDlg.h"
#include "afxdialogex.h"
#define GameClass "D3D Window"	//��Ϸ����
#define GameWinName "YB_OnlineClient"	//��Ϸ����
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRxMyzrDlg �Ի���



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


// CRxMyzrDlg ��Ϣ�������

BOOL EnablePrivilege(HANDLE hToken, PTCHAR szPrivName)
{

	TOKEN_PRIVILEGES tkp;

	LookupPrivilegeValue(NULL, szPrivName, &tkp.Privileges[0].Luid);//�޸Ľ���Ȩ��
	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	AdjustTokenPrivileges(hToken, FALSE, &tkp, sizeof tkp, NULL, NULL);//֪ͨϵͳ�޸Ľ���Ȩ��

	return((GetLastError() == ERROR_SUCCESS));

}
BOOL CRxMyzrDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	ShowWindow(SW_SHOWNORMAL);

	//��������Ȩ��
	HANDLE	hToken;
	::OpenProcessToken(::GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken);
	EnablePrivilege(hToken, SE_DEBUG_NAME);
	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CRxMyzrDlg::OnPaint()
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
				AfxMessageBox("����Զ���߳�ʧ����");
				return FALSE;
			}
			::WaitForSingleObject(RemoteThread, 0xffffffff);
			::GetExitCodeThread(RemoteThread, &ExitCode);	//��ȡ�߳��˳�����
			::VirtualFreeEx(Hproce, dwAddress, 0, MEM_RELEASE);
			::CloseHandle(RemoteThread);
			FreeLibrary((HMODULE)ExitCode);
			CloseHandle(Hproce);
			return TRUE;
		}
		else
		{
			AfxMessageBox("DLLģ��·��д��ʧ�ܣ�");
		}
	}
	else
	{
		AfxMessageBox("�����ڴ�ռ�ʧ����");
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
					AfxMessageBox("dllģ��·��δѡ��");
				}
			}
			else
			{
				AfxMessageBox("��ȡ���̾��ʧ����!");
			}
		}
		else
		{
			AfxMessageBox("��ȡ���̱�ʶ��ʧ��");
		}
	}
	else
	{
		AfxMessageBox("��ȡ���ھ��ʧ���ˣ�");
	}
	// TODO: �ڴ���ӿؼ�֪ͨ����������

}




void CRxMyzrDlg::OnBnClickedButtonOpen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "All File(*.dll)|*.dll||", AfxGetMainWnd(), 0, TRUE);
	CString Str;
	if (dlg.DoModal()==IDOK)
	{
		Str = dlg.GetPathName();
		m_Edit.SetWindowText(Str);
	}
	else
	{
		AfxMessageBox("��ѡ��Ҫע���dllģ�飡");
	}
}
