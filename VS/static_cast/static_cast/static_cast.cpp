// static_cast.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"


int main()
{
	int array[] = { 5,4,3,2,1 };
	int* p = (int*)((int)array + 1);
	printf("%X %X\n", (int)array,*(int*)((int)array+1));
	printf("%X\n", *p);
	system("pause");
    return 0;
}

