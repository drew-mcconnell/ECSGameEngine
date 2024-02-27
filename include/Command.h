#pragma once
#include "ECSManager.h"
#include "Entity.h"

extern ECSManager ecsManager;

class Command{
    public:
        virtual void execute(Entity entity) = 0;
};