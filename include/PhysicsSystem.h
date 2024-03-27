#pragma once
#include "System.h"
#include "ECSManager.h"
#include "constants.h"

extern ECSManager ecsManager;

class PhysicsSystem : public System{
    private:
        void updatePositions(float deltaTime);
        void resolveCollisions(float deltaTime);

    public:
        void Update(float deltaTime);

};