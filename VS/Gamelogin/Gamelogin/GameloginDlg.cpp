
// GameloginDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Gamelogin.h"
#include "GameloginDlg.h"
#include "afxdialogex.h"
#include <array>
#include "Global.h"
#include <io.h>
#include <atlconv.h>
#include <vector>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
using namespace std;
typedef vector<USERLONGINMESSAGE> MyuserLoginDate;
// CGameloginDlg 对话框
MyuserLoginDate G_vector;


CGameloginDlg::CGameloginDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GAMELOGIN_DIALOG, pParent)
	, m_Game_Path(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGameloginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_GAMEPATH, m_Game_Path);
	DDX_Control(pDX, IDC_LIST_DATE, m_List_Ctrl_Date);
}

BEGIN_MESSAGE_MAP(CGameloginDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_ADD, &CGameloginDlg::OnBnClickedBtnAdd)
	ON_BN_CLICKED(IDC_BTN_OPENDIRECTTORY, &CGameloginDlg::OnBnClickedBtnOpendirecttory)
	ON_BN_CLICKED(IDC_BTN_DEL, &CGameloginDlg::OnBnClickedBtnDel)
	ON_BN_CLICKED(IDC_BUTTON1, &CGameloginDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CGameloginDlg 消息处理程序

BOOL CGameloginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	/***********************************************************************************************************/
	DWORD dwstyle = NULL;
	dwstyle = ::GetWindowLong(m_List_Ctrl_Date.m_hWnd, GWL_STYLE);			//获取窗口风格
	dwstyle |= LVS_REPORT;			//设置报表视图
	::SetWindowLong(m_List_Ctrl_Date.m_hWnd, GWL_STYLE, dwstyle);				//重新设置窗口风格
	DWORD dwExstyle = NULL;		//扩展风格
	dwExstyle = m_List_Ctrl_Date.GetExtendedStyle();			//获取窗口扩展风格
	dwExstyle |= LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT;			//设置网格线和选中一行突出显示
	m_List_Ctrl_Date.SetExtendedStyle(dwExstyle);					//设置扩展风格
	/***********************************************************************************************************/
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	array<PTCHAR, 6> m_listheading = { L"账号",L"密码",L"大区",L"服务器",L"线路",L"角色" };		//列标题数组
	for (UINT i = 0; i < m_listheading.size();i++)
	{
		m_List_Ctrl_Date.InsertColumn(i, m_listheading[i], LVCFMT_LEFT, 100);
	}
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CGameloginDlg::OnPaint()
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
HCURSOR CGameloginDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CGameloginDlg::OnBnClickedBtnAdd()
{
	int m_ret= m_AddUserMessage.DoModal();
	if (m_ret == IDCANCEL)
	{
		return;
	}
	int m_index = m_List_Ctrl_Date.GetItemCount();		//获取视图列表框里的项目数
	TCHAR Wszbuf[MAX_PATH] = { 0 };
	if (m_AddUserMessage.m_userloginText.m_UserName.IsEmpty())
	{
		return;
	}
	for (int i = 0; i < m_index; i++)
	{
		memset(Wszbuf, 0, MAX_PATH);

		m_List_Ctrl_Date.GetItemText(i, 0, Wszbuf, MAX_PATH);
		
		if (!wcscmp(Wszbuf, m_AddUserMessage.m_userloginText.m_UserName))
		{
			AfxMessageBox(_T("请勿重复添加同一个账号！"));
			return;
		}
		
	}
	//把数据添加到vector数组里
	G_vector.push_back(m_AddUserMessage.m_userloginText);		//在vector的末尾添加数据

	Map_Str::iterator it = m_AddUserMessage.m_userloginText.m_GameRepion.begin();
	m_List_Ctrl_Date.InsertItem(m_index, m_AddUserMessage.m_userloginText.m_UserName);		//账号
	m_List_Ctrl_Date.SetItemText(m_index, 1, m_AddUserMessage.m_userloginText.m_PassWord);	//密码

	m_List_Ctrl_Date.SetItemText(m_index, 2, it->second);	//大区
	m_AddUserMessage.m_userloginText.m_GameRepion.clear();		//用完就清空
	it = m_AddUserMessage.m_userloginText.m_GameServer.begin();
	m_List_Ctrl_Date.SetItemText(m_index, 3, it->second);	//服务器
	m_AddUserMessage.m_userloginText.m_GameServer.clear();		//用完就清空
	it = m_AddUserMessage.m_userloginText.m_GameLine.begin();
	m_List_Ctrl_Date.SetItemText(m_index, 4, it->second);	//线路
	m_AddUserMessage.m_userloginText.m_GameLine.clear();		//用完就清空
	it = m_AddUserMessage.m_userloginText.m_GameRole.begin();
	m_List_Ctrl_Date.SetItemText(m_index, 5, it->second);	//角色
	m_AddUserMessage.m_userloginText.m_GameRole.clear();		//用完就清空
}


void CGameloginDlg::OnBnClickedBtnOpendirecttory()
{
	// TODO: 在此添加控件通知处理程序代码
	m_Game_Path = GetGamePathdirectory();
	UpdateData(FALSE);
}
//修改游戏
#define StartHookBase (LPVOID) 0x407BDA			//jmp
#define FilePathHookBase (LPVOID) 0x44A839		//目录基址
BOOL CGameloginDlg::ModifyGameRolled(CString strGamePath,DWORD ndIndex)
{
	UpdateData(TRUE);
	BOOL m_IsFlags = CopyDirectroyPathList(m_Game_Path,ndIndex);
	STARTUPINFO si = { 0 };
	PROCESS_INFORMATION pi = { 0 };
	CString strFilePath = strGamePath;
	strFilePath += L"launcher.exe";
	si.cb = sizeof STARTUPINFO;
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = TRUE;
	if (m_IsFlags)
	{
		::CreateProcess(NULL,
			strFilePath.GetBuffer(),
			NULL,
			NULL,
			FALSE,
			CREATE_SUSPENDED,//挂起的方式创建
			NULL,
			strGamePath,
			&si,
			&pi
			);
		strGamePath.ReleaseBuffer();	//释放
		//准备hook
		/*----------------------------------------------------------------------------------------*/
		BYTE btjmp = 0xEB;
		SIZE_T ndBytesWritten = NULL;
		DWORD FormerProtect = NULL;
		BOOL Rt = FALSE;
		Rt = ::VirtualProtectEx(pi.hProcess, StartHookBase, 4, PAGE_EXECUTE_READWRITE, &FormerProtect);
		if (Rt)
		{
			::WriteProcessMemory(pi.hProcess, StartHookBase, &btjmp, 1, &ndBytesWritten);
		}
		::VirtualProtectEx(pi.hProcess, StartHookBase, 4, FormerProtect, &FormerProtect);
		/*-----------------------------------------------------------------------------------------*/
		//准备修改路径
		char szpath[20] = { 0 };
		sprintf_s(szpath,"%02d",ndIndex);
		Rt = ::VirtualProtectEx(pi.hProcess, FilePathHookBase, 4, PAGE_EXECUTE_READWRITE, &FormerProtect);
		if (Rt)
		{
			::WriteProcessMemory(pi.hProcess, FilePathHookBase, &szpath, 2, &ndBytesWritten);
		}
		::VirtualProtectEx(pi.hProcess, FilePathHookBase, 4, FormerProtect, &FormerProtect);
		ResumeThread(pi.hThread);		//恢复线程
	}
	return TRUE;
}
//复制游戏目录
BOOL CGameloginDlg::CopyDirectroyPathList(CString strGamePath,DWORD ndIndex)
{
	if (strGamePath.IsEmpty())
	{
		AfxMessageBox(TEXT("请选择游戏目录"));
		return FALSE;
	}
	CString TargetDirectoryPath=NULL;		//目标目录
	CString SoucerDirectoryPath=NULL;		//源目录
	CString TempDirectoryPath=NULL;			//临时字符串
	CString AccessDirectoryPath=NULL;		//用来检测文件是否存在
														//static BYTE btNum = 0;
	SoucerDirectoryPath = strGamePath;
	TargetDirectoryPath = strGamePath;
	SoucerDirectoryPath+=L"Client";
	TempDirectoryPath.Format(L"Clie%02d",ndIndex);
	TargetDirectoryPath += TempDirectoryPath;
	TRACE(L"%s\n", SoucerDirectoryPath);
	TRACE(L"%s\n", TargetDirectoryPath);
	AccessDirectoryPath = TargetDirectoryPath;
	AccessDirectoryPath += L"\\Client.exe";
	if (_waccess(AccessDirectoryPath.GetBuffer(), 0) == -1)		//不存在的时候复制
	{
		AccessDirectoryPath.ReleaseBuffer();
		CopyDirectoryFile(SoucerDirectoryPath, TargetDirectoryPath);
	}
	::Sleep(200);
	return TRUE;
}
BOOL CGameloginDlg::CopyDirectoryFile(CString strSoucer, CString strToDest)
{
	CString strtemp = strSoucer;
	strtemp += "\\*.*";
	SHFILEOPSTRUCT fileop = { 0 };
	fileop.wFunc = FO_COPY;		//文件操作的属性 FO_COPY表示复制文件
	fileop.pFrom = strtemp;		//复制的目录
	fileop.pTo = strToDest;			//复制到的目录
	fileop.fFlags = FOF_ALLOWUNDO | FOF_SILENT | FOF_NOCONFIRMMKDIR;
	int m_ret = ::SHFileOperation(&fileop);
	TRACE("返回值==%d\n", m_ret);
	if (fileop.fAnyOperationsAborted)
	{
		return FALSE;
	}
	//TRACE("返回值==%d\n", m_ret);
	Sleep(200);
	return TRUE;
}

// 登陆游戏
BOOL CGameloginDlg::LoginGame(USERLONGINMESSAGE szUserLoginMessage)
{
	//修改游戏多开
	if (m_Game_Path.IsEmpty())
	{
		AfxMessageBox(_T("请先选择游戏安装目录！"));
		return FALSE;
	}
	//视图列表框的项目数量
	int m_indexnum = m_List_Ctrl_Date.GetItemCount();
	if (m_indexnum<1)
	{
		return FALSE;
	}
	if (!ModifyGameRolled(m_Game_Path, m_indexnum))
		return FALSE;
	//检测游戏是否打开
	Map_Str::iterator  it = szUserLoginMessage.m_GameRepion.begin();
	while (true)
	{
		if (::FindWindow(NULL, L"Yulgang_File_Update"))
		{
			TRACE("游戏已经打开了\n");
			break;
		}
		::Sleep(50);
	}
	//登陆游戏后开始选区
	::Sleep(500);
	switch (it->first)
	{
	case 0:
			SelectGameRegion(Game_WT1);		//选择大区
			break;
	case 1:
			SelectGameRegion(Game_WT2);		//选择大区
			break;
	case 2:
		SelectGameRegion(Game_WT3);		//选择大区
		break;
	case 3:
		SelectGameRegion(Game_WT4);		//选择大区
		break;
	case 4:
		SelectGameRegion(Game_DX1);		//选择大区
		break;
	case 5:
		SelectGameRegion(Game_DX2);		//选择大区
		break;
	case 6:
		SelectGameRegion(Game_DX3);		//选择大区
		break;
	case 7:
		SelectGameRegion(Game_DX4);		//选择大区
		break;
	case 8:
		SelectGameRegion(Game_DX5);		//选择大区
		break;
	case  9:
		SelectGameRegion(Game_DX6);		//选择大区
		break;
	}
	::Sleep(3000);
	SelectGameRegion(Game_START);	//点击开始
	::Sleep(2000);

	//对比颜色
	HWND m_TmpHwnd = NULL;
	m_TmpHwnd = ::FindWindow(L"D3D Window", L"YB_OnlineClient");
	for (int i = 0; i < 1000; i++)
	{
		m_TmpHwnd = ::FindWindow(L"D3D Window", L"YB_OnlineClient");
		if (m_TmpHwnd)
		{
			break;
		}
		::Sleep(50);
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	DWORD ndProcessID = NULL;
	HANDLE hpandle = NULL;
	::GetWindowThreadProcessId(m_TmpHwnd, &ndProcessID);
	ASSERT(ndProcessID != NULL);
	hpandle = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, ndProcessID);
	//while (true)
	//{
	//	if (!DectionAvection(m_TmpHwnd))
	//		::SwitchToThisWindow(m_TmpHwnd, TRUE);	//如果没被激活则激活
	//	if (DetectColor(m_TmpHwnd, Game_DETECTCOLOR, 301, 414))
	//	{
	//		TRACE("可以输入账号密码了！\n");
	//		break;
	//	}
	//	::Sleep(500);
	//}
	::Sleep(1000);
	CRect  r1 = { 0 };
	::GetWindowRect(m_TmpHwnd, &r1);
	if (!DectionAvection(m_TmpHwnd))
		::SwitchToThisWindow(m_TmpHwnd, TRUE);	//如果没被激活则激活
	::SetCursorPos(r1.left + 353, r1.top + 472);
	::PostMessage(m_TmpHwnd, WM_LBUTTONDBLCLK, 0, (LPARAM)353 + 472 * 65536);
	::Sleep(150);
	if (!DectionAvection(m_TmpHwnd))
		::SwitchToThisWindow(m_TmpHwnd, TRUE);	//如果没被激活则激活
	USES_CONVERSION;			//宽字符转换成ASINC
	oupt(W2A(szUserLoginMessage.m_UserName.GetBuffer()));
	szUserLoginMessage.m_UserName.ReleaseBuffer();		//释放缓冲区
	::Sleep(1200);
	if (!DectionAvection(m_TmpHwnd))
		::SwitchToThisWindow(m_TmpHwnd, TRUE);	//如果没被激活则激活
	keybd_event(VK_TAB, 0, 0, 0);
	keybd_event(VK_TAB, 0, KEYEVENTF_KEYUP, 0);
	::Sleep(500);
	oupt(W2A(szUserLoginMessage.m_PassWord.GetBuffer()));
	szUserLoginMessage.m_PassWord.ReleaseBuffer();			//释放缓冲区
	::Sleep(100);
	if (!DectionAvection(m_TmpHwnd))
		::SwitchToThisWindow(m_TmpHwnd, TRUE);	//如果没被激活则激活
	::SetCursorPos(r1.left + 371, r1.top + 543);
	keybd_event(VK_RETURN, 0, 0, 0);
	keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0);
	::Sleep(10000);
	//int i = 0;
	//while (true)
	//{
	//	if (i > 100)
	//	{
	//		//如果超过了就返回等待50秒
	//		::TerminateProcess(hpandle, -1);
	//		return FALSE;
	//	}
	//	if (!DectionAvection(m_TmpHwnd))
	//		::SwitchToThisWindow(m_TmpHwnd, TRUE);	//如果没被激活则激活
	//	if (!DetectColor(m_TmpHwnd, Game_DETECTCOLOR, 301, 414))
	//	{
	//		TRACE("可以选区了！\n");
	//		break;
	//	}
	//	if (!DetectColor(m_TmpHwnd, 0xD6F0F6, 310, 243))
	//	{
	//		//如果密码错误就退出游戏
	//		::Sleep(3000);
	//		::TerminateProcess(hpandle, -1);
	//		return FALSE;
	//	}
	//	::Sleep(500);
	//	i++;
	//}
	::Sleep(50);
	it = szUserLoginMessage.m_GameServer.begin();
	DWORD m_sever = it->first;
	it = szUserLoginMessage.m_GameLine.begin();
	DWORD m_serline = it->first;
	SelectServerLine(m_TmpHwnd, m_sever, m_serline);	//选区选线路
	::Sleep(2000);
	it = szUserLoginMessage.m_GameRole.begin();
	SelectRole(m_TmpHwnd, it->first);		//选择人物
	DetectionGameState(m_szName);			//检测游戏是否登陆成功
	return TRUE;
}
BOOL CALLBACK EnumChildWindowsProc(
	HWND hwnd,      // handle to parent window
	LPARAM lParam   // application-defined value
	);
