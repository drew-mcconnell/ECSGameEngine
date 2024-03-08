#pragma once
#include <map>
#include <array>
#include "constants.h"
//#include "Entity.h"
//#include "TransformComponent.h"
//#include "PhysicsComponent.h"
//#include "RenderComponent.h"

class IComponentArray
{
    public:
        virtual ~IComponentArray() = default;
        virtual void entityDestroyed(Entity e) = 0;
};

template<typename T>
class ComponentArray : public IComponentArray{
    private:
        // The packed array of components (of generic type T)
        std::array<T, maxEntities> componentArray;

        // Map from an entity ID to an index where that entity is in componentArray
	    std::map<Entity, uint8_t> entityIDToArrayIndexMap;

        // Map from an index in componentArray to the entity ID associated with the component at that index.
	    std::map<uint8_t, Entity> arrayIndexToEntityMap;

        int numComponents;

    public:

        void addComponent(Entity entity, T component){
            // ------- TODO - make sure entity doesn't already have this component

            int newComponentIndex = numComponents;

            //add component to end of array
            componentArray[newComponentIndex] = component;
            
            //map the entity ID to its index in the componentArray
            entityIDToArrayIndexMap[entity] = newComponentIndex;
            
            //map the index in componentArray to the corresponding entityID
            arrayIndexToEntityMap[newComponentIndex] = entity;

            numComponents++;

        }

        void removeComponent(Entity entity){
            // ----- TODO - make sure entity has component in list before removing

            //move last element in array to the spot that is being removed to maintain packed array
            int indexOfRemovedEntity = entityIDToArrayIndexMap[entity];
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
            entityIDToArrayIndexMap.erase(entity);
            arrayIndexToEntityMap.erase(lastIndex);

            numComponents--;
        }

        T& getComponentForEntity(Entity entity){
            //----- TODO - handle exception for entity not in array

            return componentArray[entityIDToArrayIndexMap.at(entity)];
        }

        virtual void entityDestroyed(Entity entity) override{

            //check to make sure the component exists, and if so, remove it
            if(entityIDToArrayIndexMap.find(entity) != entityIDToArrayIndexMap.end())
            {
                removeComponent(entity);
            }
        }
};

//explicitly declare instances of the different template classes for the compiler/linker
/*template class ComponentArray<TransformComponent>;
template class ComponentArray<PhysicsComponent>;
template class ComponentArray<RenderComponent>;*/