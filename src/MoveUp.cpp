#include "MoveUp.h"

void MoveUp::execute(Entity entity){
    auto &physics = ecsManager.getComponent<PhysicsComponent>(entity);

    physics.yVelocity = -200;
}