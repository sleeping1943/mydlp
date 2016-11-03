#!/usr/bin/lua


local func = function (str) 
                print("The string:"..str)
             end


print("hello lua!")
do 
    local ret = f.testv("lua_testv")
    --[[
       [print(type(ret))
       ]]
    print(ret)
end

do
    local ret0,ret1,ret2 = f.testv("just to test the lua_engine",23,false)
    --[[
       [print(type(ret))
       ]]
    print("ret0:" .. ret0)
    print("ret1:" .. ret1)
    print("ret2:" .. ret2)
end
