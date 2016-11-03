
// HttptestIDC816Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "HttptestIDC816.h"
#include "HttptestIDC816Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CHttptestIDC816Dlg 对话框



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


// CHttptestIDC816Dlg 消息处理程序

BOOL CHttptestIDC816Dlg::OnInitDialog()
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

void CHttptestIDC816Dlg::OnPaint()
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
HCURSOR CHttptestIDC816Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CHttptestIDC816Dlg::OnBnClickedBtnLogin()
{
	//初始化com库
	::CoInitialize(NULL);
	//创建com组件对象
	HRESULT	hr = Phttp.CreateInstance(__uuidof(WinHttpRequest));
	if (FAILED(hr))return;
	//调用send
	hr=Phttp->Open(_T("POST"), _T("http://www.idc816.com/chklogin.asp"));
	if (FAILED(hr))return;
	//调用send
	//u_name=ceshi256&u_password=pass123&imageField.x=38&imageField.y=13
	CString m_sendboy;
	CString m_user;				//账号
	CString m_pass;			//密码
	GetDlgItemText(IDC_EDIT1, m_user);
	GetDlgItemText(IDC_EDIT2, m_pass);
	m_sendboy.Format(_T("u_name=%s&u_password=%s&imageField.x=38&imageField.y=13"), m_user, m_pass);
	//协议头
	hr=Phttp->SetRequestHeader(_T("Content-Type"), _T("Content-Type: application/x-www-form-urlencoded"));
	if (FAILED(hr))return;
	hr = Phttp->SetRequestHeader(_T("Connection"), _T("keep-alive"));
	if (FAILED(hr))return;
	hr = Phttp->SetRequestHeader(_T("Referer"), _T("http://www.idc816.com/default.asp"));
	if (FAILED(hr))return;
	//设置禁止重定向
// 	_variant_t		value = VARIANT_FALSE;		//第一种禁止重定向方法
// 	hr = Phttp->put_Option(WinHttpRequestOption_EnableRedirects, value);			//静止重定向
	Phttp->Option[WinHttpRequestOption_EnableRedirects] = VARIANT_FALSE;			//第二种禁止重定向方法
	//if (FAILED(hr))return;
	//send
	_variant_t Sendboy;
	Sendboy = m_sendboy;
	hr = Phttp->Send(Sendboy);
	if (FAILED(hr))return;
	//获取返回的协议头
	_bstr_t	m_bstr_headers;
	m_bstr_headers = Phttp->GetAllResponseHeaders();
	CString m_cstr_headers = m_bstr_headers;
	//处理cookie
	CString m_Retcookie = DisposeCookie(m_cstr_headers);
	SetDlgItemText(IDC_EDIT_GETCOOKIE, m_Retcookie);
	//接收返回值
	/*_bstr_t  bstr_Ret = Phttp->ResponseText;*/
	_variant_t  m_ResponseBody;
	m_ResponseBody = Phttp->GetResponseBody();
	ULONG  dwLenght = m_ResponseBody.parray->rgsabound[0].cElements;
	char* PcharBuf = (char*)m_ResponseBody.parray->pvData;
	CString m_str_Ret;
	m_str_Ret = PcharBuf;
	//卸载com库
	::CoUninitialize();
}


void CHttptestIDC816Dlg::OnBnClickedButton1()
{
	::CoInitialize(NULL);
	HRESULT	hr=	Phttp.CreateInstance(__uuidof(WinHttpRequest));
	if (FAILED(hr))return;
	hr=Phttp->Open(_T("GET"), _T("http://www.idc816.com/manager/usermanager/default2.asp"));
	if (FAILED(hr))return;
	//开始设置协议头
	CString m_strcookie;
	GetDlgItemText(IDC_EDIT_SETCOOKIE, m_strcookie);
	if(m_strcookie.GetLength()>0)
	hr = Phttp->SetRequestHeader(_T("cookie"), m_strcookie.AllocSysString());
	if (FAILED(hr))return;
	//发送send
	hr = Phttp->Send();
	if (FAILED(hr))return;
	//接收返回的网页内容
	_variant_t	m_Retboy;
	m_Retboy = Phttp->GetResponseBody();
	ULONG	 dwlenght = m_Retboy.parray->rgsabound[0].cElements;
	PCHAR	PcharBuf = (PCHAR)m_Retboy.parray->pvData;
	CString m_RetText;
	m_RetText = PcharBuf;
	::CoUninitialize();
}


// 整理cookie并返回
CString CHttptestIDC816Dlg::DisposeCookie(CString StringText)
{
	CString m_RetCookile;
	CString m_FindStr = _T("Set-Cookie: ");
	if (StringText.IsEmpty())return m_RetCookile;		//如果是空就返回
	int m_begin = 0, m_end = 0;			//定义开始和结尾
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
