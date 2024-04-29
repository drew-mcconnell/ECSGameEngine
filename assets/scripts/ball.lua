function Start()
    print("start function running")
end

function Update()
    --print("lua!!!")
    local t = ecsManager:getTransform(entity)
    print(t.x)
    --print(t.y)
    
end