// Mydll.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCLibrary1.h"
#include "Mydll.h"
#include "afxdialogex.h"

// CMydll 对话框
DWORD G_Oladdress = NULL;	//原来函数地址
DWORD G_NewAddress = NULL;	//修改后的函数地址
BOOL G_bflog = FALSE;
DWORD Polgmessagadd = (DWORD)::GetProcAddress(LoadLibrary("ws2_32.dll"), "send");//获取send函数地址
CString G_str;
//全局区

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


// CMydll 消息处理程序
int Mysend(SOCKET s, const char* buf, int len, int flags)
{
	typedef int (WINAPI *Pmymessagebox)(SOCKET, const char*, int, int); //自定义函数
																		//获取参数内容
	int m_len = strlen(buf);
	G_str.Format("套接字描述符=%X 数据长度=%d  ", s, len);
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
		TRACE("debug 有异常2\r\n");
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
			AfxMessageBox("hook 未实现无需卸载\n");
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
		TRACE("debug 有异常\r\n");
	}
	return bFlag;
}

void CMydll::OnBnClickedButton1()
{
	setHookfunc(Polgmessagadd, (DWORD)Mysend);
	SetTimer(1, 1000, NULL);
	// TODO: 在此添加控件通知处理程序代码
}


void CMydll::OnBnClickedButton2()
{
	unlHook();
	KillTimer(1);
	// TODO: 在此添加控件通知处理程序代码
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
	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CMydll::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent == 1)
	{
		m_Edit.SetWindowText(G_str);
	}
	//CDialogEx::OnTimer(nIDEvent);
}
