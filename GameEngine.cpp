#include <iostream>
#include <SDL.h>
#include "GameManager.h"

using namespace std;

const int frameTargetTime = 30;
int lastFrameTime = 0;

GameManager gameManager;

bool initializeWindow(SDL_Window **window, SDL_Renderer **renderer)
{
    //initialize SDL
    if(SDL_Init(/*SDL_INIT_VIDEO*/SDL_INIT_EVERYTHING) < 0){
        cout << "SDL could not be initialized" << SDL_GetError();
        return false;
    }

    //create a new window
    *window = SDL_CreateWindow(
        "Game Title",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800,
        600,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE //| SDL_WINDOW_INPUT_GRABBED
    );

    //check to make sure window was created successfully
    if(!*window){
        cout << "Window could not be initialized" << SDL_GetError();
        return false;
    }

    *renderer = SDL_CreateRenderer(
        *window,
        -1,
        0
    );

    if(!*renderer){
        cout << "Renderer could not be initialized" << SDL_GetError();
        return false;
    }
    
    cout << "SDL video is ready to go" << endl;
    SDL_PumpEvents();
    return true;
}

void destroyWindow(SDL_Window *window, SDL_Renderer *renderer)
{
    //destroy objects in reverse order they were created in
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void setup()
{
    //-------- TODO: setup Scene system ------

    gameManager = GameManager();
    gameManager.createPaddles();
    //gameManager.deletePaddles();
    
}

void processInput(bool *isRunning)
{
    SDL_Event event;

    //process all events in the queue
    while(SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_QUIT: //event from pressing the "X" button of the window
                *isRunning = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if(event.button.button == SDL_BUTTON_LEFT){
                    
                }
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym){
                    case SDLK_ESCAPE:{
                        *isRunning = false;
                        break;
                        }
                    default:
                        //playerInput.Update(&player);
                        break;
            }
        }
    }
}

void update()
{
    //----------- should I even cap the frame rate? Seems like it would be more efficient for the system as a whole if I only executed at a certain FPS
    //wait until elapsed time for correct FPS has been reached
    int timeToWait = frameTargetTime - (SDL_GetTicks() - lastFrameTime);
    
    //only delay if the processor is early for the next frame
    if(timeToWait > 0 && timeToWait <= frameTargetTime){
        SDL_Delay(timeToWait);
    }

    //divide time since last frame by 1000ms to calculate distance in pixels per second instead of pixels per frame
    float deltaTime = (SDL_GetTicks() - lastFrameTime) / 1000.0f; 

    lastFrameTime = SDL_GetTicks();
}

void render(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    if(SDL_RenderClear(renderer) < 0)
    {
        cout << "SDL_RenderClear failed: " << SDL_GetError() << endl;
    }

    gameManager.Render(renderer);


    SDL_RenderPresent(renderer); //swap the "front" buffer and "back" buffer to display everything at once
    SDL_PumpEvents();
}

int main(int argc, char * argv[])
{
    cout << "hello" << endl;

    SDL_Window * window = nullptr;
    SDL_Renderer * renderer = nullptr;

    // ------------ TODO ----------
    setup();

    bool isRunning = initializeWindow(&window, &renderer);

    while(isRunning)
    {
        processInput(&isRunning);
        update();
        render(renderer);
    }

    //SDL_Delay(3000);

    destroyWindow(window, renderer);

    return 0;
}