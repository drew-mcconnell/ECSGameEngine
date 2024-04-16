#include "InputContext.h"

Entity InputContext::getEntityFromTag(std::string tag) const{

    //basic brute force looking for tags, but not that many tags, so performance hit should be minimal
    for(auto entity : entities){
        Tag t = ecsManager.getComponent<Tag>(entity);
        if(t.tag == tag){
            return entity;
        }
    }
    //return -1 if not found
    return -1;
}

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
                        Entity entity = getEntityFromTag("paddle2");
                        buttonUpPressed->execute(entity);
                        break;
                        }
                    case SDLK_DOWN:{
                        Entity entity = getEntityFromTag("paddle2");
                        buttonDownPressed->execute(entity);
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
                        Entity entity = getEntityFromTag("paddle1");
                        buttonWPressed->execute(entity);
                        break;
                    }
                    case SDLK_s:{
                        Entity entity = getEntityFromTag("paddle1");
                        buttonSPressed->execute(entity);
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
                        Entity entity = getEntityFromTag("paddle2");
                        buttonUpReleased->execute(entity);
                        break;
                        }
                    case SDLK_DOWN:{
                        Entity entity = getEntityFromTag("paddle2");
                        buttonDownReleased->execute(entity);
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
                        Entity entity = getEntityFromTag("paddle1");
                        buttonWReleased->execute(entity);
                        break;
                    }
                    case SDLK_s:{
                        Entity entity = getEntityFromTag("paddle1");
                        buttonSReleased->execute(entity);
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