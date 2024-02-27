#pragma once
#include "System.h"
#include "ECSManager.h"
#include "constants.h"

extern ECSManager ecsManager;

class PhysicsSystem : public System{
    private:


    public:
        void Update(float deltaTime);

};