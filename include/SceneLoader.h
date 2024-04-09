#pragma once
#include <fstream>
#include <string>
#include "ECSManager.h"
#include "TransformComponent.h"
#include "PhysicsComponent.h"
#include "RenderComponent.h"
#include "Collider.h"
#include "BoxCollider.h"
#include "CircleCollider.h"

extern ECSManager ecsManager;

class SceneLoader{
    private:
        static std::string removeQuotesAndColon(std::string text);
        static std::string removeEndComma(std::string text);

        static TransformComponent readTransform(std::ifstream &sceneFile);
        static PhysicsComponent readRigidbody(std::ifstream &sceneFile);
        static RenderComponent readRender(std::ifstream &sceneFile);
        static bool readBoxCollider(std::ifstream &sceneFile);
        static bool readCircleCollider(std::ifstream &sceneFile);
        static void parseObject(std::ifstream &sceneFile, ECSManager &ecsManager, Entity entities[]);

    public:
        static void readFile(std::string file, ECSManager &ecsManager, Entity entities[]);

};