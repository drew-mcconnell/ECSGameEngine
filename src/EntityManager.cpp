#include "EntityManager.h"

EntityManager::EntityManager(){
    livingEntityCount = 0;
    for(Entity e = 0; e < maxEntities; e++)
    {
        availableIDs.push(e);
    }
}

Entity EntityManager::createEntity(){

    //Signature sig(0);
    Entity newEntity;
    if(livingEntityCount < maxEntities){
        //get the next available ID from the queue
        newEntity = availableIDs.front();

        //remove that ID from the front of the queue
        availableIDs.pop();

        livingEntityCount++;
    }
    return newEntity;
    //return createEntity(sig);
}

/*Entity EntityManager::createEntity(Signature sig){

    Entity e;
    if(livingEntityCount < maxEntities){
        //get the next available ID from the queue
        uint8_t nextId = availableIDs.front();

        //remove that ID from the front of the queue
        availableIDs.pop();

        //make an entity with the right ID and signature
        e = Entity(nextId, sig);

        //store the Entity in the array using the ID as its index
        //entities[nextId] = e;

        livingEntityCount++;
    }
    return e;
}*/

void EntityManager::deleteEntity(Entity entity){

    //----- TODO - ensure entity is within range of maxEntities

    //invalidate the location of the entity in the array
    entitySignatures[entity].reset();

    //add the ID back to list of available IDs
    availableIDs.push(entity);

    livingEntityCount--;

}

void EntityManager::setSignature(Entity entity, Signature signature){
    
    //------ TODO - make sure entity is within maxEntities
    entitySignatures[entity] = signature;
}

Signature EntityManager::getSignature(Entity entity) const {
    
    //------ TODO - make sure entity is within maxEntities
    
    return entitySignatures[entity];
}