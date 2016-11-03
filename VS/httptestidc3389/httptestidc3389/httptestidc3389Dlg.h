
// httptestidc3389Dlg.h : 头文件
//

#pragma once

#import "C:\\Windows\\System32\\winhttpcom.dll" no_namespace
// Chttptestidc3389Dlg 对话框
class Chttptestidc3389Dlg : public CDialogEx
{
// 构造
public:
	Chttptestidc3389Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HTTPTESTIDC3389_DIALOG };
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
	afx_msg void OnBnClickedBtnLogin();
BOOL loginWeb(CString cstr_user, CString cstr_pass);
//智能指针
IWinHttpRequestPtr Pwinhttp;
// 取文本中间
CString GetStringMiddle(CString Cstr_Source, CString Cstr_left, CString Cstr_right);
afx_msg void OnBnClickedBtnGet();
};
