
do
function foo(...)  
        for i = 1, select('#', ...) do  -->获取参数总数
            local arg = select(i, ...); -->读取参数
	    local test = select(1, ...);
	    print("test", test);
            print("arg", arg);  
        end  
    end  
 
    foo(23, 21, 24, 25);  
end
