
// httptestidc3389Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "httptestidc3389.h"
#include "httptestidc3389Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Chttptestidc3389Dlg �Ի���



Chttptestidc3389Dlg::Chttptestidc3389Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_HTTPTESTIDC3389_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Chttptestidc3389Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Chttptestidc3389Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_LOGIN, &Chttptestidc3389Dlg::OnBnClickedBtnLogin)
	ON_BN_CLICKED(IDC_BTN_GET, &Chttptestidc3389Dlg::OnBnClickedBtnGet)
END_MESSAGE_MAP()


// Chttptestidc3389Dlg ��Ϣ�������

BOOL Chttptestidc3389Dlg::OnInitDialog()
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

void Chttptestidc3389Dlg::OnPaint()
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
HCURSOR Chttptestidc3389Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



BOOL	Chttptestidc3389Dlg::loginWeb(CString cstr_user, CString cstr_pass)
{
	
	//��ʼ��com��
	::CoInitialize(NULL);
	//����com����ָ��
	//IWinHttpRequestPtr Pwinhttp = NULL;
	//����com���
	HRESULT hr = Pwinhttp.CreateInstance(__uuidof(WinHttpRequest));
	if (FAILED(hr))return FALSE;
	//����վ
	hr = Pwinhttp->Open(_T("POST"), _T("http://www.idc3389.com/user/userlogin.asp"));
	if (FAILED(hr))return FALSE;
	//ƴ���ַ���
	//username=ceshi&password=password&screenwidth=&screenheight=&Submit.x=44&Submit.y=8
	CString m_setboy;
	m_setboy.Format(_T("username=%s&password=%s&screenwidth=&screenheight=&Submit.x=44&Submit.y=8"), cstr_user, cstr_pass);
	//����ͷ��Ϣ
	hr = Pwinhttp->SetRequestHeader(_T("Connection"), _T("keep-alive"));		//��ʾ���Ӵ��Ժ�HTTP�������ݵ�TCP����ر�
	hr=Pwinhttp->SetRequestHeader(_T("Content-Type"), _T("application/x-www-form-urlencoded"));		//����postt�ύ��ʽ
	if (FAILED(hr))return FALSE;
	_variant_t  varboy;
	varboy = m_setboy;
	hr=Pwinhttp->Send(varboy);
	if (FAILED(hr))return FALSE;
	//��ȡ���ص���ҳ����
	/*
	//��һ��
	_bstr_t	bstrRet = Pwinhttp->ResponseText;
	CString Cstr_ret = bstrRet;
	*/
	//�ڶ��ֿ��Ի�ȡ��GBK������ı�
	_variant_t m_vraiant;
	m_vraiant = Pwinhttp->GetResponseBody();
	ULONG dwleng = m_vraiant.parray->rgsabound[0].cElements;
	char* LPdate = (char*)m_vraiant.parray->pvData;
	CString Cstr_ret;
	Cstr_ret = LPdate;
	if (Cstr_ret.Find(_T("��ӭ��"))!=-1)
		AfxMessageBox(_T("��½�ɹ���"));
	else
		AfxMessageBox(_T("��½ʧ�ܣ�"));
	SetDlgItemText(IDC_EDIT2, Cstr_ret);
	::CoUninitialize();		//ж��com��
	return TRUE;
}
void Chttptestidc3389Dlg::OnBnClickedBtnLogin()
{
	//�Ȼ�ȡ�˺�����
	CString		m_user;
	CString		m_pass;
	GetDlgItemText(IDC_EDIT_USER, m_user);
	GetDlgItemText(IDC_EDIT_PASS, m_pass);
	//�ж��û��������Ƿ�Ϊ��
	if (m_user.IsEmpty() || m_pass.IsEmpty())AfxMessageBox(_T("�û������벻��Ϊ��!"));
	loginWeb(m_user, m_pass);
}


