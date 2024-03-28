#include "MoveUp.h"

void MoveUp::execute(Entity entity){
    auto &physics = ecsManager.getComponent<PhysicsComponent>(entity);

    physics.velocity.setY(-200);
}