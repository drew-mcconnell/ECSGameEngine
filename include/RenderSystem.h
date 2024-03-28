#pragma once
#include "System.h"
#include <SDL.h>
#include "ECSManager.h"
#include "constants.h"

extern ECSManager ecsManager;

class RenderSystem : public System{
    private:


    public:
        void RenderBoxes(SDL_Renderer * renderer);
        void DrawRect(SDL_Renderer * renderer, TransformComponent transform, RenderComponent render);
        void DrawCircle(SDL_Renderer * renderer, TransformComponent transform, RenderComponent render);
        void SDL_RenderFillCircle(SDL_Renderer * renderer, TransformComponent transform, RenderComponent render);
};