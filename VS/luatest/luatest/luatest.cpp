// luatest.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <process.h>
extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}
#pragma comment(lib,"lua532.lib")
//lua���ú�����ʾ
int FindWay()
{
	printf("Ѱ·call�Ѿ�ִ��\r\n");
	return 1;
}
//��lua���޷�ֱ�ӵ���c++�ĺ�����Ҫͨ��ע���Ժ���ܵ���
//lua ע�ắ���ĸ�ʽ
extern "C" int FindWay_lua(lua_State* L)
{
	int dbarg = 0;
	int i = 1;	//ע�������±��Ǵ�1��ʼ
	int ndNum = 0;
	while (lua_isnumber(L,i))	//�жϸ���������ֵ��һ�����֣�����һ����ת��Ϊ���ֵ��ַ���ʱ������ 1 �����򷵻� 0 ��
	{
		dbarg = lua_tonumber(L, i);	//ȥ��ָ��Ԫ�ص�����
		printf("%d\r\n", dbarg);
		ndNum += dbarg;
		i++;
	}
	printf("%d\r\n", ndNum);
	return FindWay();
}
int main()
{
	lua_State *L=luaL_newstate();	//��ʼ��lua
	luaL_openlibs(L);	//������lua��֧��
	//luaL_dofile(L, "test.lua");
	/*lua_register(lua_state* L,"������",ע�ắ���ĸ�ʽ)*/
	lua_register(L, "FindWaylua", FindWay_lua);
	luaL_dostring(L,"FindWaylua(1,2,3,4,5,6,7)");	//ͨ�����������ú���
	lua_close(L);	//�ر�lua����
	system("pause");
    return 0;
}

