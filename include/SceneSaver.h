#pragma once
#include <fstream>
#include <string>
#include "ECSManager.h"
#include "ComponentTypes.h"

class SceneSaver{
    private:
        static void addQuotesAndColon(std::string text);
        static void addEndLineComma(std::ofstream &sceneFile);

        static void writeTransform(std::ofstream &sceneFile, TransformComponent transform);
        static void writeRigidbody(std::ofstream &sceneFile, PhysicsComponent rb);
        static void writeRender(std::ofstream &sceneFile, RenderComponent r);
        static void writeBoxCollider(std::ofstream &sceneFile);
        static void writeCircleCollider(std::ofstream &sceneFile);
        static void writeTag(std::ofstream &sceneFile);
        static void writeObject(std::ofstream &sceneFile, ECSManager &ecsManager, Entity entities[], uint8_t numEntities);
    public:
        static void writeFile(std::string file, ECSManager &ecsManager, Entity entities[], uint8_t numEntities);

};