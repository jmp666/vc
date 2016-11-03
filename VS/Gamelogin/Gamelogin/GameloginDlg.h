
// GameloginDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "Global.h"
#include "AddUserMessage.h"
// CGameloginDlg �Ի���
class CGameloginDlg : public CDialogEx
{
// ����
public:
	CGameloginDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAMELOGIN_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// ��Ϸ�����ļ�Ŀ¼
	CString m_Game_Path;
	// �˺ŵ�½��Ϣ
	CListCtrl m_List_Ctrl_Date;
	//����û���½��Ϣ����
	CAddUserMessage m_AddUserMessage;
	//�޸���Ϸ
	BOOL ModifyGameRolled(CString strGamePath, DWORD ndIndex);
	//����ָ��������ϷĿ¼
	BOOL CopyDirectroyPathList(CString strGamePath, DWORD ndIndex);
	//������ϷĿ¼
	BOOL CopyDirectoryFile(CString strSoucer, CString strToDest);
	// ѡ����Ϸ��������
	BOOL SelectGameRegion(DWORD ndGameRegionID);
	//��ȡָ�������ؼ����
	HWND GetWidgetHwnd(HWND ParentHwnd, DWORD GameRegionID);
	//����ö�����ʹ������
#define Game_WT1 0x408
#define Game_START 0x3F2
#define Game_EXIT 0x402
#define Game_DETECTCOLOR 0x0C6CBD
#define Game_FIGUREROLE (LPVOID)0x032364CC
#define Game_CURname 0xF822E0					//dd [[0xF822E0]+0x8c0]+0x228 ��ǰѡ�е�����
	//����ö�����ʹ������
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
	//ѡ��������ɫ����
	TCHAR m_szName[200] = { 0 };
	// ���ָ���Ĵ����Ƿ񼤻�
	BOOL DectionAvection(HWND GameHwnd);
	// ���ָ��λ�õ���ɫ�Ƿ���ȷ
	BOOL DetectColor(HWND hwnd, COLORREF Color, int x, int y);
	// ѡ���½�ķ�������·
	BOOL SelectServerLine(HWND hwnd, DWORD dwndServerID, DWORD ndLine);
	//ѡ�������ɫ
	BOOL SelectRole(HWND hwnd, DWORD ndServerID);
	// �����Ϸ�Ƿ��½�ɹ�
	BOOL DetectionGameState(PTCHAR szGameName);
	afx_msg void OnBnClickedBtnAdd();
	afx_msg void OnBnClickedBtnOpendirecttory();
	// ��½��Ϸ
	BOOL LoginGame(USERLONGINMESSAGE szUserLoginMessage);
	// �Զ�����
	void oupt(char* szbuf);
	afx_msg void OnBnClickedBtnDel();
	afx_msg void OnBnClickedButton1();
};
