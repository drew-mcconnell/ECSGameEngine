#include "GameManager.h"

GameManager::GameManager(){
    ecsManager.init();
    //entities = new Entity[maxEntities];
};

void GameManager::Update(){
    
}

void GameManager::Render(SDL_Renderer * renderer){
    
    for(int i = 0; i < ecsManager.getLivingEntityCount(); i++){
        // ----- SHOULD BE DONE IN A SYSTEM, BUT WE'RE JUST TESTING HERE ----
        TransformComponent t = ecsManager.getComponent<TransformComponent>(entities[i]);
        SDL_Rect rect1 = {
        t.x,
        t.y,
        t.width,
        t.height
        };
        RenderComponent r = ecsManager.getComponent<RenderComponent>(entities[i]);
        SDL_SetRenderDrawColor(renderer, r.red, r.green, r.blue, r.alpha);
        SDL_RenderFillRect(renderer, &rect1);
    }
}

void GameManager::createPaddles(){
    
    ecsManager.registerComponent<TransformComponent>();
    ecsManager.registerComponent<PhysicsComponent>();
    ecsManager.registerComponent<RenderComponent>();

    //make paddle 1
    int currentIndex = ecsManager.getLivingEntityCount();
    //Signature sig1 = Signature(0b111);
    entities[currentIndex] = ecsManager.createEntity();

    //Signature sig1 = ecsManager.getComponentSignature<TransformComponent>() | componentManager.getComponentSignature<PhysicsComponent>() | componentManager.getComponentSignature<RenderComponent>();
    //ecsManager.setSignature(entities[currentIndex], sig1);

    TransformComponent t1;
    t1.x = 20;
    t1.y = 20;
    t1.width = 15;
    t1.height = 100;
    ecsManager.addComponent<TransformComponent>(entities[currentIndex], t1);
    
    PhysicsComponent phys1;
    phys1.xVelocity = 0;
    phys1.yVelocity = 0;
    ecsManager.addComponent<PhysicsComponent>(entities[currentIndex], phys1);
    
    RenderComponent rend1;
    rend1.red = 0;
    rend1.green = 255;
    rend1.blue = 0;
    rend1.alpha = 255;
    ecsManager.addComponent<RenderComponent>(entities[currentIndex], rend1);
    
    //make paddle 2
    currentIndex = ecsManager.getLivingEntityCount();
    entities[currentIndex] = ecsManager.createEntity();
    //ecsManager.setSignature(entities[currentIndex], sig1);

    TransformComponent t2;
    t2.x = 800 - 15 - 20;
    t2.y = 20;
    t2.width = 15;
    t2.height = 100;
    ecsManager.addComponent<TransformComponent>(entities[currentIndex], t2);
    PhysicsComponent phys2;
    phys2.xVelocity = 0;
    phys2.yVelocity = 0;
    ecsManager.addComponent<PhysicsComponent>(entities[currentIndex], phys2);
    RenderComponent rend2;
    rend2.red = 0;
    rend2.green = 0;
    rend2.blue = 255;
    rend2.alpha = 255;
    ecsManager.addComponent<RenderComponent>(entities[currentIndex], rend2);
    
    //componentManager.entityDestroyed(entities[currentIndex-1]);
    /*transforms[currentIndex] = t2;
    physics[currentIndex] = phys2;
    render[currentIndex] = rend2;*/
}

void GameManager::deletePaddles(){
    ecsManager.deleteEntity(entities[0]);
    ecsManager.deleteEntity(entities[1]);
}