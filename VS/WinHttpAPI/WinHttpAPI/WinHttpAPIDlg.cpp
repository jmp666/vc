
// WinHttpAPIDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WinHttpAPI.h"
#include "WinHttpAPIDlg.h"
#include "afxdialogex.h"
//#include "WinHttpRequest.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif 


// CWinHttpAPIDlg �Ի���

//�ڶ��ֵ���com����ķ���
#import "C:\\Windows\\System32\\winhttpcom.dll" no_namespace

CWinHttpAPIDlg::CWinHttpAPIDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_WINHTTPAPI_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWinHttpAPIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CWinHttpAPIDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_1_1, &CWinHttpAPIDlg::OnBnClickedBtn11)
	ON_BN_CLICKED(IDC_BTN_1_2, &CWinHttpAPIDlg::OnBnClickedBtn12)
	ON_BN_CLICKED(IDC_BTN_CLEAR, &CWinHttpAPIDlg::OnBnClickedBtnClear)
	ON_BN_CLICKED(IDC_BTN_1_4, &CWinHttpAPIDlg::OnBnClickedBtn14)
	ON_BN_CLICKED(IDC_BTN_1_5, &CWinHttpAPIDlg::OnBnClickedBtn15)
END_MESSAGE_MAP()


// CWinHttpAPIDlg ��Ϣ�������

BOOL CWinHttpAPIDlg::OnInitDialog()
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

void CWinHttpAPIDlg::OnPaint()
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
HCURSOR CWinHttpAPIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CWinHttpAPIDlg::OnBnClickedBtn11()
{
	/*
	//��ȡ��ҳԴ��Ĳ��裺
	//	1��COM�����ʼ����
	::CoInitialize(NULL);
	//	2������WinHttp����ָ�룻
	CWinHttpRequest* Pwinhttp = new CWinHttpRequest;
	//	3��������ʵ����WinHttp�����
	CLSID clsid = { 0 };		//com�����ID(�ӿ�ID)
	HRESULT  hreuslt = ::CLSIDFromProgID(_T("WinHttp.WinHttpRequest.5.1"),&clsid);
	if (S_OK != hreuslt) return;		//�����ȡ���ǿ��õ�CLSID�ͷ���
	BOOL bRet = Pwinhttp->CreateDispatch(clsid);
	if (!bRet)return;
	//	4������Open���������ӣ�
	COleVariant  variant = VARIANT_FALSE;
	Pwinhttp->Open(_T("GET"), _T("http://bbs.125.la/"), variant);
	//	5������Send������������
	Pwinhttp->Send(vtMissing);
	//	6����ȡResponseText���ص��ı���
	CString strRet;
	strRet = Pwinhttp->get_ResponseText();
	GetDlgItem(IDC_EDIT1)->SetWindowText(strRet);
	//	7���ͷ�WinHttp�������
	Pwinhttp->ReleaseDispatch();
	//	8���ͷ�WinHttp����ָ�룻
	delete Pwinhttp;
	//	9��ж��COM�����
	::CoUninitialize();
	*/
}


