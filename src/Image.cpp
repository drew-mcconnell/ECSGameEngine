#include "Image.h"

Image::Image(std::string fileName){
    setImage(fileName);
}

Image::~Image(){
    //SDL_DestroyTexture(texture);
    //SDL_FreeSurface(surface);
}

void Image::setImage(std::string fileName){
    mFileName = fileName;

    //Load splash image
    surface = IMG_Load(mFileName.c_str());
    if( surface == NULL )
    {
        printf( "Unable to load image %s! SDL Error: %s\n", "brick.jpeg", SDL_GetError() );
    }
}

void Image::render(SDL_Renderer * renderer, SDL_Rect * sourceRect, SDL_Rect * destinationRect){
    
    //create the texture
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == NULL) {
        //--- TODO - raise exception if image not loaded
        //std::cout << "Error creating texture";
    }

    SDL_RenderCopy(renderer, texture, NULL, destinationRect);
}