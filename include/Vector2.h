#pragma once

class Vector2{
    private:
        

    public:
        float x;
        float y;

        Vector2():x(0),y(0){};
        Vector2(float x, float y):x(x),y(y){};

        void setX(float x){this->x = x;};
        void setY(float y){this->y = y;};
        float getX()const {return x;};
        float getY()const {return y;};

        float magnitude();

        float distance(const Vector2 other) const;
        Vector2 operator+(const Vector2 &other) const;
        //Vector2 operator+=(const Vector2 &other);
        Vector2 operator-(const Vector2 &other) const;
        Vector2 operator-() const;
        Vector2 operator/(const float divider) const;
        Vector2 operator*(const float scaler) const;

        static Vector2 normalized(Vector2 v);
        static float dotProduct(const Vector2 &v1, const Vector2 &v2);

};

Vector2 operator*(float d, const Vector2 &v);