#include "BoxCollider.h"

void BoxCollider::updatePosition(TransformComponent t){
    upperBound = t.y;
    lowerBound = t.y + t.height;
    leftBound = t.x;
    rightBound = t.x + t.width;
}