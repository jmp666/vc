
// QQ_mfcDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "QQ_mfc.h"
#include "QQ_mfcDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CQQ_mfcDlg 对话框



CQQ_mfcDlg::CQQ_mfcDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_QQ_MFC_DIALOG, pParent)
	
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CQQ_mfcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_USER, m_StrUser);	//将编辑框的文本内容和m_struser变量关联
	DDX_Text(pDX, IDC_EDIT_PASS, m_StrPass);
}

BEGIN_MESSAGE_MAP(CQQ_mfcDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_LOGIN, &CQQ_mfcDlg::OnBnClickedBtnLogin)
END_MESSAGE_MAP()


// CQQ_mfcDlg 消息处理程序

BOOL CQQ_mfcDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	创建状态栏();
	ShowWindow(SW_SHOW);

	// TODO: 在此添加额外的初始化代码
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CQQ_mfcDlg::OnPaint()
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
HCURSOR CQQ_mfcDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CQQ_mfcDlg::OnBnClickedBtnLogin()
{
	UpdateData();
	if (m_StrUser.GetLength()<5||m_StrPass.GetLength()<2)
	{
		MessageBox(_T("账号或者密码错误"), _T("提示:"));
		return;
	}
	设置状态栏文本(_T("登陆中......"));
	禁用控件函数(false);
	// TODO: 在此添加控件通知处理程序代码
}


BOOL CQQ_mfcDlg::创建状态栏()
{
	CRect rect;
	GetWindowRect(rect);	//获取主窗口的 RECT
	MoveWindow(rect.left, rect.top, rect.Width(), rect.Height() + 15);	//只需要给窗口的高度增加15即可
	UINT array[1] = { 12301 };
	m_状态栏.Create(this);	//创建状态栏
	m_状态栏.SetIndicators(array, sizeof(array) / sizeof(UINT));
	m_状态栏.SetPaneInfo(0, array[0], 0, rect.Width());
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);
	设置状态栏文本(_T("状态:启动成功!"));
	return TRUE;
}


void CQQ_mfcDlg::设置状态栏文本(PTCHAR strbuf, UINT ID)
{
	if (!strbuf||_tcslen(strbuf)<=0)
	{
		return;
	}
	m_状态栏.SetPaneText(ID, strbuf);
}


bool CQQ_mfcDlg::禁用控件函数(bool Flog)
{
	GetDlgItem(IDC_BTN_LOGIN)->EnableWindow(Flog);
	GetDlgItem(IDC_EDIT_PASS)->EnableWindow(Flog);
	GetDlgItem(IDC_EDIT_USER)->EnableWindow(Flog);
	GetDlgItem(IDC_EDIT_FB)->EnableWindow(Flog);
	GetDlgItem(IDC_EDIT_IMAG)->EnableWindow(Flog);
	GetDlgItem(IDC_BTN_IMAG)->EnableWindow(Flog);
	return TRUE;
}
