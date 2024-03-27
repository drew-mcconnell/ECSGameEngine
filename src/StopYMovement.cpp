#include "StopYMovement.h"

void StopYMovement::execute(Entity entity){
    auto &physics = ecsManager.getComponent<PhysicsComponent>(entity);

    physics.velocity.setY(0);//yVelocity = 0;
}