HWND CGameloginDlg::GetWidgetHwnd(HWND ParentHwnd, DWORD GameRegionID)
{
	MyHwnd strMyHwnd = { 0 };
	DWORD WidgetID = NULL;
	strMyHwnd.WidGetID = GameRegionID;
	//枚举窗口句柄符合的返回
	::EnumChildWindows(ParentHwnd, EnumChildWindowsProc, (LPARAM)&strMyHwnd);
	return strMyHwnd.hwnd;
}
BOOL CALLBACK EnumChildWindowsProc(
	HWND hwnd,      // handle to parent window
	LPARAM lParam   // application-defined value
	)
{
	PMyHwnd TmpMyHwnd = (PMyHwnd)lParam;
	DWORD TmpWidgetID = NULL;
	if (!hwnd)
	{
		return FALSE;
	}
	TmpWidgetID = ::GetDlgCtrlID(hwnd);
	if (TmpWidgetID == TmpMyHwnd->WidGetID)
	{
		TmpMyHwnd->hwnd = hwnd;
		return FALSE;
	}
	return TRUE;
}
BOOL CGameloginDlg::SelectGameRegion(DWORD ndGameRegionID)
{
	HWND m_Parenthwnd = NULL;
	HWND m_tmphwnd = NULL;
	m_Parenthwnd = ::FindWindow(NULL, L"Yulgang_File_Update");
	if (!m_Parenthwnd)
	{
		AfxMessageBox(L"父窗口句柄无效");
		return FALSE;
	}
	m_tmphwnd = GetWidgetHwnd(m_Parenthwnd, ndGameRegionID);
	if (!m_tmphwnd)
	{
		AfxMessageBox(L"获取窗口句柄失败");
		return FALSE;
	}
	int x = 110;
	int y = 12;
	DWORD ndCoordinate = NULL;
	switch (ndGameRegionID)
	{
	case Game_START:
		x = 45;
		y = 4;
		break;
	default:
		break;
	}
	ndCoordinate = x + y * 65536;
	::PostMessage(m_tmphwnd, WM_LBUTTONDOWN, TRUE, ndCoordinate);
	::PostMessage(m_tmphwnd, WM_LBUTTONUP, FALSE, ndCoordinate);
	return TRUE;
}

