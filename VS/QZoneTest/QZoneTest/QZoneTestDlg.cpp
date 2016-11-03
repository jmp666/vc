
// QZoneTestDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "QZoneTest.h"
#include "QZoneTestDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CQZoneTestDlg 对话框




CQZoneTestDlg::CQZoneTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CQZoneTestDlg::IDD, pParent)
	, m_strQQ(_T(""))
	, m_strPass(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CQZoneTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ID, m_strQQ);
	DDX_Text(pDX, IDC_EDIT_PASS, m_strPass);
}

BEGIN_MESSAGE_MAP(CQZoneTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_LOGIN, &CQZoneTestDlg::OnBnClickedBtnLogin)
	ON_BN_CLICKED(IDC_BTN_PUBLIC, &CQZoneTestDlg::OnBnClickedBtnPublic)
END_MESSAGE_MAP()


// CQZoneTestDlg 消息处理程序

BOOL CQZoneTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	InitStatusBar();
	SetDlgItemText(IDC_EDIT_ID, _T("8260671"));
	SetDlgItemText(IDC_EDIT_PASS, _T("8260671"));

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CQZoneTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CQZoneTestDlg::OnPaint()
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
HCURSOR CQZoneTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CQZoneTestDlg::InitStatusBar()
{
	CRect rect;
	GetWindowRect(rect);
	MoveWindow(rect.left, rect.top, rect.Width(), rect.Height()+15);

	UINT array[1] = {12301};
	m_Statusbar.Create(this);
	m_Statusbar.SetIndicators(array, sizeof(array)/sizeof(UINT));

	m_Statusbar.SetPaneInfo(0, array[0], 0, rect.Width());
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0); 

	SetStateInfo(_T("状态：启动成功！"));

	return TRUE;
}

void CQZoneTestDlg::SetStateInfo(LPCTSTR lpszText, UINT posIdx)
{
	if (!lpszText || _tcslen(lpszText) <= 0) return;
	m_Statusbar.SetPaneText(posIdx, lpszText);
}

void CQZoneTestDlg::EnableControl(BOOL bEnable)
{
	GetDlgItem(IDC_EDIT_ID)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_PASS)->EnableWindow(bEnable);
	GetDlgItem(IDC_BTN_LOGIN)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_TEXT_PUBLIC)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_IMG_PATH)->EnableWindow(bEnable);
	GetDlgItem(IDC_BTN_BROWSE)->EnableWindow(bEnable);
	GetDlgItem(IDC_BTN_PUBLIC)->EnableWindow(bEnable);
}

#include "QZoneThread.h"
void CQZoneTestDlg::OnBnClickedBtnLogin()
{
	UpdateData(TRUE);
	if (m_strQQ.GetLength() < 5 || m_strPass.GetLength() < 2) {
		MessageBox(_T("账号或密码错误，请输入正确的QQ号和密码信息！"), _T("提示"));
		return;
	}

	CWinThread *pThread = AfxBeginThread(LoginQZoneFunc, this); //loginQZone
	if (pThread) {
		EnableControl(FALSE);
		SetStateInfo(_T("状态：登陆中..."));
	}
}


void CQZoneTestDlg::OnBnClickedBtnPublic()
{
	CString strText;
	GetDlgItemText(IDC_EDIT_TEXT_PUBLIC, strText);
	if (strText.IsEmpty()) {
		MessageBox(_T("请输入要发布的文本内容！"), _T("提示"));
		return;
	}

	SetStateInfo(_T("状态：发布中..."));

	GetDlgItem(IDC_EDIT_TEXT_PUBLIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_IMG_PATH)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_BROWSE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_PUBLIC)->EnableWindow(FALSE);
}
