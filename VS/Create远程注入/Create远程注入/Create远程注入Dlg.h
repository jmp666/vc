
// Create远程注入Dlg.h : 头文件
//

#pragma once


// CCreate远程注入Dlg 对话框
class CCreate远程注入Dlg : public CDialogEx
{
// 构造
public:
	CCreate远程注入Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CREATE_DIALOG };
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
	afx_msg void OnBnClickedButtonZr();
	afx_msg void OnBnClickedButtonCs();
};
