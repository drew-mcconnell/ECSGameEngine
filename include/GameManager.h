#pragma once
#include <SDL.h>
#include <cmath>
#include "limits.h"
#include "constants.h"
#include "ECSManager.h"
#include "ComponentTypes.h"
//#include "EntityManager.h"
//#include "ComponentManager.h"
#include "RenderSystem.h"
#include "PhysicsSystem.h"
#include "InputManager.h"
#include "InputContext.h"
//#include "Command.h"
#include "SceneLoader.h"
#include "SceneSaver.h"
#include "ScriptSystem.h"

using namespace std;

class GameManager{
    private:

        Entity entities[maxEntities];


        std::shared_ptr<RenderSystem> renderSystem;
        std::shared_ptr<PhysicsSystem> physicsSystem;
        
        std::shared_ptr<InputContext> defaultContext;
        InputManager inputManager;
        std::shared_ptr<ScriptSystem> scriptSystem;

    public:
        GameManager();

        void createWalls();
        void createPaddles();
        void createBalls();

        void saveScene();

        void ProcessInput();
        void Update(float deltaTime);
        void Render(SDL_Renderer * renderer);

};