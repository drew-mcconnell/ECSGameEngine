#pragma once
#include <queue>
#include "Entity.h"
#include "constants.h"


// EntityManager is simply for creating entities and keeping track of available IDs and number of living entities
// it does NOT actually store the entities
class EntityManager{
    private:
        //Entity entities[maxEntities];
        std::queue<uint8_t> availableIDs;
        uint8_t livingEntityCount;

    public:
        EntityManager();
        ~EntityManager(){};

        Entity createEntity();
        Entity createEntity(Signature sig);
        void deleteEntity(Entity entity);
        void setSignature(Entity entity, Signature signature){entity.setSignature(signature);};
        Signature getSignature(Entity entity) const {return entity.getSignature();};
        uint8_t getLivingEntityCount() const {return livingEntityCount;};
};