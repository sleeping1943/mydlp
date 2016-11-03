#include "lua_engine.h"
#include "var.h"

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

    var _lua2var(lua_State* L,int index) {
        switch (lua_type(L,index)) {
            case LUA_TNUMBER:
                return var((int)lua_tointeger(L,index));
                break;
            case LUA_TSTRING: 
                return var(lua_tostring(L,index));
                break;
            case LUA_TBOOLEAN:
                return var(lua_toboolean(L,index));
                break;
            case LUA_TTABLE:{
                /*
                 *递归遍历lua的table
                 */
                vmap v;
                lua_pushnil(L);

                while (lua_next(L,index) != 0) {
                    v.insert(std::pair<var,var>(_lua2var(L,-2),_lua2var(L,-1)));  
                    lua_pop(L,1);
                }
                return v;
            }
                break;
            case LUA_TNIL:
                break;
            case LUA_TUSERDATA:
            case LUA_TLIGHTUSERDATA:
            case LUA_TTHREAD:
            case LUA_TFUNCTION:
            default:
                break;
        } 
        return var();
    }

    varray lua2var (lua_State* L) {
        varray v;  
        int i = lua_gettop(L);
        for (; i > 0; --i) {
            switch (lua_type(L,i)) {
                case LUA_TNIL:
                    v.push_back(var(0));
                    break;
                case LUA_TNUMBER:
                    v.push_back(var((int)lua_tointeger(L,i)));
                    break;
                case LUA_TBOOLEAN:
                    v.push_back(var((bool)lua_toboolean(L,i)));
                    break;
                case LUA_TSTRING:
                    v.push_back(var(lua_tostring(L,i)));
                    break;
                case LUA_TTABLE:
                    v.push_back(_lua2var(L,i));
                    break;
                case LUA_TUSERDATA:
                    /*
                     *TODO
                     */
                    break;
                case LUA_TTHREAD:
                    /*
                     *TODO
                     */
                    break;
                case LUA_TFUNCTION:
                    /*
                     *TODO
                     */
                    break;
                case LUA_TLIGHTUSERDATA:
                    /*
                     *TODO
                     */
                    break;
                default:
                    break;
            }    
            lua_pop(L,1);
        }
       return v;
     }

    varray var2lua (varray v,lua_State* L) {
        /* *varray v;  */
        for (const var& tv : v) {
            switch (tv.type()) {
                case t_int:
                    lua_pushinteger(L,tv.get_number()); 
                    break;
                case t_bin:
                case t_str:{
                    std::string str = tv.get_str();
                    lua_pushlstring(L,str.c_str(),str.size());
                }
                    break;
                case t_bool:
                    lua_pushboolean(L,tv.get_bool());
                    break;
                case t_map:
                    /*
                     *TODO
                     */
                    break;
                case t_array:
                    /*
                     *TODO
                     */
                    break;
                default:
                    /*
                     *TODO
                     */
                    break;
            } 
        }
        return v;
    }

}};
