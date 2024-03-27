#include "BoxRenderSystem.h"

void BoxRenderSystem::RenderBoxes(SDL_Renderer * renderer){
    for(auto const &entity : entities){
        auto &transform = ecsManager.getComponent<TransformComponent>(entity);
        auto &render = ecsManager.getComponent<RenderComponent>(entity);

        SDL_Rect rect1 = {
        (int)(transform.x - transform.width / 2),
        (int)(transform.y - transform.height / 2),
        (int)transform.width,
        (int)transform.height
        };
        SDL_SetRenderDrawColor(renderer, render.red, render.green, render.blue, render.alpha);
        SDL_RenderFillRect(renderer, &rect1);


        #ifdef DEBUG
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderDrawPoint(renderer,transform.x, transform.y);
        #endif // DEBUG
        
        
    }
}