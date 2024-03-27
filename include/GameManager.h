#pragma once
#include <SDL.h>
#include "constants.h"
#include "ECSManager.h"
#include "TransformComponent.h"
#include "PhysicsComponent.h"
#include "RenderComponent.h"
#include "EntityManager.h"
#include "ComponentManager.h"
#include "BoxRenderSystem.h"
#include "PhysicsSystem.h"
#include "InputManager.h"
#include "InputContext.h"
#include "Command.h"
#include "Collider.h"
#include "BoxCollider.h"
#include "CircleCollider.h"

using namespace std;

class GameManager{
    private:

        Entity entities[maxEntities];

        std::shared_ptr<BoxRenderSystem> boxRenderSystem;
        std::shared_ptr<PhysicsSystem> physicsSystem;
        
        std::shared_ptr<InputContext> defaultContext;
        InputManager inputManager;

        /*TransformComponent transforms[maxEntities];
        PhysicsComponent physics[maxEntities];
        RenderComponent render[maxEntities];*/


    public:
        GameManager();

        void createWalls();
        void createPaddles();
        void createBalls();
        void deletePaddles();

        void ProcessInput();
        void Update(float deltaTime);
        void Render(SDL_Renderer * renderer);



};