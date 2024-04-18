#pragma once

#include "System.h"
#include "ECSManager.h"
#include "Script.h"
#include "sol/sol.hpp"

extern ECSManager ecsManager;

class ScriptSystem : public System{
    private:


    public:
        void Update();

};