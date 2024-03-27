#pragma once
#include "Vector2.h"

class PhysicsComponent{
    public:
        Vector2 velocity;
        //float xVelocity;
        //float yVelocity;

        bool isKinematic;
        float elasticity;
        float mass;

        //float acceleration;
        //bool gravity;
};