#include "BoxRenderSystem.h"

void BoxRenderSystem::RenderBoxes(SDL_Renderer * renderer){
    for(auto const &entity : entities){
        auto &transform = ecsManager.getComponent<TransformComponent>(entity);
        auto &render = ecsManager.getComponent<RenderComponent>(entity);

        SDL_Rect rect1 = {
        transform.x,
        transform.y,
        transform.width,
        transform.height
        };
        SDL_SetRenderDrawColor(renderer, render.red, render.green, render.blue, render.alpha);
        SDL_RenderFillRect(renderer, &rect1);
    }
}