// 检测指定的窗口是否激活
BOOL CGameloginDlg::DectionAvection(HWND GameHwnd)
{
	HWND m_AvectionHwnd = NULL;	//激活的窗口句柄
	m_AvectionHwnd = ::GetForegroundWindow();
	if (m_AvectionHwnd != GameHwnd)
	{
		return FALSE;
	}
	return TRUE;
}
// 检测指定位置的颜色是否正确
BOOL CGameloginDlg::DetectColor(HWND hwnd, COLORREF Color, int x, int y)
{
	HDC		hdc = NULL;
	COLORREF m_color = NULL;
	hdc = ::GetWindowDC(hwnd);
	if (!hdc)
	{
		return FALSE;
	}
	CRect m_rect = { 0 };
	::GetWindowRect(hwnd, &m_rect);
	m_color = ::GetPixel(hdc, m_rect.left + x, m_rect.top + y);
	::ReleaseDC(hwnd, hdc);
	TRACE("\nm_color=%X color=%X", m_color, Color);
	if (m_color != Color)
	{

		return FALSE;
	}
	return TRUE;
}
// 选择登陆的服务器线路
BOOL CGameloginDlg::SelectServerLine(HWND hwnd, DWORD ndServerID, DWORD ndLine)
{
	if (!DectionAvection(hwnd))
		::SwitchToThisWindow(hwnd, TRUE);	//如果没被激活则激活
	int severX = 284;		//服务器坐标
	int severY = 316 + (ndServerID) * 21;
	int LineX = 515;		//线路坐标
	int LineY = 316 + (ndLine) * 21;
	CRect r1 = { 0 };
	::GetWindowRect(hwnd, &r1);
	::SetCursorPos(r1.left + severX, r1.top + severY);		//选择服务器
	::mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);//点下左键 
	::Sleep(50);
	::mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);//松开左键
	::Sleep(1000);
	::SetCursorPos(r1.left + LineX, r1.top + LineY);		//选择线路
	::mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);//点下左键 
	::Sleep(50);
	::mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);//松开左键
	::mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);//点下左键 
	::Sleep(50);
	::mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);//松开左键
	::Sleep(1000);
	::SetCursorPos(r1.left + 496, r1.top + 556);		//进入游戏
	::mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);//点下左键 
	::Sleep(100);
	::mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);//松开左键
	return TRUE;
}
//选择人物角色
BOOL CGameloginDlg::SelectRole(HWND hwnd, DWORD ndServerID)
{
	DWORD ndProcessID = NULL;
	HANDLE hpandle = NULL;
	DWORD lpbuf = NULL;
	DWORD ReadSize = NULL;
	TCHAR szGameName[200] = { 0 };
	::GetWindowThreadProcessId(hwnd, &ndProcessID);
	ASSERT(ndProcessID != NULL);
	hpandle = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, ndProcessID);
	int x = 137;
	int y = 168 + (ndServerID) * 41;
	CRect r1 = { 0 };
	::GetWindowRect(hwnd, &r1);
	if (!DectionAvection(hwnd))
		::SwitchToThisWindow(hwnd, TRUE);	//如果没被激活则激活
	::SetCursorPos(r1.left + x, r1.top + y);
	::mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);//点下左键 
	::Sleep(100);
	::mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);//松开左键
	::Sleep(1000);
	//设置人物角色名字到窗口
	DWORD m_NameBase = NULL;

	//dd[[0xF822E0] + 0x8c0] + 0x228 当前选中的名
	::ReadProcessMemory(hpandle, (PDWORD)Game_CURname, &m_NameBase, 4, &ReadSize);
	ASSERT(m_NameBase != NULL);
	//m_NameBase = *(PDWORD)((DWORD)m_NameBase + 0x8c0);
	::ReadProcessMemory(hpandle, (PDWORD)((DWORD)m_NameBase + 0x8c0), &m_NameBase, 4, &ReadSize);
	ASSERT(m_NameBase != NULL);
	::ReadProcessMemory(hpandle, (PDWORD)((DWORD)m_NameBase + 0x228), szGameName, 200, &ReadSize);
	if (!wcscmp(szGameName, L""))
	{
		::CloseHandle(hpandle);
		return FALSE;
	}
	memcpy(m_szName, szGameName, 200);
	::SetWindowText(hwnd, szGameName);
	::CloseHandle(hpandle);
	::Sleep(1500);
	//进入游戏

	::SetCursorPos(r1.left + 400, r1.top + 597);
	::mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);//点下左键 
	::Sleep(100);
	::mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);//松开左键

	return TRUE;
}


