
// HttpTestJiaidcDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HttpTestJiaidc.h"
#include "HttpTestJiaidcDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHttpTestJiaidcDlg �Ի���



CHttpTestJiaidcDlg::CHttpTestJiaidcDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_HTTPTESTJIAIDC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHttpTestJiaidcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CHttpTestJiaidcDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_GETVCODE, &CHttpTestJiaidcDlg::OnBnClickedBtnGetvcode)
	ON_BN_CLICKED(IDC_BTN_LOGIN, &CHttpTestJiaidcDlg::OnBnClickedBtnLogin)
END_MESSAGE_MAP()


// CHttpTestJiaidcDlg ��Ϣ�������

BOOL CHttpTestJiaidcDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CHttpTestJiaidcDlg::OnPaint()
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
HCURSOR CHttpTestJiaidcDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CHttpTestJiaidcDlg::OnBnClickedBtnGetvcode()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	::CoInitialize(NULL);
	HRESULT hr = LPhttp.CreateInstance(__uuidof(WinHttpRequest));
	if (FAILED(hr))
	{
		return;
	}
	hr=LPhttp->Open(_T("GET"), _T("http://bl.shishicaicp.net/index.php/user/vcode/1476105386973"));
	if (FAILED(hr))return;
	LPhttp->Send();
	_variant_t  m_Respon;
	m_Respon = LPhttp->GetResponseBody();
	ULONG	  dwLenght = m_Respon.parray->rgsabound[0].cElements;
	PCHAR  PcharBuf = (PCHAR)m_Respon.parray->pvData;
	CImage	  img;
	if (PcharBuf)
	{
		CStatic	*m_Bitmap = (CStatic*)GetDlgItem(IDC_STATIC_VCODE);
		if (LodcomImage(PcharBuf, dwLenght, img))
		{
			if (m_Bitmap)
			{
				HBITMAP	Retbitmap = m_Bitmap->SetBitmap(img.Detach());
				DeleteObject(Retbitmap);		//ɾ����ǰ�Ķ�����
			}
		}
	}
	//::CoUninitialize();
}


// ��������ͼƬ��CImage����
BOOL CHttpTestJiaidcDlg::LodcomImage(LPVOID PmemIm, ULONG dwLen, CImage& ImgObj)
{
	LPVOID	  m_ImageBuf = NULL;
	BOOL bRet = FALSE;
	HGLOBAL	 Hglobal = ::GlobalAlloc(GMEM_MOVEABLE, dwLen);
	if (!Hglobal)
	{
		return bRet;
	}
	m_ImageBuf = ::GlobalLock(Hglobal);			//����ȫ�ַ�����ڴ�Ȼ����
	memset(m_ImageBuf, 0, dwLen);
	memcpy(m_ImageBuf, PmemIm,dwLen);
	::GlobalUnlock(Hglobal);		//�������
	IStream	 *Pstream = NULL;
	HRESULT hr = ::CreateStreamOnHGlobal(Hglobal, TRUE, &Pstream);
	if (FAILED(hr))return bRet;
	hr=ImgObj.Load(Pstream);
	if (FAILED(hr))return bRet;
	Pstream->Release();
	bRet = TRUE;
	::GlobalFree(Hglobal);		//�ͷ�ȫ���ڴ�����
	return bRet;
}


void CHttpTestJiaidcDlg::OnBnClickedBtnLogin()
{
	LPhttp->Open(_T("POST"), _T("http://bl.shishicaicp.net/index.php/user/logined "));
	CString	 m_SendBoy;
	//username=ceshi&password=123456&vcode=1341
	CString m_user;
	CString m_pass;
	CString m_vcode;
	GetDlgItemText(IDC_EDIT_USER, m_user);
	GetDlgItemText(IDC_EDIT_PASS, m_pass);
	GetDlgItemText(IDC_EDIT_VCODE, m_vcode);
	m_SendBoy.Format(_T("username=%s&password=%s&vcode=%s"), m_user, m_pass, m_vcode);
	//����Э��ͷ
	LPhttp->SetRequestHeader(_T("Content-Type"), _T("application/x-www-form-urlencoded; charset=UTF-8"));
	LPhttp->SetRequestHeader(_T("Referer"), _T("http://bl.shishicaicp.net/index.php/user/login"));
	//����
	_variant_t  Async;
	Async = m_SendBoy;
	LPhttp->Send(Async);
	//���շ�������
	_variant_t  m_RequestBoy;
	m_RequestBoy = LPhttp->GetResponseBody();
// 	ULONG  dwLen = NULL;
// 	dwLen = m_RequestBoy.parray->rgsabound[0].cElements;
	if (!m_RequestBoy.parray)
	{
		::CoUninitialize();
		return;
	}
	PCHAR	 PcharBuf = (PCHAR)m_RequestBoy.parray->pvData;
	CString m_Retstr;
	m_Retstr = PcharBuf;
	::CoUninitialize();
}
