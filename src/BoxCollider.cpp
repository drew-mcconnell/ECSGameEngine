#include "BoxCollider.h"

/*void BoxCollider::updatePosition(TransformComponent t){
    max.y = t.y - t.height / 2;
    min.y = t.y + t.height / 2;
    min.x = t.x - t.width / 2;
    max.x = t.x + t.width / 2;
}*/

/*bool BoxCollider::isColliding(Collider &other){
    bool xCollision = (leftBound < other.leftBound && other.leftBound < rightBound) || (other.leftBound < leftBound && leftBound < other.rightBound);
    bool yCollision = (upperBound < other.upperBound && other.upperBound < lowerBound) || (other.upperBound < upperBound && upperBound < other.lowerBound);
    return xCollision && yCollision;
}*/

/*Vector2 BoxCollider::getCenter(){
    return Vector2((max.x - min.x) / 2, (max.y - min.y) / 2);//Vector2(rightBound - (rightBound - leftBound) / 2, lowerBound - (lowerBound - upperBound) / 2);
}*/