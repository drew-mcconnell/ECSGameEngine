#include "MoveDown.h"

void MoveDown::execute(Entity entity){
    auto &physics = ecsManager.getComponent<PhysicsComponent>(entity);

    physics.velocity.setY(200);//yVelocity = 200;
}