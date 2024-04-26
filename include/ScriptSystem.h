#pragma once

#include "System.h"
#include "ECSManager.h"
#include "Script.h"
#include "sol/sol.hpp"

extern ECSManager ecsManager;

class ScriptSystem : public System{
    private:
        sol::state lua;

    public:
        ScriptSystem();
        void Start();
        void Update();

};