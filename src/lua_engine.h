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


namespace slp{namespace script{

    using std::string;
    void define (string name,struct luaL_reg* regs,lua_State* L);
}};


#endif /*_SLP_SRC_LUA_ENGINE_H*/
