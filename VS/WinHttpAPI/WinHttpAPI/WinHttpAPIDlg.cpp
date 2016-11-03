
// WinHttpAPIDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "WinHttpAPI.h"
#include "WinHttpAPIDlg.h"
#include "afxdialogex.h"
//#include "WinHttpRequest.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif 


// CWinHttpAPIDlg 对话框

//第二种调用com组件的方法
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


// CWinHttpAPIDlg 消息处理程序

BOOL CWinHttpAPIDlg::OnInitDialog()
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

void CWinHttpAPIDlg::OnPaint()
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
HCURSOR CWinHttpAPIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CWinHttpAPIDlg::OnBnClickedBtn11()
{
	/*
	//获取网页源码的步骤：
	//	1、COM组件初始化；
	::CoInitialize(NULL);
	//	2、定义WinHttp对象指针；
	CWinHttpRequest* Pwinhttp = new CWinHttpRequest;
	//	3、创建并实例化WinHttp组件；
	CLSID clsid = { 0 };		//com组件类ID(接口ID)
	HRESULT  hreuslt = ::CLSIDFromProgID(_T("WinHttp.WinHttpRequest.5.1"),&clsid);
	if (S_OK != hreuslt) return;		//如果获取不是可用的CLSID就返回
	BOOL bRet = Pwinhttp->CreateDispatch(clsid);
	if (!bRet)return;
	//	4、调用Open方法打开连接；
	COleVariant  variant = VARIANT_FALSE;
	Pwinhttp->Open(_T("GET"), _T("http://bbs.125.la/"), variant);
	//	5、调用Send方法发送请求；
	Pwinhttp->Send(vtMissing);
	//	6、获取ResponseText返回的文本；
	CString strRet;
	strRet = Pwinhttp->get_ResponseText();
	GetDlgItem(IDC_EDIT1)->SetWindowText(strRet);
	//	7、释放WinHttp组件对象；
	Pwinhttp->ReleaseDispatch();
	//	8、释放WinHttp对象指针；
	delete Pwinhttp;
	//	9、卸载COM组件；
	::CoUninitialize();
	*/
}


void CWinHttpAPIDlg::OnBnClickedBtn12()
{
	/*
	//第一种方法
	//获取网页源码的步骤：
	//	1、COM组件初始化；
	::CoInitialize(NULL);
	//	2、定义WinHttp对象指针；
	CWinHttpRequest* Pwinhttp = new CWinHttpRequest;
	//	3、创建并实例化WinHttp组件；
	CLSID clsid = { 0 };		//com组件类ID(接口ID)
	HRESULT  hreuslt = ::CLSIDFromProgID(_T("WinHttp.WinHttpRequest.5.1"), &clsid);
	if (S_OK != hreuslt) return;		//如果获取不是可用的CLSID就返回
	BOOL bRet = Pwinhttp->CreateDispatch(clsid);
	if (!bRet)return;
	//	4、调用Open方法打开连接；
	COleVariant  variant = VARIANT_FALSE;
	Pwinhttp->Open(_T("GET"), _T("http://bbs.125.la/"), variant);
	//	5、调用Send方法发送请求；
	Pwinhttp->Send(vtMissing);
	//	6、获取ResponseText返回的文本；
	CString strRet;
	strRet = Pwinhttp->GetAllResponseHeaders();
	GetDlgItem(IDC_EDIT1)->SetWindowText(strRet);
	//	7、释放WinHttp组件对象；
	Pwinhttp->ReleaseDispatch();
	//	8、释放WinHttp对象指针；
	delete Pwinhttp;
	//	9、卸载COM组件；
	::CoUninitialize();
	*/


	//第二种方法
	//COM组件初始化
	::CoInitialize(NULL);
	IWinHttpRequest* m_Winhttp = NULL;			//定义WinHttp对象指针
												//创建并实例化WinHttp组件
	HRESULT  hr = ::CoCreateInstance(__uuidof(WinHttpRequest), NULL, CLSCTX_ALL, __uuidof(IWinHttpRequest), (LPVOID*)&m_Winhttp);
	if (FAILED(hr))		//如果返回值不是0就失败了
	{
		return;
	}
	//调用Open方法打开连接
	hr = m_Winhttp->Open(_T("GET"), _T("http://bbs.125.la/"));
	if (FAILED(hr))
	{
		m_Winhttp->Release();		//释放com对象指针
		::CoUninitialize();					//卸载com组件
		return;
	}
	//然后调用send
	hr = m_Winhttp->Send();
	if (FAILED(hr))
	{
		m_Winhttp->Release();		//释放com对象指针
		::CoUninitialize();					//卸载com组件
		return;
	}
	//获取网页内容
	_bstr_t  bStr_ret = m_Winhttp->GetAllResponseHeaders();
	CString m_cstr = bStr_ret;
	GetDlgItem(IDC_EDIT1)->SetWindowText(m_cstr);
	//然后释放对象指针卸载com组件
	m_Winhttp->Release();		//释放com对象指针
	::CoUninitialize();					//卸载com组件
}


void CWinHttpAPIDlg::OnBnClickedBtnClear()
{
	GetDlgItem(IDC_EDIT1)->SetWindowText(_T(""));
}


void CWinHttpAPIDlg::OnBnClickedBtn14()
{
	//COM组件初始化
	::CoInitialize(NULL);
	IWinHttpRequest* m_Winhttp = NULL;			//定义WinHttp对象指针
	//创建并实例化WinHttp组件
	HRESULT  hr = ::CoCreateInstance(__uuidof(WinHttpRequest), NULL, CLSCTX_ALL, __uuidof(IWinHttpRequest), (LPVOID*)&m_Winhttp);
	if (FAILED(hr))		//如果返回值不是0就失败了
	{
		return;
	}
	//调用Open方法打开连接
	hr = m_Winhttp->Open(_T("GET"), _T("http://bbs.125.la/"));
	if (FAILED(hr))
	{
		m_Winhttp->Release();		//释放com对象指针
		::CoUninitialize();					//卸载com组件
		return;
	}
	//然后调用send
	hr = m_Winhttp->Send();
	if (FAILED(hr))
	{
		m_Winhttp->Release();		//释放com对象指针
		::CoUninitialize();					//卸载com组件
		return;
	}
	//获取网页内容
	_bstr_t  bStr_ret = m_Winhttp->ResponseText;
	CString m_cstr = bStr_ret;
	GetDlgItem(IDC_EDIT1)->SetWindowText(m_cstr);
	//然后释放对象指针卸载com组件
	m_Winhttp->Release();		//释放com对象指针
	::CoUninitialize();					//卸载com组件
}


void CWinHttpAPIDlg::OnBnClickedBtn15()
{

	::CoInitialize(NULL);		//初始化com库
	//定义com对象指针
	IWinHttpRequestPtr PhttpObj = NULL;			//智能指针方式调用
	HRESULT hr = PhttpObj.CreateInstance(__uuidof(WinHttpRequest));
	if (FAILED(hr))return;
	//用open打开
	hr = PhttpObj->Open(_T("GET"), _T("http://www.hao123.com/"));
	if (FAILED(hr))return;
	//开始send
	PhttpObj->Send();
	_bstr_t	bstr_ret = PhttpObj->ResponseText;			//获取网页内容
	CString	m_cstr = bstr_ret;
	GetDlgItem(IDC_EDIT1)->SetWindowText(m_cstr);
	//因为是智能指针所以不需要我们手动调用 PhttpObj->Release(); 它会自己卸载
	::CoUninitialize();		//卸载com库

}
