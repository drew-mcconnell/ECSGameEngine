#pragma once
#include "Collider.h"
#include <typeinfo>

class CircleCollider : public Collider{
    public:
        CircleCollider(){};
        CircleCollider(TransformComponent t){updatePosition(t);};
        
        //void updatePosition(TransformComponent t);
        /*float getUpperBound(){return max.y;};
        float getLowerBound(){return min.y;};
        float getLeftBound(){return min.x;};
        float getRightBound(){return max.x;};*/

        //Vector2 getCenter();

        Vector2 getSurfaceNormalOfCollision(const Collider &other) const;
};