#include "Collider.h"

class CircleCollider : public Collider{
    public:
        CircleCollider(){};
        CircleCollider(TransformComponent t){updatePosition(t);};
        
        void updatePosition(TransformComponent t);
        int getUpperBound(){return upperBound;};
        int getLowerBound(){return lowerBound;};
        int getLeftBound(){return leftBound;};
        int getRightBound(){return rightBound;};
};