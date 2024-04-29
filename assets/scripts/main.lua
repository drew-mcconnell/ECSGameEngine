function Start()
    print("main is running")

    --create a ball
    createBall()



end

function createBall()
    print("creating balls")

    --for i=0,4,1 do
        --create new entity
        local e = ecsManager:createEntity()

        -- TODO - how or if to add entity to entities[] in GameManager?

        --create and add transform to entity
        local t = Transform.new() 
        t.x = math.random(100, 700)
        t.y = math.random(100, 500)
        t.width = 50
        t.height = 50

        ecsManager:addTransform(e, t)

        --create and add image renderer to entity
        local i = Image.new("assets/textures/ball.png")
        r = Render.new(i)

        ecsManager:addRender(e, r)

        --create and add rigidbody to entity with random-ish velocity
        -- TODO - implement random seed
        local velocity = Vector2.new()
        velocity.x = math.random(-200, 200)
        velocity.y = math.random(-200, 200)
        rb = Rigidbody.new()
        rb.velocity = velocity
        rb.isKinematic = false
        rb.elasticity = 1
        rb.mass = 1

        ecsManager:addRigidbody(e, rb)

        -- TODO - figure out memory management from lua created objects
        collider = CircleCollider.new(t)

        ecsManager:addCollider(e, collider)
    --end

end

function Update()

end