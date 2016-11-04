#!/usr/bin/lua


local func = function (str) 
                print("The string:"..str)
             end



local func2 = function()
    local ret = f.testv("lua_testv")
    --[[
       [print(type(ret))
       ]]
    print(ret)
end

local func3 = function()
    local ret0,ret1,ret2 = f.testv("just to test the lua_engine",23,false)
    --[[
       [print(type(ret))
       ]]
    print("ret0:" .. ret0)
    print("ret1:" .. ret1)
    print("ret2:" .. ret2)
end

local test_map = function ()
   local m = {};
   m.key1 = "value1"
   local m2 = {};
   m2.key2 = "value2"
   local mm = f.testm(m,m2) 
   if "table" == type(mm) then
        for k,v in pairs(mm) do
            print("lua-key:" .. k .. " lua-value:" ..v) 
        end
   else 
        print("type of mm:" .. type(mm))
   end
end

print("/root/test/myluabind/test.lua")
test_map()
