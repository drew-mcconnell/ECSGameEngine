#include "RenderSystem.h"

void RenderSystem::Render(SDL_Renderer * renderer){
    for(auto const &entity : entities){
        auto &transform = ecsManager.getComponent<TransformComponent>(entity);
        auto &render = ecsManager.getComponent<RenderComponent>(entity);

        //--- TODO - find more efficient way to select shape - is this conditional
        render.render(&render, renderer, transform);

        // still faster than a virtual function?
        /*if(render.mShape == RECT){
            DrawRect(renderer, transform, render);
        }
        else if(render.mShape == CIRCLE){
            DrawCircle(renderer, transform, render);
        }
        else{
            DrawImage(renderer, transform, render);
        }*/

        #ifdef DEBUG
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderDrawPoint(renderer,transform.x, transform.y);
        #endif // DEBUG
        
        
    }
}

void RenderSystem::DrawRect(SDL_Renderer * renderer, TransformComponent transform, RenderComponent render){
    SDL_Rect rect1 = {
            (int)(transform.x - transform.width / 2),
            (int)(transform.y - transform.height / 2),
            (int)transform.width,
            (int)transform.height
            };
            SDL_SetRenderDrawColor(renderer, render.mColor.red, render.mColor.green, render.mColor.blue, render.mColor.alpha);
            SDL_RenderFillRect(renderer, &rect1);
}

void RenderSystem::DrawCircle(SDL_Renderer * renderer, TransformComponent transform, RenderComponent render)
{
    SDL_SetRenderDrawColor(renderer, render.mColor.red, render.mColor.green, render.mColor.blue, render.mColor.alpha);
    
    const int32_t radius = transform.width / 2;
    const int32_t diameter = (radius * 2);
    const int32_t centerX = transform.x;
    const int32_t centerY = transform.y;

    int32_t x = (radius - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - diameter);

   while (x >= y)
   {
      //  Each of the following renders an octant of the circle
      SDL_RenderDrawPoint(renderer, centerX + x, centerY - y);
      SDL_RenderDrawPoint(renderer, centerX + x, centerY + y);
      SDL_RenderDrawPoint(renderer, centerX - x, centerY - y);
      SDL_RenderDrawPoint(renderer, centerX - x, centerY + y);
      SDL_RenderDrawPoint(renderer, centerX + y, centerY - x);
      SDL_RenderDrawPoint(renderer, centerX + y, centerY + x);
      SDL_RenderDrawPoint(renderer, centerX - y, centerY - x);
      SDL_RenderDrawPoint(renderer, centerX - y, centerY + x);

      if (error <= 0)
      {
         ++y;
         error += ty;
         ty += 2;
      }

      if (error > 0)
      {
         --x;
         tx += 2;
         error += (tx - diameter);
      }
   }
}

void RenderSystem::SDL_RenderFillCircle(SDL_Renderer * renderer, TransformComponent transform, RenderComponent render)
{

    SDL_SetRenderDrawColor(renderer, render.mColor.red, render.mColor.green, render.mColor.blue, render.mColor.alpha);
    int x = transform.x;
    int y = transform.y;
    int radius = transform.width / 2;
    int offsetx, offsety, d;
    int status;

    offsetx = 0;
    offsety = radius;
    d = radius -1;
    status = 0;

    while (offsety >= offsetx) {

        status += SDL_RenderDrawLine(renderer, x - offsety, y + offsetx,
                                     x + offsety, y + offsetx);
        status += SDL_RenderDrawLine(renderer, x - offsetx, y + offsety,
                                     x + offsetx, y + offsety);
        status += SDL_RenderDrawLine(renderer, x - offsetx, y - offsety,
                                     x + offsetx, y - offsety);
        status += SDL_RenderDrawLine(renderer, x - offsety, y - offsetx,
                                     x + offsety, y - offsetx);

        if (status < 0) {
            status = -1;
            break;
        }

        if (d >= 2*offsetx) {
            d -= 2*offsetx + 1;
            offsetx +=1;
        }
        else if (d < 2 * (radius - offsety)) {
            d += 2 * offsety - 1;
            offsety -= 1;
        }
        else {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }

    //return status;
}

void RenderSystem::DrawImage(SDL_Renderer * renderer, TransformComponent transform, RenderComponent render){
    SDL_Rect sr = {(int)transform.x, (int)transform.y, (int)transform.width, (int)transform.height};
    SDL_Rect dr = {(int)transform.x, (int)transform.y, (int)transform.width, (int)transform.height};
    //render.image.render(renderer, &sr, &dr);
}