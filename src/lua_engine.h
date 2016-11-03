/************************************
*
*此头文件...
*filename : src/lua_engine.h
*author   : sleeping
*email    : csleeping@163.com
*date     : 2016年11月02日 星期三 16时22分02秒
*
************************************/
#ifndef _SLP_SRC_LUA_ENGINE_H
#define _SLP_SRC_LUA_ENGINE_H

#ifdef __cplusplus
extern "C" {
#endif
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
#ifdef __cplusplus
}
#endif
#include <string>
#include "var.h"

namespace slp{namespace script{

    using std::string;
    varray lua2var (lua_State* L);
    /* *varray var2lua (lua_State* L); */
    varray var2lua (varray v,lua_State* L);
    void define (string name,struct luaL_reg* regs,lua_State* L);

    template <varray (*pfunc)(varray,lua_State*)>
    int lfun (lua_State* L) {
        varray v;
        /* *v.push_back(var(1)); */
        v = pfunc(lua2var(L),L); 
        var2lua(v,L);
        return v.size();
    }
}};


#endif /*_SLP_SRC_LUA_ENGINE_H*/
