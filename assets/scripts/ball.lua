function Start()

end

function Update()
    print("lua!!!")
    local t = ecsManager:ecs_transform(entity)
    print(t.x)
    print(t.y)
    
end