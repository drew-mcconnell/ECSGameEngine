#pragma once
#include "System.h"
#include <SDL.h>
#include "ECSManager.h"
#include "constants.h"

extern ECSManager ecsManager;

class BoxRenderSystem : public System{
    private:


    public:
        void RenderBoxes(SDL_Renderer * renderer);

};