
// GameloginDlg.cpp : ʵ���ļ�
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
// CGameloginDlg �Ի���
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


// CGameloginDlg ��Ϣ�������

BOOL CGameloginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	/***********************************************************************************************************/
	DWORD dwstyle = NULL;
	dwstyle = ::GetWindowLong(m_List_Ctrl_Date.m_hWnd, GWL_STYLE);			//��ȡ���ڷ��
	dwstyle |= LVS_REPORT;			//���ñ�����ͼ
	::SetWindowLong(m_List_Ctrl_Date.m_hWnd, GWL_STYLE, dwstyle);				//�������ô��ڷ��
	DWORD dwExstyle = NULL;		//��չ���
	dwExstyle = m_List_Ctrl_Date.GetExtendedStyle();			//��ȡ������չ���
	dwExstyle |= LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT;			//���������ߺ�ѡ��һ��ͻ����ʾ
	m_List_Ctrl_Date.SetExtendedStyle(dwExstyle);					//������չ���
	/***********************************************************************************************************/
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	array<PTCHAR, 6> m_listheading = { L"�˺�",L"����",L"����",L"������",L"��·",L"��ɫ" };		//�б�������
	for (UINT i = 0; i < m_listheading.size();i++)
	{
		m_List_Ctrl_Date.InsertColumn(i, m_listheading[i], LVCFMT_LEFT, 100);
	}
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CGameloginDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
	int m_index = m_List_Ctrl_Date.GetItemCount();		//��ȡ��ͼ�б�������Ŀ��
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
			AfxMessageBox(_T("�����ظ����ͬһ���˺ţ�"));
			return;
		}
		
	}
	//��������ӵ�vector������
	G_vector.push_back(m_AddUserMessage.m_userloginText);		//��vector��ĩβ�������

	Map_Str::iterator it = m_AddUserMessage.m_userloginText.m_GameRepion.begin();
	m_List_Ctrl_Date.InsertItem(m_index, m_AddUserMessage.m_userloginText.m_UserName);		//�˺�
	m_List_Ctrl_Date.SetItemText(m_index, 1, m_AddUserMessage.m_userloginText.m_PassWord);	//����

	m_List_Ctrl_Date.SetItemText(m_index, 2, it->second);	//����
	m_AddUserMessage.m_userloginText.m_GameRepion.clear();		//��������
	it = m_AddUserMessage.m_userloginText.m_GameServer.begin();
	m_List_Ctrl_Date.SetItemText(m_index, 3, it->second);	//������
	m_AddUserMessage.m_userloginText.m_GameServer.clear();		//��������
	it = m_AddUserMessage.m_userloginText.m_GameLine.begin();
	m_List_Ctrl_Date.SetItemText(m_index, 4, it->second);	//��·
	m_AddUserMessage.m_userloginText.m_GameLine.clear();		//��������
	it = m_AddUserMessage.m_userloginText.m_GameRole.begin();
	m_List_Ctrl_Date.SetItemText(m_index, 5, it->second);	//��ɫ
	m_AddUserMessage.m_userloginText.m_GameRole.clear();		//��������
}


void CGameloginDlg::OnBnClickedBtnOpendirecttory()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_Game_Path = GetGamePathdirectory();
	UpdateData(FALSE);
}
//�޸���Ϸ
#define StartHookBase (LPVOID) 0x407BDA			//jmp
#define FilePathHookBase (LPVOID) 0x44A839		//Ŀ¼��ַ
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
			CREATE_SUSPENDED,//����ķ�ʽ����
			NULL,
			strGamePath,
			&si,
			&pi
			);
		strGamePath.ReleaseBuffer();	//�ͷ�
		//׼��hook
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
		//׼���޸�·��
		char szpath[20] = { 0 };
		sprintf_s(szpath,"%02d",ndIndex);
		Rt = ::VirtualProtectEx(pi.hProcess, FilePathHookBase, 4, PAGE_EXECUTE_READWRITE, &FormerProtect);
		if (Rt)
		{
			::WriteProcessMemory(pi.hProcess, FilePathHookBase, &szpath, 2, &ndBytesWritten);
		}
		::VirtualProtectEx(pi.hProcess, FilePathHookBase, 4, FormerProtect, &FormerProtect);
		ResumeThread(pi.hThread);		//�ָ��߳�
	}
	return TRUE;
}
//������ϷĿ¼
BOOL CGameloginDlg::CopyDirectroyPathList(CString strGamePath,DWORD ndIndex)
{
	if (strGamePath.IsEmpty())
	{
		AfxMessageBox(TEXT("��ѡ����ϷĿ¼"));
		return FALSE;
	}
	CString TargetDirectoryPath=NULL;		//Ŀ��Ŀ¼
	CString SoucerDirectoryPath=NULL;		//ԴĿ¼
	CString TempDirectoryPath=NULL;			//��ʱ�ַ���
	CString AccessDirectoryPath=NULL;		//��������ļ��Ƿ����
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
	if (_waccess(AccessDirectoryPath.GetBuffer(), 0) == -1)		//�����ڵ�ʱ����
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
	fileop.wFunc = FO_COPY;		//�ļ����������� FO_COPY��ʾ�����ļ�
	fileop.pFrom = strtemp;		//���Ƶ�Ŀ¼
	fileop.pTo = strToDest;			//���Ƶ���Ŀ¼
	fileop.fFlags = FOF_ALLOWUNDO | FOF_SILENT | FOF_NOCONFIRMMKDIR;
	int m_ret = ::SHFileOperation(&fileop);
	TRACE("����ֵ==%d\n", m_ret);
	if (fileop.fAnyOperationsAborted)
	{
		return FALSE;
	}
	//TRACE("����ֵ==%d\n", m_ret);
	Sleep(200);
	return TRUE;
}

