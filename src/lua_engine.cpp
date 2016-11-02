#include "lua_engine.h"

namespace slp{namespace script{

    
    void define (string name,struct luaL_reg* regs,lua_State* L) {
       luaL_newmetatable(L,name.c_str());  
        for (struct luaL_reg* p = regs; p->name && p->func; ++p) {
            lua_pushstring(L,p->name); 
            lua_pushcfunction(L,p->func);
            lua_settable(L,-3);
        }
        
        lua_setglobal(L,name.c_str());
    }
}};
