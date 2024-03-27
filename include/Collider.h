#pragma once
#include "float.h"
#include "math.h"
#include "TransformComponent.h"
#include "Vector2.h"


class Collider{
    public:

    /*//upperBound is higher on screen, but lower in numbers
    float upperBound;
    //lowerBound is lower on screen, but higher in numbers
    float lowerBound;
    float leftBound;
    float rightBound;*/

    Vector2 min;
    Vector2 max;

    Collider():min(Vector2()),max(Vector2()){};
    //Collider():upperBound(0),lowerBound(0),leftBound(0),rightBound(0){};
    //Collider(TransformComponent t){updatePosition(t);};

    virtual void updatePosition(TransformComponent t);
    virtual float getUpperBound() const {return max.y;/*upperBound;*/};
    virtual float getLowerBound() const {return min.y;/*lowerBound;*/};
    virtual float getLeftBound() const {return min.x;/*leftBound;*/};
    virtual float getRightBound() const {return max.x;/*rightBound;*/};

    void empty();
    void add(const Vector2 &p);
    virtual Vector2 getCenter() const;

    float extentX() const{return (max.x - min.x) / 2;/*(rightBound - leftBound) / 2;*/}
    float extentY() const{return (max.y - min.y) / 2;/*(lowerBound - upperBound) / 2;*/}

    float width() const {return max.x - min.x;};
    float height() const {return max.y - min.y;}; 

    virtual bool isColliding(const Collider &other) const;

    virtual Vector2 getSurfaceNormalOfCollision(const Collider &other) const;
};

Collider colliderUnion(const Collider &a, const Collider &b);
Collider colliderIntersection(const Collider &a, const Collider&b);