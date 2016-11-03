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
#include "lua_engine.h"
#include "var.h"

using std::cout;
using std::endl;
using std::string;
using slp::script::var;
using slp::script::varray;

/*
 *template <class T>
 *int test(lua_State* L) {
 *    cout << "test" << endl;
 *    T* p = new T;
 *    *p = "This type of T is string!";
 *    cout << *p << endl;
 *    delete p;
 *    p = NULL;
 *    return 0;
 *}
 *luaL_Reg m[] =  {
 *        {"test",test<string>},
 *        {NULL,NULL}
 *    };
 */

varray testv (varray arg,lua_State* L) {
    varray v;
    for (const var& tv : arg) {
        tv.print_type();
        cout << tv << endl;
        std::string str = "testv over!";
        str += tv.get_type_str();
        v.push_back(var(str));
    }
    return v;
}

luaL_Reg mv[] = {
    {"testv",slp::script::lfun<testv>},
    {NULL,NULL}
};

int main(int argc,char** argv) {
    if (2 != argc) {
        cout << "Useage: testlua <filename> " << endl;
        return -1;
    } 
#if 1
    lua_State *L = luaL_newstate();
    if (!L) {
        cout << "luaL_newstate error!" << endl; 
        return -2;
    }

    /*
     *开启辅助库，否则基本的print函数等无法调用
     */
    luaL_openlibs(L);

    slp::script::define("f",mv,L);
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


#if 0
    {
        using slp::script::varray;
        varray arr;
        std::string str = "test ";
        for (int i=0; i < 3; ++i) {
            str += std::to_string(i); 
            arr.push_back(var(str));
        }
        for (const auto& t : arr) {
            std::cout << "v:" << t << endl; 
        }

        var v_arr = arr;
        for (const auto& t : v_arr.get_array()) {
            std::cout << "v_arr:" << t << endl; 
        }

        var v2 = 1;
    }
#endif

    getchar();
	return 0;
}
