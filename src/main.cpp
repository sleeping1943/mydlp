/************************************
*
*此源文件用于测试lua与C++互相调用
*filename : main.cpp
*author   : sleeping
*email    : csleeping@163.com
*date     : 2016年11月01日 星期二 10时13分05秒
*
************************************/
#include <iostream>
#include <string>

#ifdef __cplusplus
extern "C" {
#endif
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
#ifdef __cplusplus
}
#endif
#include "var.h"

using std::cout;
using std::endl;
using std::string;
using slp::script::var;

int main(int argc,char** argv) {
    if (2 != argc) {
        cout << "Useage: testlua <filename> " << endl;
        return -1;
    } 
#if 0
    lua_State *L = luaL_newstate();
    if (!L) {
        cout << "luaL_newstate error!" << endl; 
        return -2;
    }

    /*
     *开启辅助库，否则基本的print函数等无法调用
     */
    luaL_openlibs(L);

    int ret = luaL_loadfile(L,argv[1]);
    switch (ret) {
        case LUA_ERRSYNTAX:
                cout << "语法错误!" << endl;
                return -3;
                break;
        case LUA_ERRMEM:
                cout << "内存分配错误!" << endl;
                return -4;
                break;
        default:
                break;
    }
    
    lua_pcall(L,0,0,0);
#endif
    {
            using slp::script::varray;
            varray arr;
            std::string str = "test ";
            for (int i=0; i < 3; ++i) {
                var tmp;
                str += std::to_string(i); 
                tmp = str; 
                tmp.print_type();
                cout << "before\n";
                var v(tmp);
                cout << "after\n";
                arr.push_back(tmp);
            }
#if 1
            for (const auto& t : arr) {
                    std::cout << "v:" << t << endl; 
            }
#endif
    }

    getchar();
	return 0;
}