// ��½��Ϸ
BOOL CGameloginDlg::LoginGame(USERLONGINMESSAGE szUserLoginMessage)
{
	//�޸���Ϸ�࿪
	if (m_Game_Path.IsEmpty())
	{
		AfxMessageBox(_T("����ѡ����Ϸ��װĿ¼��"));
		return FALSE;
	}
	//��ͼ�б�����Ŀ����
	int m_indexnum = m_List_Ctrl_Date.GetItemCount();
	if (m_indexnum<1)
	{
		return FALSE;
	}
	if (!ModifyGameRolled(m_Game_Path, m_indexnum))
		return FALSE;
	//�����Ϸ�Ƿ��
	Map_Str::iterator  it = szUserLoginMessage.m_GameRepion.begin();
	while (true)
	{
		if (::FindWindow(NULL, L"Yulgang_File_Update"))
		{
			TRACE("��Ϸ�Ѿ�����\n");
			break;
		}
		::Sleep(50);
	}
	//��½��Ϸ��ʼѡ��
	::Sleep(500);
	switch (it->first)
	{
	case 0:
			SelectGameRegion(Game_WT1);		//ѡ�����
			break;
	case 1:
			SelectGameRegion(Game_WT2);		//ѡ�����
			break;
	case 2:
		SelectGameRegion(Game_WT3);		//ѡ�����
		break;
	case 3:
		SelectGameRegion(Game_WT4);		//ѡ�����
		break;
	case 4:
		SelectGameRegion(Game_DX1);		//ѡ�����
		break;
	case 5:
		SelectGameRegion(Game_DX2);		//ѡ�����
		break;
	case 6:
		SelectGameRegion(Game_DX3);		//ѡ�����
		break;
	case 7:
		SelectGameRegion(Game_DX4);		//ѡ�����
		break;
	case 8:
		SelectGameRegion(Game_DX5);		//ѡ�����
		break;
	case  9:
		SelectGameRegion(Game_DX6);		//ѡ�����
		break;
	}
	::Sleep(3000);
	SelectGameRegion(Game_START);	//�����ʼ
	::Sleep(2000);

	//�Ա���ɫ
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
	//		::SwitchToThisWindow(m_TmpHwnd, TRUE);	//���û�������򼤻�
	//	if (DetectColor(m_TmpHwnd, Game_DETECTCOLOR, 301, 414))
	//	{
	//		TRACE("���������˺������ˣ�\n");
	//		break;
	//	}
	//	::Sleep(500);
	//}
	::Sleep(1000);
	CRect  r1 = { 0 };
	::GetWindowRect(m_TmpHwnd, &r1);
	if (!DectionAvection(m_TmpHwnd))
		::SwitchToThisWindow(m_TmpHwnd, TRUE);	//���û�������򼤻�
	::SetCursorPos(r1.left + 353, r1.top + 472);
	::PostMessage(m_TmpHwnd, WM_LBUTTONDBLCLK, 0, (LPARAM)353 + 472 * 65536);
	::Sleep(150);
	if (!DectionAvection(m_TmpHwnd))
		::SwitchToThisWindow(m_TmpHwnd, TRUE);	//���û�������򼤻�
	USES_CONVERSION;			//���ַ�ת����ASINC
	oupt(W2A(szUserLoginMessage.m_UserName.GetBuffer()));
	szUserLoginMessage.m_UserName.ReleaseBuffer();		//�ͷŻ�����
	::Sleep(1200);
	if (!DectionAvection(m_TmpHwnd))
		::SwitchToThisWindow(m_TmpHwnd, TRUE);	//���û�������򼤻�
	keybd_event(VK_TAB, 0, 0, 0);
	keybd_event(VK_TAB, 0, KEYEVENTF_KEYUP, 0);
	::Sleep(500);
	oupt(W2A(szUserLoginMessage.m_PassWord.GetBuffer()));
	szUserLoginMessage.m_PassWord.ReleaseBuffer();			//�ͷŻ�����
	::Sleep(100);
	if (!DectionAvection(m_TmpHwnd))
		::SwitchToThisWindow(m_TmpHwnd, TRUE);	//���û�������򼤻�
	::SetCursorPos(r1.left + 371, r1.top + 543);
	keybd_event(VK_RETURN, 0, 0, 0);
	keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0);
	::Sleep(10000);
	//int i = 0;
	//while (true)
	//{
	//	if (i > 100)
	//	{
	//		//��������˾ͷ��صȴ�50��
	//		::TerminateProcess(hpandle, -1);
	//		return FALSE;
	//	}
	//	if (!DectionAvection(m_TmpHwnd))
	//		::SwitchToThisWindow(m_TmpHwnd, TRUE);	//���û�������򼤻�
	//	if (!DetectColor(m_TmpHwnd, Game_DETECTCOLOR, 301, 414))
	//	{
	//		TRACE("����ѡ���ˣ�\n");
	//		break;
	//	}
	//	if (!DetectColor(m_TmpHwnd, 0xD6F0F6, 310, 243))
	//	{
	//		//������������˳���Ϸ
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
	SelectServerLine(m_TmpHwnd, m_sever, m_serline);	//ѡ��ѡ��·
	::Sleep(2000);
	it = szUserLoginMessage.m_GameRole.begin();
	SelectRole(m_TmpHwnd, it->first);		//ѡ������
	DetectionGameState(m_szName);			//�����Ϸ�Ƿ��½�ɹ�
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
	//ö�ٴ��ھ�����ϵķ���
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
		AfxMessageBox(L"�����ھ����Ч");
		return FALSE;
	}
	m_tmphwnd = GetWidgetHwnd(m_Parenthwnd, ndGameRegionID);
	if (!m_tmphwnd)
	{
		AfxMessageBox(L"��ȡ���ھ��ʧ��");
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

// ���ָ���Ĵ����Ƿ񼤻�
BOOL CGameloginDlg::DectionAvection(HWND GameHwnd)
{
	HWND m_AvectionHwnd = NULL;	//����Ĵ��ھ��
	m_AvectionHwnd = ::GetForegroundWindow();
	if (m_AvectionHwnd != GameHwnd)
	{
		return FALSE;
	}
	return TRUE;
}
// ���ָ��λ�õ���ɫ�Ƿ���ȷ
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
// ѡ���½�ķ�������·
BOOL CGameloginDlg::SelectServerLine(HWND hwnd, DWORD ndServerID, DWORD ndLine)
{
	if (!DectionAvection(hwnd))
		::SwitchToThisWindow(hwnd, TRUE);	//���û�������򼤻�
	int severX = 284;		//����������
	int severY = 316 + (ndServerID) * 21;
	int LineX = 515;		//��·����
	int LineY = 316 + (ndLine) * 21;
	CRect r1 = { 0 };
	::GetWindowRect(hwnd, &r1);
	::SetCursorPos(r1.left + severX, r1.top + severY);		//ѡ�������
	::mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);//������� 
	::Sleep(50);
	::mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);//�ɿ����
	::Sleep(1000);
	::SetCursorPos(r1.left + LineX, r1.top + LineY);		//ѡ����·
	::mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);//������� 
	::Sleep(50);
	::mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);//�ɿ����
	::mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);//������� 
	::Sleep(50);
	::mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);//�ɿ����
	::Sleep(1000);
	::SetCursorPos(r1.left + 496, r1.top + 556);		//������Ϸ
	::mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);//������� 
	::Sleep(100);
	::mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);//�ɿ����
	return TRUE;
}
//ѡ�������ɫ
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
		::SwitchToThisWindow(hwnd, TRUE);	//���û�������򼤻�
	::SetCursorPos(r1.left + x, r1.top + y);
	::mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);//������� 
	::Sleep(100);
	::mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);//�ɿ����
	::Sleep(1000);
	//���������ɫ���ֵ�����
	DWORD m_NameBase = NULL;

	//dd[[0xF822E0] + 0x8c0] + 0x228 ��ǰѡ�е���
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
	//������Ϸ

	::SetCursorPos(r1.left + 400, r1.top + 597);
	::mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);//������� 
	::Sleep(100);
	::mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);//�ɿ����

	return TRUE;
}


// �����Ϸ�Ƿ��½�ɹ�
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
			TRACE(L"\n��Ϸ��½�ɹ��ˣ�\n");
			break;
		}
		::Sleep(1000);
		i++;
	}

	::CloseHandle(hpandle);
	return TRUE;
}


// �Զ�����
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
		AfxMessageBox(_T("������ѡ��һ����Ҫɾ��������!"));
		return;
	}
	else
	{
		while (pos)
		{
			int nItem = m_List_Ctrl_Date.GetNextSelectedItem(pos);
			m_List_Ctrl_Date.DeleteItem(nItem);		//ɾ��ָ����
		}
	}


}


void CGameloginDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	MyuserLoginDate::iterator it = G_vector.begin();
	for (; it != G_vector.end();it++)
	{
		LoginGame(*it);
	}
}
