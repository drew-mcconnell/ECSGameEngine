#pragma once
#include "RGBA.h"
#include "Image.h"
#include "TransformComponent.h"

enum Shapes{
    RECT,
    CIRCLE,
    IMAGE
};

class RenderComponent{
    private:
        static void rectRender(RenderComponent * r, SDL_Renderer * renderer, TransformComponent transform);
        static void circleRender(RenderComponent * r, SDL_Renderer * renderer, TransformComponent transform);
        static void imageRender(RenderComponent * r, SDL_Renderer * renderer, TransformComponent transform);
    
    public:
        RGBA mColor;
        Shapes mShape;
        Image mImage;

        RenderComponent();
        RenderComponent(RGBA color, Shapes shape);
        RenderComponent(Image image);

        //function pointer to set render function based on shape type
        void (*render)(RenderComponent * r, SDL_Renderer *, TransformComponent);


};