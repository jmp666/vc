// Cmydialogbox.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Mydll.h"
#include "Cmydialogbox.h"
#include "afxdialogex.h"


// Cmydialogbox �Ի���

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


// Cmydialogbox ��Ϣ�������


void Cmydialogbox::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
