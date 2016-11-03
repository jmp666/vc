
// QQ_mfcDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "QQ_mfc.h"
#include "QQ_mfcDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CQQ_mfcDlg �Ի���



CQQ_mfcDlg::CQQ_mfcDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_QQ_MFC_DIALOG, pParent)
	
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CQQ_mfcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_USER, m_StrUser);	//���༭����ı����ݺ�m_struser��������
	DDX_Text(pDX, IDC_EDIT_PASS, m_StrPass);
}

BEGIN_MESSAGE_MAP(CQQ_mfcDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_LOGIN, &CQQ_mfcDlg::OnBnClickedBtnLogin)
END_MESSAGE_MAP()


// CQQ_mfcDlg ��Ϣ�������

BOOL CQQ_mfcDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	����״̬��();
	ShowWindow(SW_SHOW);

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CQQ_mfcDlg::OnPaint()
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
HCURSOR CQQ_mfcDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CQQ_mfcDlg::OnBnClickedBtnLogin()
{
	UpdateData();
	if (m_StrUser.GetLength()<5||m_StrPass.GetLength()<2)
	{
		MessageBox(_T("�˺Ż����������"), _T("��ʾ:"));
		return;
	}
	����״̬���ı�(_T("��½��......"));
	���ÿؼ�����(false);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


BOOL CQQ_mfcDlg::����״̬��()
{
	CRect rect;
	GetWindowRect(rect);	//��ȡ�����ڵ� RECT
	MoveWindow(rect.left, rect.top, rect.Width(), rect.Height() + 15);	//ֻ��Ҫ�����ڵĸ߶�����15����
	UINT array[1] = { 12301 };
	m_״̬��.Create(this);	//����״̬��
	m_״̬��.SetIndicators(array, sizeof(array) / sizeof(UINT));
	m_״̬��.SetPaneInfo(0, array[0], 0, rect.Width());
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);
	����״̬���ı�(_T("״̬:�����ɹ�!"));
	return TRUE;
}


void CQQ_mfcDlg::����״̬���ı�(PTCHAR strbuf, UINT ID)
{
	if (!strbuf||_tcslen(strbuf)<=0)
	{
		return;
	}
	m_״̬��.SetPaneText(ID, strbuf);
}


bool CQQ_mfcDlg::���ÿؼ�����(bool Flog)
{
	GetDlgItem(IDC_BTN_LOGIN)->EnableWindow(Flog);
	GetDlgItem(IDC_EDIT_PASS)->EnableWindow(Flog);
	GetDlgItem(IDC_EDIT_USER)->EnableWindow(Flog);
	GetDlgItem(IDC_EDIT_FB)->EnableWindow(Flog);
	GetDlgItem(IDC_EDIT_IMAG)->EnableWindow(Flog);
	GetDlgItem(IDC_BTN_IMAG)->EnableWindow(Flog);
	return TRUE;
}
