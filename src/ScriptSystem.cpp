#include "ScriptSystem.h"

ScriptSystem::ScriptSystem(){
    lua.open_libraries(sol::lib::base);

    //make getComponent() method available to script for transform and physics components
    lua.new_usertype<ECSManager>("ECSManager",
        "ecs_transform", &ECSManager::getComponent<TransformComponent>,
        "ecs_rigidbody", &ECSManager::getComponent<PhysicsComponent>
    );

    //create TransformComponent in lua
    lua.new_usertype<TransformComponent>("Transform",
        "x", &TransformComponent::x,
        "y", &TransformComponent::y,
        "width", &TransformComponent::width,
        "height", &TransformComponent::height
    );

    //create PhysicsComponent in lua
    /*lua.new_usertype<PhysicsComponent>("Rigidbody",
        "x", &PhysicsComponent::x,
        "y", &PhysicsComponent::y,
        "width", &PhysicsComponent::width,
        "height", &PhysicsComponent::height
    );*/

    lua["ecsManager"] = &ecsManager;
    
}

void ScriptSystem::Start(){
    for(auto entity : entities){
        Script script = ecsManager.getComponent<Script>(entity);

        lua.script_file(script.name);
        
        //make entity ID available to lua script
        lua["entity"] = entity;

        //call update function of each script
        lua["Start"];
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