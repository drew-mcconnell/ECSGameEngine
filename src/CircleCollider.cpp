#include "CircleCollider.h"

/*void CircleCollider::updatePosition(TransformComponent t){
    max.y = t.y + t.height / 2;
    min.y = t.y - t.height / 2;
    min.x = t.x - t.width / 2;
    max.x = t.x + t.width / 2;
}*/

/*Vector2 CircleCollider::getCenter(){
    return Vector2((max.x - min.x) / 2, (max.y - min.y) / 2);
}*/

Vector2 CircleCollider::getSurfaceNormalOfCollision(const Collider &other) const{
    //const char * otherTypeName = typeid(typeof(other)).name();

    //if other is not circle collider, default to AABB surface normal
    //otherwise, calculate surface normal for two circles
    if(typeid(other).name() != typeid(CircleCollider).name()){
        return Collider::getSurfaceNormalOfCollision(other);
    }
    else{
        return Vector2::normalized(getCenter() - other.getCenter());
    }
}