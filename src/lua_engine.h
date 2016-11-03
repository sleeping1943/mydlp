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

    var _lua2var(lua_State* L,int index);
    /**
     * @brief lua栈中的数据转换并填充到C++的var中
     *
     * @param L lua虚拟机
     *
     * @return  lua数据的var形式
     */
    varray lua2var (lua_State* L);


    /**
     * @brief C++中的数据转换并放入lua栈中
     *
     * @param v 包含了C++函数返回给lua的数据
     * @param L lua虚拟机
     *
     * @return ...
     */
    varray var2lua (varray v,lua_State* L);


    /**
     * @brief 定义lua全局对象，并绑定C++函数到lua对象的元表
     *
     * @param name 全局对象名
     * @param regs C++函数
     * @param L lua虚拟机
     */
    void define (string name,struct luaL_reg* regs,lua_State* L);


    /**
     * @brief 关联C++函数和lua标准C函数
     *
     * @tparam (*pfunc)(varray
     * @tparam lua_State*)
     * @param L lua虚拟机
     *
     * @return C++返回给lua的返回值个数
     */
    template <varray (*pfunc)(varray,lua_State*)>
    int lfun (lua_State* L) {
        varray v;
        v = pfunc(lua2var(L),L); 
        var2lua(v,L);
        return v.size();
    }
}};


#endif /*_SLP_SRC_LUA_ENGINE_H*/
