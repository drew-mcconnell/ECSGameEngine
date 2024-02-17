#pragma once
#include <SDL.h>
#include "constants.h"
#include "TransformComponent.h"
#include "PhysicsComponent.h"
#include "RenderComponent.h"
#include "EntityManager.h"
#include "ComponentManager.h"

using namespace std;

class GameManager{
    private:
        EntityManager entityManager;

        Entity entities[maxEntities];

        ComponentManager componentManager;

        /*TransformComponent transforms[maxEntities];
        PhysicsComponent physics[maxEntities];
        RenderComponent render[maxEntities];*/

    public:
        GameManager(){};

        void createPaddles();
        void deletePaddles();

        void Update();
        void Render(SDL_Renderer * renderer);



};