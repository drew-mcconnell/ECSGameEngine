#include "Vector2.h"
#include <cmath>
float Vector2::magnitude(){
    return (std::sqrt(x*x + y*y));
}

float Vector2::distance(const Vector2 other) const{
    return std::sqrt(pow(other.y - y, 2) + pow(other.x - x, 2));
}

Vector2 Vector2::operator+(const Vector2 &other) const{
    return Vector2(x + other.x, y + other.y);
}

/*Vector2 operator+=(const Vector2 v1, const Vector2 &other){
    v1.x += other.x;
    v1.y += other.y;
}*/

Vector2 Vector2::operator-(const Vector2 &other) const{
    return Vector2(x - other.x, y - other.y);
}

Vector2 Vector2::operator-() const{
    return Vector2(-x, -y);
}

Vector2 Vector2::operator/(const float divider) const{
    return Vector2(x / divider, y / divider);
}

Vector2 Vector2::operator*(const float scaler) const{
    return Vector2(x * scaler, y * scaler);
}

Vector2 Vector2::normalized(Vector2 v){
    float mag = v.magnitude();
    //return (0,0) if magnitude is 0
    //---- TODO - does this violate single responsibility rule? should it return an optional value instead?
    Vector2 norm = mag ? Vector2(v.x / mag, v.y / mag) : Vector2(0,0);
    return norm;
}

float Vector2::dotProduct(const Vector2 &v1, const Vector2 &v2){
    return v1.x * v2.x + v1.y * v2.y;
}


Vector2 operator*(float d, const Vector2 &v){
    return Vector2(d * v.getX(), d * v.getY());
}