#include "ScriptSystem.h"

void ScriptSystem::Update(){
    sol::state lua;
	lua.open_libraries(sol::lib::base);

    for(auto entity : entities){
        Script script = ecsManager.getComponent<Script>(entity);

        

        lua.script_file(script.name);
        int x = lua["f"](30);
        int y = lua["f"](5);
    }
}