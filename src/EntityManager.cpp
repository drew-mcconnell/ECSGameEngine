#include "EntityManager.h"

EntityManager::EntityManager(){
    livingEntityCount = 0;
    for(int i = 0; i < maxEntities; i++)
    {
        availableIDs.push(i);
    }
}

Entity EntityManager::createEntity(){

    Signature sig(0);
    return createEntity(sig);
}

Entity EntityManager::createEntity(Signature sig){

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
}

void EntityManager::deleteEntity(Entity entity){

    //add the ID back to list of available IDs
    availableIDs.push(entity.getID());

    //invalidate the location of the entity in the array
    // -------- invalidating simply by giving it 0 components so no systems operate on it ---------
    // ------------------------ could be a bad idea, but we'll see --------
    //entities[entity.getID()].setSignature(Signature(0));

    livingEntityCount--;

}