// 检测游戏是否登陆成功
BOOL CGameloginDlg::DetectionGameState(PTCHAR szGameName)
{
	HWND hwnd = NULL;
	DWORD ndProcessID = NULL;
	HANDLE hpandle = NULL;
	DWORD lpbuf = NULL;
	DWORD ReadSize = NULL;
	if (!wcscmp(szGameName, L""))
	{
		return FALSE;
	}
	hwnd = ::FindWindow(L"D3D Window", szGameName);
	if (!hwnd)
	{
		return FALSE;
	}
	::GetWindowThreadProcessId(hwnd, &ndProcessID);
	ASSERT(ndProcessID != NULL);
	hpandle = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, ndProcessID);
	ASSERT(hpandle != NULL);
	int i = 0;
	while (true)
	{

		if (i > 60)
		{
			::TerminateProcess(hpandle, -1);
			return FALSE;
		}
		if (!hpandle)
		{

			return FALSE;
		}
		::ReadProcessMemory(hpandle, Game_FIGUREROLE, &lpbuf, 4, &ReadSize);
		if (lpbuf)
		{
			TRACE(L"\n游戏登陆成功了！\n");
			break;
		}
		::Sleep(1000);
		i++;
	}

	::CloseHandle(hpandle);
	return TRUE;
}


