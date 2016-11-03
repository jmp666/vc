
// HttptestIDC816Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HttptestIDC816.h"
#include "HttptestIDC816Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CHttptestIDC816Dlg �Ի���



CHttptestIDC816Dlg::CHttptestIDC816Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_HTTPTESTIDC816_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHttptestIDC816Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CHttptestIDC816Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_LOGIN, &CHttptestIDC816Dlg::OnBnClickedBtnLogin)
	ON_BN_CLICKED(IDC_BUTTON1, &CHttptestIDC816Dlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CHttptestIDC816Dlg ��Ϣ�������

BOOL CHttptestIDC816Dlg::OnInitDialog()
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

void CHttptestIDC816Dlg::OnPaint()
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
HCURSOR CHttptestIDC816Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CHttptestIDC816Dlg::OnBnClickedBtnLogin()
{
	//��ʼ��com��
	::CoInitialize(NULL);
	//����com�������
	HRESULT	hr = Phttp.CreateInstance(__uuidof(WinHttpRequest));
	if (FAILED(hr))return;
	//����send
	hr=Phttp->Open(_T("POST"), _T("http://www.idc816.com/chklogin.asp"));
	if (FAILED(hr))return;
	//����send
	//u_name=ceshi256&u_password=pass123&imageField.x=38&imageField.y=13
	CString m_sendboy;
	CString m_user;				//�˺�
	CString m_pass;			//����
	GetDlgItemText(IDC_EDIT1, m_user);
	GetDlgItemText(IDC_EDIT2, m_pass);
	m_sendboy.Format(_T("u_name=%s&u_password=%s&imageField.x=38&imageField.y=13"), m_user, m_pass);
	//Э��ͷ
	hr=Phttp->SetRequestHeader(_T("Content-Type"), _T("Content-Type: application/x-www-form-urlencoded"));
	if (FAILED(hr))return;
	hr = Phttp->SetRequestHeader(_T("Connection"), _T("keep-alive"));
	if (FAILED(hr))return;
	hr = Phttp->SetRequestHeader(_T("Referer"), _T("http://www.idc816.com/default.asp"));
	if (FAILED(hr))return;
	//���ý�ֹ�ض���
// 	_variant_t		value = VARIANT_FALSE;		//��һ�ֽ�ֹ�ض��򷽷�
// 	hr = Phttp->put_Option(WinHttpRequestOption_EnableRedirects, value);			//��ֹ�ض���
	Phttp->Option[WinHttpRequestOption_EnableRedirects] = VARIANT_FALSE;			//�ڶ��ֽ�ֹ�ض��򷽷�
	//if (FAILED(hr))return;
	//send
	_variant_t Sendboy;
	Sendboy = m_sendboy;
	hr = Phttp->Send(Sendboy);
	if (FAILED(hr))return;
	//��ȡ���ص�Э��ͷ
	_bstr_t	m_bstr_headers;
	m_bstr_headers = Phttp->GetAllResponseHeaders();
	CString m_cstr_headers = m_bstr_headers;
	//����cookie
	CString m_Retcookie = DisposeCookie(m_cstr_headers);
	SetDlgItemText(IDC_EDIT_GETCOOKIE, m_Retcookie);
	//���շ���ֵ
	/*_bstr_t  bstr_Ret = Phttp->ResponseText;*/
	_variant_t  m_ResponseBody;
	m_ResponseBody = Phttp->GetResponseBody();
	ULONG  dwLenght = m_ResponseBody.parray->rgsabound[0].cElements;
	char* PcharBuf = (char*)m_ResponseBody.parray->pvData;
	CString m_str_Ret;
	m_str_Ret = PcharBuf;
	//ж��com��
	::CoUninitialize();
}


void CHttptestIDC816Dlg::OnBnClickedButton1()
{
	::CoInitialize(NULL);
	HRESULT	hr=	Phttp.CreateInstance(__uuidof(WinHttpRequest));
	if (FAILED(hr))return;
	hr=Phttp->Open(_T("GET"), _T("http://www.idc816.com/manager/usermanager/default2.asp"));
	if (FAILED(hr))return;
	//��ʼ����Э��ͷ
	CString m_strcookie;
	GetDlgItemText(IDC_EDIT_SETCOOKIE, m_strcookie);
	if(m_strcookie.GetLength()>0)
	hr = Phttp->SetRequestHeader(_T("cookie"), m_strcookie.AllocSysString());
	if (FAILED(hr))return;
	//����send
	hr = Phttp->Send();
	if (FAILED(hr))return;
	//���շ��ص���ҳ����
	_variant_t	m_Retboy;
	m_Retboy = Phttp->GetResponseBody();
	ULONG	 dwlenght = m_Retboy.parray->rgsabound[0].cElements;
	PCHAR	PcharBuf = (PCHAR)m_Retboy.parray->pvData;
	CString m_RetText;
	m_RetText = PcharBuf;
	::CoUninitialize();
}


// ����cookie������
CString CHttptestIDC816Dlg::DisposeCookie(CString StringText)
{
	CString m_RetCookile;
	CString m_FindStr = _T("Set-Cookie: ");
	if (StringText.IsEmpty())return m_RetCookile;		//����ǿվͷ���
	int m_begin = 0, m_end = 0;			//���忪ʼ�ͽ�β
	while (m_begin<StringText.GetLength())
	{
		m_begin = StringText.Find(m_FindStr, m_end);
		if (m_begin>0)
		{
			m_end = StringText.Find(_T("\r\n"), m_begin);
			if (m_end >m_begin)
			{
				m_RetCookile += StringText.Mid(m_begin+ m_FindStr.GetLength(),m_end - (m_begin+ m_FindStr.GetLength())-wcslen(_T(" path=/")));
				m_RetCookile += _T(" ");
			}
		}
		else
		{
			break;
		}
	}
	m_RetCookile.Delete(m_RetCookile.GetLength()-2, 2);
	return m_RetCookile;
}
