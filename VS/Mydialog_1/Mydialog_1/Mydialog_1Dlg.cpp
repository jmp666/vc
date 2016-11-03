
// Mydialog_1Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Mydialog_1.h"
#include "Mydialog_1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMydialog_1Dlg 对话框



CMydialog_1Dlg::CMydialog_1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MYDIALOG_1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMydialog_1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMydialog_1Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMydialog_1Dlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CMydialog_1Dlg 消息处理程序

BOOL CMydialog_1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMydialog_1Dlg::OnPaint()
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
HCURSOR CMydialog_1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


CEdit* m_Edit = NULL;
CButton* m_Button = NULL;
void CMydialog_1Dlg::OnBnClickedButton1()
{
	m_Edit = (CEdit*)GetDlgItem(IDC_EDIT1);
	if (!m_Edit)
		MessageBox(L"获取窗口控件失败了");
	TCHAR szbuf[0x100];
	memset(szbuf, 0, 0x100);
	m_Edit->GetWindowText(szbuf, 0x100);
	this->SetWindowText(szbuf);
}
