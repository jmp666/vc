
// GameloginDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "Global.h"
#include "AddUserMessage.h"
// CGameloginDlg 对话框
class CGameloginDlg : public CDialogEx
{
// 构造
public:
	CGameloginDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAMELOGIN_DIALOG };
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
	// 游戏所在文件目录
	CString m_Game_Path;
	// 账号登陆信息
	CListCtrl m_List_Ctrl_Date;
	//添加用户登陆信息窗口
	CAddUserMessage m_AddUserMessage;
	//修改游戏
	BOOL ModifyGameRolled(CString strGamePath, DWORD ndIndex);
	//复制指定数量游戏目录
	BOOL CopyDirectroyPathList(CString strGamePath, DWORD ndIndex);
	//复制游戏目录
	BOOL CopyDirectoryFile(CString strSoucer, CString strToDest);
	// 选择游戏大区函数
	BOOL SelectGameRegion(DWORD ndGameRegionID);
	//获取指定大区控件句柄
	HWND GetWidgetHwnd(HWND ParentHwnd, DWORD GameRegionID);
	//定义枚举类型大区编号
#define Game_WT1 0x408
#define Game_START 0x3F2
#define Game_EXIT 0x402
#define Game_DETECTCOLOR 0x0C6CBD
#define Game_FIGUREROLE (LPVOID)0x032364CC
#define Game_CURname 0xF822E0					//dd [[0xF822E0]+0x8c0]+0x228 当前选中的名字
	//定义枚举类型大区编号
	enum Game_WT2_DX2 {
		Game_WT2 = 0x40C,
		Game_WT3,
		Game_WT4,
		Game_DX1,
		Game_DX2
	};
	enum Game_DX3_DX6 {
		Game_DX3 = 0x412,
		Game_DX4,
		Game_DX5,
		Game_DX6
	};
	//选择的人物角色名字
	TCHAR m_szName[200] = { 0 };
	// 检测指定的窗口是否激活
	BOOL DectionAvection(HWND GameHwnd);
	// 检测指定位置的颜色是否正确
	BOOL DetectColor(HWND hwnd, COLORREF Color, int x, int y);
	// 选择登陆的服务器线路
	BOOL SelectServerLine(HWND hwnd, DWORD dwndServerID, DWORD ndLine);
	//选择人物角色
	BOOL SelectRole(HWND hwnd, DWORD ndServerID);
	// 检测游戏是否登陆成功
	BOOL DetectionGameState(PTCHAR szGameName);
	afx_msg void OnBnClickedBtnAdd();
	afx_msg void OnBnClickedBtnOpendirecttory();
	// 登陆游戏
	BOOL LoginGame(USERLONGINMESSAGE szUserLoginMessage);
	// 自动输入
	void oupt(char* szbuf);
	afx_msg void OnBnClickedBtnDel();
	afx_msg void OnBnClickedButton1();
};
