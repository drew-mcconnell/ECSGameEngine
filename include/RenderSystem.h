#pragma once
#include <SDL.h>
#include "System.h"
#include "ECSManager.h"
#include "constants.h"

extern ECSManager ecsManager;

class RenderSystem : public System{
    private:


    public:
        void Render(SDL_Renderer * renderer);
        void DrawRect(SDL_Renderer * renderer, TransformComponent transform, RenderComponent render);
        void DrawCircle(SDL_Renderer * renderer, TransformComponent transform, RenderComponent render);
        void SDL_RenderFillCircle(SDL_Renderer * renderer, TransformComponent transform, RenderComponent render);
};