#include "StopYMovement.h"

void StopYMovement::execute(Entity entity){
    auto &physics = ecsManager.getComponent<PhysicsComponent>(entity);

    physics.yVelocity = 0;
}