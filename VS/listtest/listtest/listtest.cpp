// listtest.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Cmylist.h"
void testfunc()
{
	LinkedList<int>* test =new LinkedList<int>;
	for (DWORD i = 0; i < 10;i++)
	{
		test->Insert(i, i + 1);
	}
}
int main()
{
	
	testfunc();
    return 0;
}

