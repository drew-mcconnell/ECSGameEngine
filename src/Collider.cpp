#include "Collider.h"

void Collider::updatePosition(TransformComponent t){
    max.y = t.y + t.height / 2;
    min.y = t.y - t.height / 2;
    min.x = t.x - t.width / 2;
    max.x = t.x + t.width / 2;
}

void Collider::empty() {
    min.x = min.y = FLT_MAX;
    max.x = max.y = -FLT_MAX;
}

void Collider::add(const Vector2 &p) {
    if (p.x < min.x) min.x = p.x;
    if (p.x > max.x) max.x = p.x;
    if (p.y < min.y) min.y = p.y;
    if (p.y > max.y) max.y = p.y;
}

Vector2 Collider::getCenter() const {
    return Vector2(max.x - (max.x - min.x) / 2, max.y - (max.y - min.y) / 2);
}

//---- TODO - can I use composition to turn this method into an instance variable
// that calls a different function based on whether it's a box or a circle?
// would eliminate the need for virtual functions in Colliders and fix corner circle
// collision issue
bool Collider::isColliding(const Collider &other) const{
    
    //if width and height of union are both smaller than 
    //the combined width and height of the two objects

    Collider u = colliderUnion(*this, other);

    //------ consider doing inline calculations here instead of function calls if speed is an issue -----
    bool xCollision = u.width() < width() + other.width();
    bool yCollision = u.height() < height() + other.height();
    
    return xCollision && yCollision;
}

Vector2 Collider::getSurfaceNormalOfCollision(const Collider &other) const{
    //https://gamedev.stackexchange.com/questions/48816/how-to-calculate-collision-normal-between-two-axisalignedboxs

    //get the intersection of the two colliders
    Collider intersection = colliderIntersection(*this, other);

    //axis with the smaller penetration depth is assumed to be the collision axis
    //then calculate the surface normal direction and return
    if(intersection.width() < intersection.height()){
        return getCenter().x < other.getCenter().x ? Vector2(-1.0f, 0) : Vector2(1.0f, 0);
    }
    else{
        return getCenter().y < other.getCenter().y ? Vector2(0, -1.0f) : Vector2(0, 1.0f);
    }
}

//calculates and returns union of 2 Colliders
Collider colliderUnion(const Collider &a, const Collider &b){
    
    //https://gamemath.com/book/geomprims.html#computing_aabbs
    Collider u;
    u.empty();
    u.add(a.min);
    u.add(b.min);
    u.add(a.max);
    u.add(b.max);

    return u;

}

//calculates and returns intersection of 2 Colliders
Collider colliderIntersection(const Collider &a, const Collider&b){

    Collider intersection;
    intersection.empty();

    intersection.min = Vector2(fmax(a.min.x, b.min.x), fmax(a.min.y, b.min.y));
    intersection.max = Vector2(fmin(a.max.x, b.max.x), fmin(a.max.y, b.max.y));

    return intersection;
}