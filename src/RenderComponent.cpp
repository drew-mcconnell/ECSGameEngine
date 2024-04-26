#include "RenderComponent.h"

RenderComponent::RenderComponent(){
    //mColor = RGBA();
    //mShape = RECT;
    //mImage = Image();
    render = RenderComponent::rectRender;
}

RenderComponent::RenderComponent(RGBA color, Shapes shape){
    mColor = color;
    mShape = shape;
    mImage = Image();

    if(mShape == RECT){
        render = RenderComponent::rectRender;
    }
    else if(mShape == CIRCLE){
        render = RenderComponent::circleRender;
    }
    else{
        //--- TODO - throw error if shape isn't RECT or CIRCLE
    }
}

RenderComponent::RenderComponent(Image image){
    mColor = RGBA();
    mShape = IMAGE;
    mImage = image;
    render = RenderComponent::imageRender;
}

void RenderComponent::rectRender(RenderComponent * r, SDL_Renderer * renderer, TransformComponent transform){
    SDL_Rect rect1 = {
        (int)(transform.x - transform.width / 2),
        (int)(transform.y - transform.height / 2),
        (int)transform.width,
        (int)transform.height
        };
        SDL_SetRenderDrawColor(renderer, r->mColor.red, r->mColor.green, r->mColor.blue, r->mColor.alpha);
        SDL_RenderFillRect(renderer, &rect1);
}

void RenderComponent::circleRender(RenderComponent * r, SDL_Renderer * renderer, TransformComponent transform){
    SDL_SetRenderDrawColor(renderer, r->mColor.red, r->mColor.green, r->mColor.blue, r->mColor.alpha);
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
}

void RenderComponent::imageRender(RenderComponent * r, SDL_Renderer * renderer, TransformComponent transform){
    
    SDL_Rect sr = {(int)transform.x, (int)transform.y, (int)transform.width, (int)transform.height};
    SDL_Rect dr = {(int)(transform.x - transform.width / 2), (int)(transform.y - transform.height / 2), (int)transform.width, (int)transform.height};
    r->mImage.render(renderer, &sr, &dr);
}
        