// 自动输入
void CGameloginDlg::oupt(char* szbuf)
{
		int leng = strlen(szbuf);
		for (int i = 0; i< leng; i++)
		{
			if (szbuf[i] >= 'a' && szbuf[i] <= 'z')
			{
				SHORT m_key = ::GetKeyState(VK_CAPITAL);
				BYTE m_State = LOBYTE(m_key);
				if (m_State)
				{
					::keybd_event(VK_CAPITAL, 0, 0, 0);
					::keybd_event(VK_CAPITAL, 0, KEYEVENTF_KEYUP, 0);
				}
				::keybd_event(szbuf[i] - 32, 0, 0, 0);
				::keybd_event(szbuf[i] - 32, 0, KEYEVENTF_KEYUP, 0);
				::Sleep(100);
				continue;
			}
			if (szbuf[i] >= 'A' && szbuf[i] <= 'Z')
			{
				SHORT m_key = ::GetKeyState(VK_CAPITAL);
				BYTE m_State = LOBYTE(m_key);
				if (!m_State)
				{
					::keybd_event(VK_CAPITAL, 0, 0, 0);
					::keybd_event(VK_CAPITAL, 0, KEYEVENTF_KEYUP, 0);
				}
				::keybd_event(szbuf[i], 0, 0, 0);
				::keybd_event(szbuf[i], 0, KEYEVENTF_KEYUP, 0);
				::Sleep(100);
				continue;
			}
			switch (szbuf[i])
			{
			case 33:				//!
				::keybd_event(VK_SHIFT, 0, 0, 0);
				::keybd_event(49, 0, 0, 0);
				::keybd_event(49, 0, KEYEVENTF_KEYUP, 0);
				::keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);
				::Sleep(100);
				break;
			case 35:		//#
				::keybd_event(VK_SHIFT, 0, 0, 0);
				::keybd_event(51, 0, 0, 0);
				::keybd_event(51, 0, KEYEVENTF_KEYUP, 0);
				::keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);
				::Sleep(100);
				break;
			case 36:			//$
				::keybd_event(VK_SHIFT, 0, 0, 0);
				::keybd_event(52, 0, 0, 0);
				::keybd_event(52, 0, KEYEVENTF_KEYUP, 0);
				::keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);
				::Sleep(100);
				break;
			case 37:			//%
				::keybd_event(VK_SHIFT, 0, 0, 0);
				::keybd_event(53, 0, 0, 0);
				::keybd_event(53, 0, KEYEVENTF_KEYUP, 0);
				::keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);
				::Sleep(100);
				break;
			case 38:			//&
				::keybd_event(VK_SHIFT, 0, 0, 0);
				::keybd_event(55, 0, 0, 0);
				::keybd_event(55, 0, KEYEVENTF_KEYUP, 0);
				::keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);
				::Sleep(100);
				break;
			case 94:		//^
				::keybd_event(VK_SHIFT, 0, 0, 0);
				::keybd_event(54, 0, 0, 0);
				::keybd_event(54, 0, KEYEVENTF_KEYUP, 0);
				::keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);
				::Sleep(100);
				break;
			case 42:			//*
				::keybd_event(VK_SHIFT, 0, 0, 0);
				::keybd_event(56, 0, 0, 0);
				::keybd_event(56, 0, KEYEVENTF_KEYUP, 0);
				::keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);
				::Sleep(100);
				break;
			case 40:			//(
				::keybd_event(VK_SHIFT, 0, 0, 0);
				::keybd_event(57, 0, 0, 0);
				::keybd_event(57, 0, KEYEVENTF_KEYUP, 0);
				::keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);
				::Sleep(100);
				break;
			case 41:		//)
				::keybd_event(VK_SHIFT, 0, 0, 0);
				::keybd_event(48, 0, 0, 0);
				::keybd_event(48, 0, KEYEVENTF_KEYUP, 0);
				::keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);
				::Sleep(100);
				break;
			case 64:		//@
				::keybd_event(VK_SHIFT, 0, 0, 0);
				::keybd_event(50, 0, 0, 0);
				::keybd_event(50, 0, KEYEVENTF_KEYUP, 0);
				::keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);
				::Sleep(100);
				break;
			default:
				::keybd_event(szbuf[i], 0, 0, 0);
				::keybd_event(szbuf[i], 0, KEYEVENTF_KEYUP, 0);
				::Sleep(100);
				break;
			}

		}

}


void CGameloginDlg::OnBnClickedBtnDel()
{
	POSITION pos = m_List_Ctrl_Date.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		AfxMessageBox(_T("请至少选中一项需要删除的数据!"));
		return;
	}
	else
	{
		while (pos)
		{
			int nItem = m_List_Ctrl_Date.GetNextSelectedItem(pos);
			m_List_Ctrl_Date.DeleteItem(nItem);		//删除指定项
		}
	}


}


void CGameloginDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	MyuserLoginDate::iterator it = G_vector.begin();
	for (; it != G_vector.end();it++)
	{
		LoginGame(*it);
	}
}
