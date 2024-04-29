#include "ScriptSystem.h"

ScriptSystem::ScriptSystem(){
    lua.open_libraries(sol::lib::base, sol::lib::math);

    //make getComponent() method available to script for transform and physics components
    lua.new_usertype<ECSManager>("ECSManager",
        "createEntity", &ECSManager::createEntity,
        "getTransform", &ECSManager::getComponent<TransformComponent>,
        "getRigidbody", &ECSManager::getComponent<PhysicsComponent>,
        "addTransform", &ECSManager::addComponent<TransformComponent>, 
        "addRigidbody", &ECSManager::addComponent<PhysicsComponent>,
        "addRender", &ECSManager::addComponent<RenderComponent>,
        "addCollider", &ECSManager::addComponent<Collider *>,
        "addTag", &ECSManager::addComponent<Tag>,
        "addScript", &ECSManager::addComponent<Script>
    );

    //create TransformComponent in lua
    lua.new_usertype<TransformComponent>("Transform",
        "x", &TransformComponent::x,
        "y", &TransformComponent::y,
        "width", &TransformComponent::width,
        "height", &TransformComponent::height
    );

    //create Vector2 in lua
    lua.new_usertype<Vector2>("Vector2",
        "x", &Vector2::x,
        "y", &Vector2::y
    );

    //create PhysicsComponent in lua
    lua.new_usertype<PhysicsComponent>("Rigidbody",
        "velocity", &PhysicsComponent::velocity,
        "isKinematic", &PhysicsComponent::isKinematic,
        "elasticity", &PhysicsComponent::elasticity,
        "mass", &PhysicsComponent::mass
    );

    //create Colliders in lua
    lua.new_usertype<Collider>("Collider",
        "min", &Collider::min,
        "max", &Collider::max
    );
    lua.new_usertype<BoxCollider>("BoxCollider",
        sol::constructors<BoxCollider(TransformComponent)>(),
        sol::base_classes, sol::bases<Collider>()
    );
    lua.new_usertype<CircleCollider>("CircleCollider",
        sol::constructors<CircleCollider(TransformComponent)>(),
        sol::base_classes, sol::bases<Collider>()
    );

    //create RGBA in lua
    lua.new_usertype<RGBA>("RGBA",
        "red", &RGBA::red,
        "green", &RGBA::green,
        "blue", &RGBA::blue,
        "alpha", &RGBA::alpha
    );

    //create Shapes in lua
    lua["Shapes"] = lua.create_table_with(
        "RECT", Shapes::RECT,
        "CIRCLE", Shapes::CIRCLE,
        "IMAGE", Shapes::IMAGE
    );


    //create Image in lua
    lua.new_usertype<Image>("Image",
        sol::constructors<Image(std::string)>(),
        "fileName", &Image::mFileName,
        "setImage", &Image::setImage
    );

    //create RenderComponent in lua
    lua.new_usertype<RenderComponent>("Render",
        //sol::constructors<RenderComponent(RGBA, Shapes)>(),
        sol::constructors<RenderComponent(Image)>(),
        "color", &RenderComponent::mColor,
        "shape", &RenderComponent::mShape,
        "image", &RenderComponent::mImage
    );

    lua["ecsManager"] = &ecsManager;
    
}

void ScriptSystem::Start(){
    for(auto entity : entities){
        Script script = ecsManager.getComponent<Script>(entity);

        lua.script_file(script.name);
        
        //make entity ID` available to lua script
        lua["entity"] = entity;

        //call update function of each script
        lua["Start"]();
    }
}

void ScriptSystem::Update(){
    //sol::state lua;
	//lua.open_libraries(sol::lib::base);

    for(auto entity : entities){
        Script script = ecsManager.getComponent<Script>(entity);

        lua.script_file(script.name);

        //call update function of each script
        lua["Update"]();

        //call collision method of each script if necessary
    }
}

void testMethod(){
    //std::cout << 
}