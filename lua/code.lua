t = {};
   
-- 使用一个table作为t的key值
key1 = {name = "key1"};
t[key1] = 1;
key1 = nil;
   
-- 又使用一个table作为t的key值
key2 = {name = "key2"};
t[key2] = 1;
key2 = nil;
   
-- 强制进行一次垃圾收集
collectgarbage();
   
for key, value in pairs(t) do
    print(key.name .. ":" .. value);
end