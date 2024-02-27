#include "PhysicsSystem.h"

void PhysicsSystem::Update(float deltaTime){
    for(auto & entity : entities){
        auto &transform = ecsManager.getComponent<TransformComponent>(entity);
        auto &physics = ecsManager.getComponent<PhysicsComponent>(entity);

        transform.x += physics.xVelocity * deltaTime;
        transform.y += physics.yVelocity * deltaTime;
        if(transform.y < 0){
            transform.y = 0;
            physics.yVelocity *= -1;
        }
        else if(transform.y + transform.height > 600){
            transform.y = (600 - transform.height);
            physics.yVelocity *= -1;
        }
        if(transform.x < 0){
            transform.x = 0;
            physics.xVelocity *= -1;
        }
        else if(transform.x + transform.width > 800){
            transform.x = (800 - transform.width);
            physics.xVelocity *= -1;
        }
    }
}