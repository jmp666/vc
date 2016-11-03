// Mydlg.cpp : 实现文件
//

#include "stdafx.h"
#include "RxMydll.h"
#include "Mydlg.h"
#include "afxdialogex.h"


// CMydlg 对话框

IMPLEMENT_DYNAMIC(CMydlg, CDialogEx)

CMydlg::CMydlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_MAIN, pParent)
{

}

CMydlg::~CMydlg()
{
}

void CMydlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMydlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CMydlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CMydlg 消息处理程序
#define  CALLECX 0x0F822E0
#define  CALLBASE 0x0694440
BOOL CAlltest()
{
	DWORD m_edi = *(PDWORD)CALLECX;
	DWORD m_user = (*(PDWORD)(m_edi + 0x250)) + 0x238;
	memcpy((PTCHAR)m_user, TEXT("jmp222"), strlen(TEXT("jmp222")) + 1);
	TRACE("m_user=%X\n", m_user);
	DWORD m_password = (*(PDWORD)(m_edi + 0x254)) + 0x238;
	memcpy((PTCHAR)m_user, TEXT("test123456"), strlen(TEXT("test123456")) + 1);
	TRACE("m_password=%X\n", m_password);
	__try
	{
		__asm
		{
			mov esi,m_edi
			push m_password
			push m_user
			mov ebx,CALLBASE
			call ebx
		}
	}
	__except (1)
	{
		TRACE("异常\n");
		return FALSE;
	}
	return TRUE;
}
void CMydlg::OnBnClickedButton1()
{
	CAlltest();
}
