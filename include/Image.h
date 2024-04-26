#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>

class Image{
    public:
        std::string mFileName;

        Image():mFileName(""){};
        Image(std::string fileName);
        ~Image();
        void setImage(std::string fileName);
        void render(SDL_Renderer * renderer, SDL_Rect * sourceRect, SDL_Rect * destinationRect);

    private:
        SDL_Surface * surface;
        SDL_Texture * texture;
};