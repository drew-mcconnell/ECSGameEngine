#pragma once
#include <queue>
#include <array>
//#include "Entity.h"
#include "constants.h"


// EntityManager is simply for creating entities and keeping track of available IDs and number of living entities
// it does NOT actually store the entities
class EntityManager{
    private:
        //Entity entities[maxEntities];
        
        //keep track of available IDs
        std::queue<Entity> availableIDs;

        //array of signatures where entity ID is the index of its Signature
        std::array<Signature, maxEntities> entitySignatures{};

        uint8_t livingEntityCount;

    public:
        EntityManager();
        ~EntityManager(){};

        Entity createEntity();
        //Entity createEntity(Signature sig);
        void deleteEntity(Entity entity);
        void setSignature(Entity entity, Signature signature);
        Signature getSignature(Entity entity) const;
        uint8_t getLivingEntityCount() const {return livingEntityCount;};
};