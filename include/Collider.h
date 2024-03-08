#pragma once
#include "TransformComponent.h"

class Collider{
    public:

    int upperBound;
    int lowerBound;
    int leftBound;
    int rightBound;

    Collider():upperBound(0),lowerBound(0),leftBound(0),rightBound(0){};
    //Collider(TransformComponent t){updatePosition(t);};

    virtual void updatePosition(TransformComponent t)=0;
    virtual int getUpperBound() = 0;//{return upperBound;};
    virtual int getLowerBound()=0;//{return lowerBound;};
    virtual int getLeftBound()=0;//{return leftBound;};
    virtual int getRightBound()=0;//{return rightBound;};
};