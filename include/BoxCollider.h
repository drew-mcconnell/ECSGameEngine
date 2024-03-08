#pragma once
#include "Collider.h"

class BoxCollider : public Collider{
    public:
        
        BoxCollider(){};
        BoxCollider(TransformComponent t){updatePosition(t);};
        
        void updatePosition(TransformComponent t);
        int getUpperBound(){return upperBound;};
        int getLowerBound(){return lowerBound;};
        int getLeftBound(){return leftBound;};
        int getRightBound(){return rightBound;};
};