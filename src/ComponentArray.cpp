#include "ComponentArray.h"

/*template<typename T>
void ComponentArray<T>::addComponent(Entity e, T component){
    // ------- TODO - make sure entity doesn't already have this component

    int newComponentIndex = numComponents;
    uint8_t entityID = e.getID();

    //add component to end of array
    componentArray[newComponentIndex] = component;
    
    //map the entity ID to its index in the componentArray
    entityIDToArrayIndexMap[entityID] = newComponentIndex;
    
    //map the index in componentArray to the corresponding entityID
    arrayIndexToEntityMap[newComponentIndex] = entityID;

    numComponents++;

}

template<typename T>
void ComponentArray<T>::removeComponent(Entity e){
    // ----- TODO - make sure entity has component in list before removing

    //move last element in array to the spot that is being removed to maintain packed array
    int removedEntityID = e.getID();
    int indexOfRemovedEntity = entityIDToArrayIndexMap[removedEntityID];
    int lastIndex = numComponents-1;
    componentArray[indexOfRemovedEntity] = componentArray[lastIndex];

    //update maps to reflect moved component
    //get ID of moved entity
    uint8_t IDofMovedEntity = arrayIndexToEntityMap[lastIndex];
    //update map to reflect new index
    entityIDToArrayIndexMap[IDofMovedEntity] = indexOfRemovedEntity;
    //update other map to reflect new ID at removed index
    arrayIndexToEntityMap[indexOfRemovedEntity] = IDofMovedEntity;

    //remove entity from maps
    entityIDToArrayIndexMap.erase(removedEntityID);
    arrayIndexToEntityMap.erase(lastIndex);

    numComponents--;
}

template<typename T>
T& ComponentArray<T>::getComponentForEntity(Entity e){
    //----- TODO - handle exception for entity not in array

    componentArray[entityIDToArrayIndexMap.at(e.getID())];
}

template<typename T>
void ComponentArray<T>::entityDestroyed(Entity e){

    //check to make sure the component exists, and if so, remove it
    if(entityIDToArrayIndexMap.find(e.getID()) != entityIDToArrayIndexMap.end())
    {
        removeComponent(e);
    }
}

//explicitly declare instances of the different template classes for the compiler/linker
template class ComponentArray<TransformComponent>;
template class ComponentArray<PhysicsComponent>;
template class ComponentArray<RenderComponent>;*/