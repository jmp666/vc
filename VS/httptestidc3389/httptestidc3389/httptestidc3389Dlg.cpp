
// httptestidc3389Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "httptestidc3389.h"
#include "httptestidc3389Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Chttptestidc3389Dlg 对话框



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


// Chttptestidc3389Dlg 消息处理程序

BOOL Chttptestidc3389Dlg::OnInitDialog()
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

void Chttptestidc3389Dlg::OnPaint()
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
HCURSOR Chttptestidc3389Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



BOOL	Chttptestidc3389Dlg::loginWeb(CString cstr_user, CString cstr_pass)
{
	
	//初始化com库
	::CoInitialize(NULL);
	//创建com对象指针
	//IWinHttpRequestPtr Pwinhttp = NULL;
	//创建com组件
	HRESULT hr = Pwinhttp.CreateInstance(__uuidof(WinHttpRequest));
	if (FAILED(hr))return FALSE;
	//打开网站
	hr = Pwinhttp->Open(_T("POST"), _T("http://www.idc3389.com/user/userlogin.asp"));
	if (FAILED(hr))return FALSE;
	//拼接字符串
	//username=ceshi&password=password&screenwidth=&screenheight=&Submit.x=44&Submit.y=8
	CString m_setboy;
	m_setboy.Format(_T("username=%s&password=%s&screenwidth=&screenheight=&Submit.x=44&Submit.y=8"), cstr_user, cstr_pass);
	//设置头信息
	hr = Pwinhttp->SetRequestHeader(_T("Connection"), _T("keep-alive"));		//表示链接打开以后HTTP传输数据的TCP不会关闭
	hr=Pwinhttp->SetRequestHeader(_T("Content-Type"), _T("application/x-www-form-urlencoded"));		//设置postt提交方式
	if (FAILED(hr))return FALSE;
	_variant_t  varboy;
	varboy = m_setboy;
	hr=Pwinhttp->Send(varboy);
	if (FAILED(hr))return FALSE;
	//获取返回的网页内容
	/*
	//第一种
	_bstr_t	bstrRet = Pwinhttp->ResponseText;
	CString Cstr_ret = bstrRet;
	*/
	//第二种可以获取到GBK编码的文本
	_variant_t m_vraiant;
	m_vraiant = Pwinhttp->GetResponseBody();
	ULONG dwleng = m_vraiant.parray->rgsabound[0].cElements;
	char* LPdate = (char*)m_vraiant.parray->pvData;
	CString Cstr_ret;
	Cstr_ret = LPdate;
	if (Cstr_ret.Find(_T("欢迎您"))!=-1)
		AfxMessageBox(_T("登陆成功！"));
	else
		AfxMessageBox(_T("登陆失败！"));
	SetDlgItemText(IDC_EDIT2, Cstr_ret);
	::CoUninitialize();		//卸载com库
	return TRUE;
}
void Chttptestidc3389Dlg::OnBnClickedBtnLogin()
{
	//先获取账号密码
	CString		m_user;
	CString		m_pass;
	GetDlgItemText(IDC_EDIT_USER, m_user);
	GetDlgItemText(IDC_EDIT_PASS, m_pass);
	//判断用户名密码是否为空
	if (m_user.IsEmpty() || m_pass.IsEmpty())AfxMessageBox(_T("用户名密码不能为空!"));
	loginWeb(m_user, m_pass);
}


// 取文本中间
CString Chttptestidc3389Dlg::GetStringMiddle(CString Cstr_Source, CString Cstr_left, CString Cstr_right)
{
	CString m_Retstr;
	int m_tmplenght = Cstr_left.GetLength();
	int m_strbegin = Cstr_Source.Find(Cstr_left);			//左边文本所在位置
	if (m_strbegin!=-1)
	{
		m_strbegin += m_tmplenght;
		int m_strend = Cstr_Source.Find(Cstr_right, m_strbegin);
		if (m_strend!=-1)
		{
			m_Retstr = Cstr_Source.Mid(m_strbegin, m_strend - m_strbegin);
		}
	}
	return m_Retstr;			//返回取出的中间文本
}


void Chttptestidc3389Dlg::OnBnClickedBtnGet()
{
	//初始化com库
 	::CoInitialize(NULL);
// 	HRESULT hr = Pwinhttp.CreateInstance(__uuidof(WinHttpRequest));		//创建com组件
	
	HRESULT hr = Pwinhttp->Open(_T("GET"), _T("http://www.idc3389.com/user/modify.asp"));		//用GET方式获取网页
	if (FAILED(hr))return;
	hr = Pwinhttp->SetRequestHeader(_T("Connection"), _T("keep-alive"));		//表示链接打开以后HTTP传输数据的TCP不会关闭
	if (FAILED(hr))return;
	hr = Pwinhttp->SetRequestHeader(_T("Referer"), _T("http://www.idc3389.com/user/logininfo.asp"));		//表示链接打开以后HTTP传输数据的TCP不会关闭
	if (FAILED(hr))return;
	hr = Pwinhttp->SetRequestHeader(_T("User-Agent"), _T("Mozilla//5.0 (Windows NT 10.0; WOW64) AppleWebKit//537.36 (KHTML, like Gecko) Chrome//50.0.2661.102 Safari//537.36"));		//表示链接打开以后HTTP传输数据的TCP不会关闭
	if (FAILED(hr))return;
	hr = Pwinhttp->SetRequestHeader(_T("Upgrade-Insecure-Requests"), _T("1"));		//表示链接打开以后HTTP传输数据的TCP不会关闭
	if (FAILED(hr))return;
	hr = Pwinhttp->SetRequestHeader(_T("Accept"), _T("text//html,application//xhtml+xml,application//xml;q=0.9,image//webp,*//*;q=0.8"));		//表示链接打开以后HTTP传输数据的TCP不会关闭
	if (FAILED(hr))return;
	hr = Pwinhttp->SetRequestHeader(_T("Accept-Encoding"), _T("gzip, deflate, sdch"));		//表示链接打开以后HTTP传输数据的TCP不会关闭
	if (FAILED(hr))return;
	//发送send
	Pwinhttp->Send();
	//获取网页内容
	_variant_t   m_source = Pwinhttp->GetResponseBody();		//获取整个网页的body内容
	//ULONG  dwLenght = m_source.parray->rgsabound[0].cElements;			//获取网页元素的长度
	char* Pcharbuf = (char*)m_source.parray->pvData;		//获取网页的内容转换成多字节字符集
	CString m_Retstr;
	m_Retstr = Pcharbuf;
	if (m_Retstr.Find(_T("出错"))!=-1)
	{
		SetDlgItemText(IDC_EDIT2, _T("出错了！获取失败！"));
		return;
	}
	//开始查找
	CString m_addtext=_T("用户名：");
	m_addtext += GetStringMiddle(m_Retstr, _T("name=\"username\" type=\"hidden\" value=\""), _T("\""));		//先获取用户名
	m_addtext += _T("\n");
	m_addtext += _T("姓名");
	m_addtext += GetStringMiddle(m_Retstr, _T("id=\"truename\" value=\""), _T("\""));		//先获姓名
	m_addtext += _T("\n");
	SetDlgItemText(IDC_EDIT2, m_addtext);
	//卸载com库
	::CoUninitialize();
}
