#include "MoveDown.h"

void MoveDown::execute(Entity entity){
    auto &physics = ecsManager.getComponent<PhysicsComponent>(entity);

    physics.yVelocity = 200;
}