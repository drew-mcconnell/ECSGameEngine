#pragma once
#include "Collider.h"

class BoxCollider : public Collider{
    public:
        
        BoxCollider(){};
        BoxCollider(TransformComponent t){updatePosition(t);};
        
        //void updatePosition(TransformComponent t);
        //float getUpperBound(){return max.y;/*upperBound;*/};
        //float getLowerBound(){return min.y;/*lowerBound;*/};
        //float getLeftBound(){return min.x;/*leftBound;*/};
        //float getRightBound(){return max.x;/*rightBound;*/};

        //Vector2 getCenter();

        //bool isColliding(Collider &other);


};