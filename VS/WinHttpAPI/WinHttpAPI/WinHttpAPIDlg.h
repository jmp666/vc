
// WinHttpAPIDlg.h : 头文件
//

#pragma once


// CWinHttpAPIDlg 对话框
class CWinHttpAPIDlg : public CDialogEx
{
// 构造
public:
	CWinHttpAPIDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WINHTTPAPI_DIALOG };
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
	afx_msg void OnBnClickedBtn11();
	afx_msg void OnBnClickedBtn12();
	afx_msg void OnBnClickedBtnClear();
	afx_msg void OnBnClickedBtn14();
	afx_msg void OnBnClickedBtn15();
};
