// Mydll.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCLibrary1.h"
#include "Mydll.h"
#include "afxdialogex.h"

// CMydll �Ի���
DWORD G_Oladdress = NULL;	//ԭ��������ַ
DWORD G_NewAddress = NULL;	//�޸ĺ�ĺ�����ַ
BOOL G_bflog = FALSE;
DWORD Polgmessagadd = (DWORD)::GetProcAddress(LoadLibrary("ws2_32.dll"), "send");//��ȡsend������ַ
CString G_str;
//ȫ����

IMPLEMENT_DYNAMIC(CMydll, CDialogEx)

CMydll::CMydll(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

CMydll::~CMydll()
{
}

void CMydll::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_Edit);
}


BEGIN_MESSAGE_MAP(CMydll, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CMydll::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMydll::OnBnClickedButton2)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CMydll ��Ϣ�������
int Mysend(SOCKET s, const char* buf, int len, int flags)
{
	typedef int (WINAPI *Pmymessagebox)(SOCKET, const char*, int, int); //�Զ��庯��
																		//��ȡ��������
	int m_len = strlen(buf);
	G_str.Format("�׽���������=%X ���ݳ���=%d  ", s, len);
	CString m_str;
	for (int i = 0; i < m_len; i++)
	{
		m_str.Format("%X  ", *(buf + i));
	}
	G_str += m_str;
	int ret = (Pmymessagebox(Polgmessagadd))(s, buf, len, flags);
	return ret;
}
DWORD setHookfunc(DWORD dest, DWORD src)
{
	BOOL bFlag = FALSE;
	__try
	{
		PIMAGE_NT_HEADERS Pnt_head = NULL;
		PDWORD Piathead = NULL;
		DWORD Imagebase = (DWORD)::GetModuleHandle(NULL);
		PIMAGE_IMPORT_DESCRIPTOR Pimportaddres = NULL;
		if (!Imagebase)
		{
			return FALSE;
		}
		Pnt_head = (PIMAGE_NT_HEADERS)((DWORD)Imagebase + (DWORD)(((PIMAGE_DOS_HEADER)Imagebase)->e_lfanew));
		Pimportaddres = (PIMAGE_IMPORT_DESCRIPTOR)(Imagebase + (DWORD)Pnt_head->OptionalHeader.DataDirectory[1].VirtualAddress);
		while (Pimportaddres->FirstThunk != 0 && bFlag == FALSE)
		{
			Piathead = (PDWORD)((DWORD)Imagebase + Pimportaddres->FirstThunk);
			while (*Piathead)
			{
				if (*Piathead == dest)
				{
					*Piathead = src;
					bFlag = TRUE;
					break;
				}
				Piathead++;
			}
			Pimportaddres = (PIMAGE_IMPORT_DESCRIPTOR)((DWORD)Pimportaddres + sizeof(IMAGE_IMPORT_DESCRIPTOR));
		}
		G_Oladdress = dest;
		G_NewAddress = src;
		G_bflog = 1;
	}
	__except (1)
	{
		TRACE("debug ���쳣2\r\n");
	}
	return bFlag;
}
DWORD unlHook()
{
	BOOL bFlag = FALSE;
	__try
	{
		PIMAGE_NT_HEADERS Pnt_head = NULL;
		PDWORD Piathead = NULL;
		DWORD Imagebase = (DWORD)::GetModuleHandle(NULL);
		PIMAGE_IMPORT_DESCRIPTOR Pimportaddres = NULL;
		if (!Imagebase)
		{
			return FALSE;
		}
		if (!G_bflog)
		{
			AfxMessageBox("hook δʵ������ж��\n");
			return FALSE;
		}
		Pnt_head = (PIMAGE_NT_HEADERS)((DWORD)Imagebase + (DWORD)(((PIMAGE_DOS_HEADER)Imagebase)->e_lfanew));
		Pimportaddres = (PIMAGE_IMPORT_DESCRIPTOR)(Imagebase + (DWORD)Pnt_head->OptionalHeader.DataDirectory[1].VirtualAddress);
		while (Pimportaddres->FirstThunk != 0 && bFlag == FALSE)
		{
			Piathead = (PDWORD)((DWORD)Imagebase + Pimportaddres->FirstThunk);
			while (*Piathead)
			{
				if (*Piathead == G_NewAddress)
				{
					*Piathead = G_Oladdress;
					bFlag = TRUE;
					break;
				}
				Piathead++;
			}
			Pimportaddres = (PIMAGE_IMPORT_DESCRIPTOR)((DWORD)Pimportaddres + sizeof(IMAGE_IMPORT_DESCRIPTOR));
		}
		G_Oladdress = 0;
		G_NewAddress = 0;
		G_bflog = 0;
	}
	__except (1)
	{
		TRACE("debug ���쳣\r\n");
	}
	return bFlag;
}

void CMydll::OnBnClickedButton1()
{
	setHookfunc(Polgmessagadd, (DWORD)Mysend);
	SetTimer(1, 1000, NULL);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CMydll::OnBnClickedButton2()
{
	unlHook();
	KillTimer(1);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


BOOL CMydll::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	DWORD Imagebase = NULL;
	Imagebase = (DWORD)::GetModuleHandle(NULL);
	if (Imagebase != NULL)
	{
		CString szbuf;
		szbuf.Format("%X", Imagebase);
		SetWindowText(szbuf);
	}
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CMydll::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (nIDEvent == 1)
	{
		m_Edit.SetWindowText(G_str);
	}
	//CDialogEx::OnTimer(nIDEvent);
}
