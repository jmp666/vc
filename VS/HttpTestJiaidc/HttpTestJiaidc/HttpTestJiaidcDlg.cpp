
// HttpTestJiaidcDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "HttpTestJiaidc.h"
#include "HttpTestJiaidcDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHttpTestJiaidcDlg 对话框



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


// CHttpTestJiaidcDlg 消息处理程序

BOOL CHttpTestJiaidcDlg::OnInitDialog()
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

void CHttpTestJiaidcDlg::OnPaint()
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
HCURSOR CHttpTestJiaidcDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CHttpTestJiaidcDlg::OnBnClickedBtnGetvcode()
{
	// TODO: 在此添加控件通知处理程序代码
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
				DeleteObject(Retbitmap);		//删除以前的对象句柄
			}
		}
	}
	//::CoUninitialize();
}


// 加载网络图片到CImage对象
BOOL CHttpTestJiaidcDlg::LodcomImage(LPVOID PmemIm, ULONG dwLen, CImage& ImgObj)
{
	LPVOID	  m_ImageBuf = NULL;
	BOOL bRet = FALSE;
	HGLOBAL	 Hglobal = ::GlobalAlloc(GMEM_MOVEABLE, dwLen);
	if (!Hglobal)
	{
		return bRet;
	}
	m_ImageBuf = ::GlobalLock(Hglobal);			//锁定全局分配的内存然后复制
	memset(m_ImageBuf, 0, dwLen);
	memcpy(m_ImageBuf, PmemIm,dwLen);
	::GlobalUnlock(Hglobal);		//解除锁定
	IStream	 *Pstream = NULL;
	HRESULT hr = ::CreateStreamOnHGlobal(Hglobal, TRUE, &Pstream);
	if (FAILED(hr))return bRet;
	hr=ImgObj.Load(Pstream);
	if (FAILED(hr))return bRet;
	Pstream->Release();
	bRet = TRUE;
	::GlobalFree(Hglobal);		//释放全局内存申请
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
	//设置协议头
	LPhttp->SetRequestHeader(_T("Content-Type"), _T("application/x-www-form-urlencoded; charset=UTF-8"));
	LPhttp->SetRequestHeader(_T("Referer"), _T("http://bl.shishicaicp.net/index.php/user/login"));
	//发送
	_variant_t  Async;
	Async = m_SendBoy;
	LPhttp->Send(Async);
	//接收返回内容
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
