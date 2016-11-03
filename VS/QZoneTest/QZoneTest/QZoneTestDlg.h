
// QZoneTestDlg.h : 头文件
//

#pragma once
#include "resource.h"


// CQZoneTestDlg 对话框
class CQZoneTestDlg : public CDialogEx
{
// 构造
public:
	CQZoneTestDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_QZONETEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnLogin();
	CStatusBar m_Statusbar;
	BOOL InitStatusBar();
	void SetStateInfo(LPCTSTR lpszText, UINT posIdx = 0);

	void EnableControl(BOOL bEnable = TRUE);

	CString m_strQQ;
	CString m_strPass;
	afx_msg void OnBnClickedBtnPublic();
};
