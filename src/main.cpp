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


void test_array();
void test_get_map ();
int test_lua_file(const char* fpath,luaL_reg* mv,lua_State** pL);

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

varray testm (varray arg,lua_State* L) {
    varray v;
    cout << "testm" << endl;
    for (const auto& t : arg) {
        if (slp::script::t_map == t.type()) {
            for (const auto& tt : t.get_map()) {
                cout << "first:" << tt.first 
                     << " second:" << tt.second << endl;
            }

        } 
    }
    slp::script::vmap vm;
    vm.insert(std::pair<var,var>("var-key","var-value"));
    v.push_back(var(vm));
    return v;
}

luaL_Reg mv[] = {
    {"testv",slp::script::lfun<testv>},
    {"testm",slp::script::lfun<testm>},
    {NULL,NULL}
};

int main(int argc,char** argv) {
    if (2 != argc) {
        cout << "Useage: testlua <filename> " << endl;
        return -1;
    } 
    lua_State* L; 
    test_lua_file(argv[1],mv,&L);
    /*
     *getchar();
     */
	return 0;
}

int test_lua_file(const char* fpath,luaL_reg* mv,lua_State** pL) {
#if 1
    *pL = luaL_newstate();
    lua_State* L = *pL;
    if (!L) {
        cout << "luaL_newstate error!" << endl; 
        return -2;
    }

    /*
     *开启辅助库，否则基本的print函数等无法调用
     */
    luaL_openlibs(L);

    slp::script::define("f",mv,L);
    int ret = luaL_loadfile(L,fpath);
    switch (ret) {
        case LUA_ERRSYNTAX:
                cout << "语法错误!" << std::string(fpath) << endl;
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
    return 0;
}

void test_get_map () {

#if 1
    slp::script::vmap vm;
    string str = "test-";
    for (int i=0; i < 5; ++i) {
        vm.insert(std::pair<var,var>(std::to_string(i),str+std::to_string(i))); 
    }
    var v = vm;
    for (const auto& tv : v.get_map()) {
        cout << "first:" << tv.first << " second:" << tv.second << endl; 
    }
#endif
}

void test_array() {
#if 1
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
}

