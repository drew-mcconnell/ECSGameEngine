#include "PhysicsSystem.h"

void PhysicsSystem::Update(float deltaTime){
    for(auto & entity : entities){
        auto &transform = ecsManager.getComponent<TransformComponent>(entity);
        auto &physics = ecsManager.getComponent<PhysicsComponent>(entity);
        
        //----- TODO - make generic for any collider
        auto collider = ecsManager.getComponent<Collider *>(entity);

        transform.x += physics.xVelocity * deltaTime;
        transform.y += physics.yVelocity * deltaTime;

        //update collider before testing bounds collisions
        collider->updatePosition(transform);

        if(collider->getUpperBound() < 0){
            transform.y = 0;
            physics.yVelocity *= -1;
        }
        else if(collider->getLowerBound() > 600){
            transform.y = (600 - transform.height);
            physics.yVelocity *= -1;
        }
        if(collider->getLeftBound() < 0){
            transform.x = 0;
            physics.xVelocity *= -1;
        }
        else if(collider->getRightBound() > 800){
            transform.x = (800 - transform.width);
            physics.xVelocity *= -1;
        }

        //re-update collider after resolving bounds collisions
        collider->updatePosition(transform);
    }
}