void CWinHttpAPIDlg::OnBnClickedBtn12()
{
	/*
	//��һ�ַ���
	//��ȡ��ҳԴ��Ĳ��裺
	//	1��COM�����ʼ����
	::CoInitialize(NULL);
	//	2������WinHttp����ָ�룻
	CWinHttpRequest* Pwinhttp = new CWinHttpRequest;
	//	3��������ʵ����WinHttp�����
	CLSID clsid = { 0 };		//com�����ID(�ӿ�ID)
	HRESULT  hreuslt = ::CLSIDFromProgID(_T("WinHttp.WinHttpRequest.5.1"), &clsid);
	if (S_OK != hreuslt) return;		//�����ȡ���ǿ��õ�CLSID�ͷ���
	BOOL bRet = Pwinhttp->CreateDispatch(clsid);
	if (!bRet)return;
	//	4������Open���������ӣ�
	COleVariant  variant = VARIANT_FALSE;
	Pwinhttp->Open(_T("GET"), _T("http://bbs.125.la/"), variant);
	//	5������Send������������
	Pwinhttp->Send(vtMissing);
	//	6����ȡResponseText���ص��ı���
	CString strRet;
	strRet = Pwinhttp->GetAllResponseHeaders();
	GetDlgItem(IDC_EDIT1)->SetWindowText(strRet);
	//	7���ͷ�WinHttp�������
	Pwinhttp->ReleaseDispatch();
	//	8���ͷ�WinHttp����ָ�룻
	delete Pwinhttp;
	//	9��ж��COM�����
	::CoUninitialize();
	*/


	//�ڶ��ַ���
	//COM�����ʼ��
	::CoInitialize(NULL);
	IWinHttpRequest* m_Winhttp = NULL;			//����WinHttp����ָ��
												//������ʵ����WinHttp���
	HRESULT  hr = ::CoCreateInstance(__uuidof(WinHttpRequest), NULL, CLSCTX_ALL, __uuidof(IWinHttpRequest), (LPVOID*)&m_Winhttp);
	if (FAILED(hr))		//�������ֵ����0��ʧ����
	{
		return;
	}
	//����Open����������
	hr = m_Winhttp->Open(_T("GET"), _T("http://bbs.125.la/"));
	if (FAILED(hr))
	{
		m_Winhttp->Release();		//�ͷ�com����ָ��
		::CoUninitialize();					//ж��com���
		return;
	}
	//Ȼ�����send
	hr = m_Winhttp->Send();
	if (FAILED(hr))
	{
		m_Winhttp->Release();		//�ͷ�com����ָ��
		::CoUninitialize();					//ж��com���
		return;
	}
	//��ȡ��ҳ����
	_bstr_t  bStr_ret = m_Winhttp->GetAllResponseHeaders();
	CString m_cstr = bStr_ret;
	GetDlgItem(IDC_EDIT1)->SetWindowText(m_cstr);
	//Ȼ���ͷŶ���ָ��ж��com���
	m_Winhttp->Release();		//�ͷ�com����ָ��
	::CoUninitialize();					//ж��com���
}


void CWinHttpAPIDlg::OnBnClickedBtnClear()
{
	GetDlgItem(IDC_EDIT1)->SetWindowText(_T(""));
}


void CWinHttpAPIDlg::OnBnClickedBtn14()
{
	//COM�����ʼ��
	::CoInitialize(NULL);
	IWinHttpRequest* m_Winhttp = NULL;			//����WinHttp����ָ��
	//������ʵ����WinHttp���
	HRESULT  hr = ::CoCreateInstance(__uuidof(WinHttpRequest), NULL, CLSCTX_ALL, __uuidof(IWinHttpRequest), (LPVOID*)&m_Winhttp);
	if (FAILED(hr))		//�������ֵ����0��ʧ����
	{
		return;
	}
	//����Open����������
	hr = m_Winhttp->Open(_T("GET"), _T("http://bbs.125.la/"));
	if (FAILED(hr))
	{
		m_Winhttp->Release();		//�ͷ�com����ָ��
		::CoUninitialize();					//ж��com���
		return;
	}
	//Ȼ�����send
	hr = m_Winhttp->Send();
	if (FAILED(hr))
	{
		m_Winhttp->Release();		//�ͷ�com����ָ��
		::CoUninitialize();					//ж��com���
		return;
	}
	//��ȡ��ҳ����
	_bstr_t  bStr_ret = m_Winhttp->ResponseText;
	CString m_cstr = bStr_ret;
	GetDlgItem(IDC_EDIT1)->SetWindowText(m_cstr);
	//Ȼ���ͷŶ���ָ��ж��com���
	m_Winhttp->Release();		//�ͷ�com����ָ��
	::CoUninitialize();					//ж��com���
}


void CWinHttpAPIDlg::OnBnClickedBtn15()
{

	::CoInitialize(NULL);		//��ʼ��com��
	//����com����ָ��
	IWinHttpRequestPtr PhttpObj = NULL;			//����ָ�뷽ʽ����
	HRESULT hr = PhttpObj.CreateInstance(__uuidof(WinHttpRequest));
	if (FAILED(hr))return;
	//��open��
	hr = PhttpObj->Open(_T("GET"), _T("http://www.hao123.com/"));
	if (FAILED(hr))return;
	//��ʼsend
	PhttpObj->Send();
	_bstr_t	bstr_ret = PhttpObj->ResponseText;			//��ȡ��ҳ����
	CString	m_cstr = bstr_ret;
	GetDlgItem(IDC_EDIT1)->SetWindowText(m_cstr);
	//��Ϊ������ָ�����Բ���Ҫ�����ֶ����� PhttpObj->Release(); �����Լ�ж��
	::CoUninitialize();		//ж��com��

}
