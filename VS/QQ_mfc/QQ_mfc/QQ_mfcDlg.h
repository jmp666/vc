
// QQ_mfcDlg.h : 头文件
//

#pragma once
#include "afxext.h"


// CQQ_mfcDlg 对话框
class CQQ_mfcDlg : public CDialogEx
{
// 构造
public:
	CQQ_mfcDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_QQ_MFC_DIALOG };
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
public:
	CString m_StrUser;
	CString m_StrPass;
	BOOL 创建状态栏();
	CStatusBar m_状态栏;
	
	void 设置状态栏文本(PTCHAR strbuf, UINT ID=0);
	bool 禁用控件函数(bool Flog);
};
