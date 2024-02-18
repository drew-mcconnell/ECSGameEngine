#pragma once
#include "EntityManager.h"
#include "ComponentManager.h"
#include "SystemManager.h"

class ECSManager{
    private:
        std::unique_ptr<EntityManager> entityManager;
        std::unique_ptr<ComponentManager> componentManager;
        std::unique_ptr<SystemManager> systemManager;

    public:
        void init(){
            entityManager = std::make_unique<EntityManager>();
            componentManager = std::make_unique<ComponentManager>();
            systemManager = std::make_unique<SystemManager>();
        }

        //Entity Methods
        Entity createEntity(){
            return entityManager->createEntity();
        }

        void deleteEntity(Entity entity){
            entityManager->deleteEntity(entity);
            componentManager->entityDestroyed(entity);
            systemManager->entityDestroyed(entity);
        }

        uint8_t getLivingEntityCount(){
            return entityManager->getLivingEntityCount();
        }

        //Component Methods
        template<typename T>
        void registerComponent(){
            componentManager->registerComponent<T>();
        }

        template<typename T>
        Signature getComponentSignature(){
            return componentManager->getComponentSignature<T>();
        }

        template<typename T>
        void addComponent(Entity entity, T component){
            //add component for entity
            componentManager->addComponent(entity, component);

            //update entity signature and related system
            auto oldSig = entityManager->getSignature(entity);
            auto newSig = componentManager->getComponentSignature<T>();
            newSig |= oldSig;
            entityManager->setSignature(entity, newSig);

            //update systems with new entity component
            systemManager->entitySignatureChanged(entity, newSig);
        }

        template<typename T>
        void removeComponent(Entity entity){
            //remove component for entity
            componentManager->removeComponent<T>(entity);

            //update entity signature
            auto oldSig = entityManager->getSignature(entity);
            auto newSig = componentManager->getComponentSignature<T>();
            //turn off component bit in signature
            newSig ^= oldSig;
            entityManager->setSignature(entity, newSig);

            //update systems with new entity component
            systemManager->entitySignatureChanged(entity, newSig);
        }

        template<typename T>
        T& getComponent(Entity entity){
            return componentManager->getComponent<T>(entity);
        }

        //System Methods
        template<typename T>
        std::shared_ptr<T> registerSystem(){
            return systemManager->registerSystem<T>();
        }

        template<typename T>
        void setSignature(Signature signature){
            systemManager->setSignature<T>(signature);
        }
};