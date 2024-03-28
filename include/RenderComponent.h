#pragma once
#include "RGBA.h"

enum Shapes{
    RECT,
    CIRCLE
};

class RenderComponent{
    public:
        RGBA color;
        Shapes shape;
};