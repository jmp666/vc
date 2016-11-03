// Cmydialogbox.cpp : 实现文件
//

#include "stdafx.h"
#include "Mydll.h"
#include "Cmydialogbox.h"
#include "afxdialogex.h"


// Cmydialogbox 对话框

IMPLEMENT_DYNAMIC(Cmydialogbox, CDialogEx)

Cmydialogbox::Cmydialogbox(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_MAIN, pParent)
{

}

Cmydialogbox::~Cmydialogbox()
{
}

void Cmydialogbox::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Cmydialogbox, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &Cmydialogbox::OnBnClickedButton1)
END_MESSAGE_MAP()


// Cmydialogbox 消息处理程序


void Cmydialogbox::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
}
