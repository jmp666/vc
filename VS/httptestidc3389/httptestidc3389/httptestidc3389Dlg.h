
// httptestidc3389Dlg.h : ͷ�ļ�
//

#pragma once

#import "C:\\Windows\\System32\\winhttpcom.dll" no_namespace
// Chttptestidc3389Dlg �Ի���
class Chttptestidc3389Dlg : public CDialogEx
{
// ����
public:
	Chttptestidc3389Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HTTPTESTIDC3389_DIALOG };
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
	afx_msg void OnBnClickedBtnLogin();
BOOL loginWeb(CString cstr_user, CString cstr_pass);
//����ָ��
IWinHttpRequestPtr Pwinhttp;
// ȡ�ı��м�
CString GetStringMiddle(CString Cstr_Source, CString Cstr_left, CString Cstr_right);
afx_msg void OnBnClickedBtnGet();
};
