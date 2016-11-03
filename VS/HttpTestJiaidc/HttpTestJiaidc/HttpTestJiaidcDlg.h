
// HttpTestJiaidcDlg.h : 头文件
//

#pragma once
#import "C:\\Windows\\System32\\winhttpcom.dll"	no_namespace

// CHttpTestJiaidcDlg 对话框
class CHttpTestJiaidcDlg : public CDialogEx
{
// 构造
public:
	CHttpTestJiaidcDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HTTPTESTJIAIDC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnGetvcode();
	//定义对象指针
	IWinHttpRequestPtr	LPhttp;
	// 加载网络图片到CImage对象
	BOOL LodcomImage(LPVOID PmemIm, ULONG dwLen, CImage& ImgObj);
	afx_msg void OnBnClickedBtnLogin();
};
