#pragma once
#include <array>
#include <map>
#include <SDL.h>
#include "constants.h"
#include "InputContext.h"

class InputManager{

    private:
        //have multiple context so buttons can do different things in different contexts (menu, gameplay, etc.)
        std::shared_ptr<InputContext> inputContexts[maxInputContexts];
        int numInputContexts;
        int currentInputContext;

        //std::map<SDL_Keycode, /*??? actions and states*/> inputMap;

    public:
        InputManager():numInputContexts(0),currentInputContext(0){};
        void addContext(std::shared_ptr<InputContext> context);
        
        //---- TODO - have better system than this ----
        void changeContext(int activeContext);
        
        void processInput();

};