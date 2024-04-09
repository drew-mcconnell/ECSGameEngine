#include "InputContext.h"

InputContext::InputContext(){

    //setup default context
    // ----- TODO - create four Command objects to use here
    // ----- W Command for up
    // ----- S Command for down
    // ----- Empty command for A and D

    buttonWPressed = &moveUp;
    buttonWReleased = &stopY;
    buttonSPressed = &moveDown;
    buttonSReleased = &stopY;

    buttonA = &nullC;
    buttonD = &nullC;

    buttonUpPressed = &moveUp;
    buttonUpReleased = &stopY;

    buttonDownPressed = &moveDown;
    buttonDownReleased = &stopY;

    buttonLeft = &nullC;
    buttonRight = &nullC;
}
//using a Command pattern to map buttons to actions
void InputContext::processInput(){
        //pump events into queue before running SDL_PeepEvents
    SDL_PumpEvents();
    
    SDL_Event events[10];

    //process all events relevant to player, but don't remove because some key events need to be processed outside this component
    int count = SDL_PeepEvents(events, 10, SDL_PEEKEVENT, SDL_KEYDOWN, SDL_KEYUP);
    for(auto event : events){
        switch(event.type){
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym){
                    case SDLK_UP:{
                        buttonUpPressed->execute(*entities.find(5));
                        break;
                        }
                    case SDLK_DOWN:{
                        buttonDownPressed->execute(*entities.find(5));
                        break;
                        }
                    case SDLK_LEFT:{
                        buttonLeft->execute(0);
                        break;
                    }
                    case SDLK_RIGHT:{
                        buttonRight->execute(0);
                        break;
                    }
                    case SDLK_w:{
                        buttonWPressed->execute(*entities.find(4));
                        break;
                    }
                    case SDLK_s:{
                        buttonSPressed->execute(*entities.find(4));
                        break;
                    }
                    case SDLK_a:{
                        buttonA->execute(0);
                        break;
                    }
                    case SDLK_d:{
                        buttonD->execute(0);
                        break;
                    }
                }
                break;
            case SDL_KEYUP:
                switch(event.key.keysym.sym){
                    case SDLK_UP:{
                        buttonUpReleased->execute(*entities.find(5));
                        break;
                        }
                    case SDLK_DOWN:{
                        buttonDownReleased->execute(*entities.find(5));
                        break;
                        }
                    case SDLK_LEFT:{
                        buttonLeft->execute(0);
                        break;
                    }
                    case SDLK_RIGHT:{
                        buttonRight->execute(0);
                        break;
                    }
                    case SDLK_w:{
                        buttonWReleased->execute(*entities.find(4));
                        break;
                    }
                    case SDLK_s:{
                        buttonSReleased->execute(*entities.find(4));
                        break;
                    }
                    case SDLK_a:{
                        buttonA->execute(0);
                        break;
                    }
                    case SDLK_d:{
                        buttonD->execute(0);
                        break;
                    }
                }
                break;
        }
    }
}