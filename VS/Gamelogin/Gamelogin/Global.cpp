#include "stdafx.h"
#include "Global.h"

//��ȡ��Ϸ·��
CString GetGamePathdirectory()
{
	TCHAR szFileDirectoryPath[MAX_PATH];
	ZeroMemory(&szFileDirectoryPath, MAX_PATH);
	TCHAR szDisplayName[MAX_PATH] = { 0 };
	BROWSEINFO bi;
	PIDLIST_ABSOLUTE Pid;
	ZeroMemory(&bi, sizeof BROWSEINFO);
	bi.pszDisplayName = szDisplayName;
	bi.lpszTitle = TEXT("��ѡ����Ϸ��װĿ¼�µ�Launcher.exe�ļ�");
	bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_EDITBOX | BIF_BROWSEINCLUDEFILES;		//ͨ�öԻ��������
	Pid = ::SHBrowseForFolder(&bi);
	::SHGetPathFromIDList(Pid, szFileDirectoryPath);
	TRACE(L"%s\n", szDisplayName);
	TRACE(L"%s\n", szFileDirectoryPath);
	if (wcscmp(szDisplayName, L"launcher.exe") != 0)
	{
		AfxMessageBox(TEXT("��ѡ��Launcher.exe�ļ�"));
		return NULL;
	}
	PTCHAR szFileDirectroryName = nullptr;
	szFileDirectroryName = wcsstr(szFileDirectoryPath, L"launcher.exe");
	if (nullptr != szFileDirectroryName)
	{
		*szFileDirectroryName = '\0';
		TRACE(L"%s\n", szFileDirectoryPath);
	}
	return szFileDirectoryPath;
}
