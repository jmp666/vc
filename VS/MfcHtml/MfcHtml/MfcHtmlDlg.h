
// MfcHtmlDlg.h : 头文件
//

#pragma once
#include "explorer1.h"
#include "afxwin.h"


// CMfcHtmlDlg 对话框
class CMfcHtmlDlg : public CDialogEx
{
// 构造
public:
	CMfcHtmlDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCHTML_DIALOG };
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
	CExplorer1 m_Web;
	CEdit m_Edit;
	CButton m_Button;
	afx_msg void OnBnClickedButton1();
};
