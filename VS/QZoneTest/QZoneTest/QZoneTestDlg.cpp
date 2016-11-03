
// QZoneTestDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "QZoneTest.h"
#include "QZoneTestDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CQZoneTestDlg �Ի���




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


// CQZoneTestDlg ��Ϣ�������

BOOL CQZoneTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	InitStatusBar();
	SetDlgItemText(IDC_EDIT_ID, _T("8260671"));
	SetDlgItemText(IDC_EDIT_PASS, _T("8260671"));

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CQZoneTestDlg::OnPaint()
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

	SetStateInfo(_T("״̬�������ɹ���"));

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
		MessageBox(_T("�˺Ż����������������ȷ��QQ�ź�������Ϣ��"), _T("��ʾ"));
		return;
	}

	CWinThread *pThread = AfxBeginThread(LoginQZoneFunc, this); //loginQZone
	if (pThread) {
		EnableControl(FALSE);
		SetStateInfo(_T("״̬����½��..."));
	}
}


void CQZoneTestDlg::OnBnClickedBtnPublic()
{
	CString strText;
	GetDlgItemText(IDC_EDIT_TEXT_PUBLIC, strText);
	if (strText.IsEmpty()) {
		MessageBox(_T("������Ҫ�������ı����ݣ�"), _T("��ʾ"));
		return;
	}

	SetStateInfo(_T("״̬��������..."));

	GetDlgItem(IDC_EDIT_TEXT_PUBLIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_IMG_PATH)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_BROWSE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_PUBLIC)->EnableWindow(FALSE);
}
