// test.cpp : �������̨Ӧ�ó������ڵ㡣
//
// ���ַ���ת����ASCLL�� 
#include "stdafx.h"
#include <Windows.h>
/*void __cdecl DbgPrin_Mine(const char *format, ...)
{
#ifdef _DEBUG
	char szbufFormat[0x1000];
	char szBufFormat_Game[0x1008]="Game::";
	va_list  arglist;
	va_start(arglist, format);
	vsprintf_s(szbufFormat, format, arglist);
	strcat_s(szBufFormat_Game, szbufFormat);
	OutputDebugStringA(szBufFormat_Game);
#endif
}
int* GetcharIN(char* str,DWORD & len)
{
	int* lstr = (int*)malloc(len*sizeof(int));
	if (!lstr)
	{
		return NULL;
	}
	memset(lstr, 0, len*sizeof(int));
	size_t i = 0;
	unsigned short ndbuf = 0;
	for (; i < strlen(str);i++)
	{
		unsigned char  pdchar= *(str + i);
		if ((pdchar & 0x80)==0x80)
		{
			ndbuf = pdchar;
			*(lstr + i) = ndbuf;
			//printf("%d\n", ndbuf);
		}
		else
		{
			*(lstr + i) = *(str + i);
			//printf("%d\r\n", *(str + i));
		}
	}
	len = strlen(str);
	return lstr;	//���ʧ�ܷ���0
}
int main()
{
	char* str = "ajkdsx���ddcx";
	DWORD  len = 0;
	int* p1 = GetcharIN(str, len);
	if (len!=NULL &&p1!=NULL)
	{
		for (size_t  i = 0; i < len;i++)
		{
			printf("%d\r\n", *(p1 + i));
		}
	}
	getchar();
	free(p1);
    return 0;
}
*/
int found(int* arr, int x, int y, int val)
{
	int m = x + (y - x) / 2;
	if (x > y)//�������û���ҵ��𰸣�����-1
		return -1;
	else
	{
		if (arr[m] == val)
			return m;//�ҵ�!����λ��.
		else if (arr[m] > val)
			return found(arr, x, m - 1, val);//�����
		else
			return found(arr, m + 1, y, val);//���ұ�
	}
}
int main(int argc, char* argv[])
{
	int a[100] = {1,2,3,5,12,12,12,15,29,55};
	int cl = 0;
	cl = found(a, 0, 9, 15);
	return 0;
}