// ȡ�ı��м�
CString Chttptestidc3389Dlg::GetStringMiddle(CString Cstr_Source, CString Cstr_left, CString Cstr_right)
{
	CString m_Retstr;
	int m_tmplenght = Cstr_left.GetLength();
	int m_strbegin = Cstr_Source.Find(Cstr_left);			//����ı�����λ��
	if (m_strbegin!=-1)
	{
		m_strbegin += m_tmplenght;
		int m_strend = Cstr_Source.Find(Cstr_right, m_strbegin);
		if (m_strend!=-1)
		{
			m_Retstr = Cstr_Source.Mid(m_strbegin, m_strend - m_strbegin);
		}
	}
	return m_Retstr;			//����ȡ�����м��ı�
}


void Chttptestidc3389Dlg::OnBnClickedBtnGet()
{
	//��ʼ��com��
 	::CoInitialize(NULL);
// 	HRESULT hr = Pwinhttp.CreateInstance(__uuidof(WinHttpRequest));		//����com���
	
	HRESULT hr = Pwinhttp->Open(_T("GET"), _T("http://www.idc3389.com/user/modify.asp"));		//��GET��ʽ��ȡ��ҳ
	if (FAILED(hr))return;
	hr = Pwinhttp->SetRequestHeader(_T("Connection"), _T("keep-alive"));		//��ʾ���Ӵ��Ժ�HTTP�������ݵ�TCP����ر�
	if (FAILED(hr))return;
	hr = Pwinhttp->SetRequestHeader(_T("Referer"), _T("http://www.idc3389.com/user/logininfo.asp"));		//��ʾ���Ӵ��Ժ�HTTP�������ݵ�TCP����ر�
	if (FAILED(hr))return;
	hr = Pwinhttp->SetRequestHeader(_T("User-Agent"), _T("Mozilla//5.0 (Windows NT 10.0; WOW64) AppleWebKit//537.36 (KHTML, like Gecko) Chrome//50.0.2661.102 Safari//537.36"));		//��ʾ���Ӵ��Ժ�HTTP�������ݵ�TCP����ر�
	if (FAILED(hr))return;
	hr = Pwinhttp->SetRequestHeader(_T("Upgrade-Insecure-Requests"), _T("1"));		//��ʾ���Ӵ��Ժ�HTTP�������ݵ�TCP����ر�
	if (FAILED(hr))return;
	hr = Pwinhttp->SetRequestHeader(_T("Accept"), _T("text//html,application//xhtml+xml,application//xml;q=0.9,image//webp,*//*;q=0.8"));		//��ʾ���Ӵ��Ժ�HTTP�������ݵ�TCP����ر�
	if (FAILED(hr))return;
	hr = Pwinhttp->SetRequestHeader(_T("Accept-Encoding"), _T("gzip, deflate, sdch"));		//��ʾ���Ӵ��Ժ�HTTP�������ݵ�TCP����ر�
	if (FAILED(hr))return;
	//����send
	Pwinhttp->Send();
	//��ȡ��ҳ����
	_variant_t   m_source = Pwinhttp->GetResponseBody();		//��ȡ������ҳ��body����
	//ULONG  dwLenght = m_source.parray->rgsabound[0].cElements;			//��ȡ��ҳԪ�صĳ���
	char* Pcharbuf = (char*)m_source.parray->pvData;		//��ȡ��ҳ������ת���ɶ��ֽ��ַ���
	CString m_Retstr;
	m_Retstr = Pcharbuf;
	if (m_Retstr.Find(_T("����"))!=-1)
	{
		SetDlgItemText(IDC_EDIT2, _T("�����ˣ���ȡʧ�ܣ�"));
		return;
	}
	//��ʼ����
	CString m_addtext=_T("�û�����");
	m_addtext += GetStringMiddle(m_Retstr, _T("name=\"username\" type=\"hidden\" value=\""), _T("\""));		//�Ȼ�ȡ�û���
	m_addtext += _T("\n");
	m_addtext += _T("����");
	m_addtext += GetStringMiddle(m_Retstr, _T("id=\"truename\" value=\""), _T("\""));		//�Ȼ�����
	m_addtext += _T("\n");
	SetDlgItemText(IDC_EDIT2, m_addtext);
	//ж��com��
	::CoUninitialize();
}
