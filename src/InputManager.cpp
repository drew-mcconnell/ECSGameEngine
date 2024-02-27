#include "InputManager.h"

void InputManager::processInput(){
    inputContexts[currentInputContext]->processInput();
}

void InputManager::addContext(std::shared_ptr<InputContext> context){
    //make sure there is still room in the array
    assert(numInputContexts < maxInputContexts);

    inputContexts[numInputContexts] = context;
}

void InputManager::changeContext(int activeContext){
    currentInputContext = activeContext;
}