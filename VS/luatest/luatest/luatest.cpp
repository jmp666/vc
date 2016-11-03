// luatest.cpp : 定义控制台应用程序的入口点。
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
//lua调用函数演示
int FindWay()
{
	printf("寻路call已经执行\r\n");
	return 1;
}
//在lua里无法直接调用c++的函数需要通过注册以后才能调用
//lua 注册函数的格式
extern "C" int FindWay_lua(lua_State* L)
{
	int dbarg = 0;
	int i = 1;	//注意它的下标是从1开始
	int ndNum = 0;
	while (lua_isnumber(L,i))	//判断给定索引的值是一个数字，或是一个可转换为数字的字符串时，返回 1 ，否则返回 0 。
	{
		dbarg = lua_tonumber(L, i);	//去除指定元素的内容
		printf("%d\r\n", dbarg);
		ndNum += dbarg;
		i++;
	}
	printf("%d\r\n", ndNum);
	return FindWay();
}
int main()
{
	lua_State *L=luaL_newstate();	//初始化lua
	luaL_openlibs(L);	//打开所有lua库支持
	//luaL_dofile(L, "test.lua");
	/*lua_register(lua_state* L,"函数名",注册函数的格式)*/
	lua_register(L, "FindWaylua", FindWay_lua);
	luaL_dostring(L,"FindWaylua(1,2,3,4,5,6,7)");	//通过函数名调用函数
	lua_close(L);	//关闭lua环境
	system("pause");
    return 0;
}

