#pragma once
#include <map>
#include "constants.h"
//#include "Entity.h"
#include "ComponentArray.h"
#include "TransformComponent.h"
#include "PhysicsComponent.h"
#include "RenderComponent.h"
#include "Collider.h"
#include "BoxCollider.h"

class ComponentManager{
    private:
        // Map from type string pointer to a component Signature
        std::map<const char *, Signature> componentSignatures{};
        
        // Map from type string pointer to a component array
	    std::map<const char *, std::shared_ptr<IComponentArray>> componentArrays{};

        // The bit Signature to be assigned to the next registered component - starting at 0b1
	    Signature nextComponentSignature{};

        //function for getting the array for a specific component type
        template<typename T>
	    std::shared_ptr<ComponentArray<T>> getComponentArray(){
            const char * typeName = typeid(T).name();

            //----- TODO - make sure type exists first

            return std::static_pointer_cast<ComponentArray<T>>(componentArrays[typeName]);
        }

    public:
        ComponentManager(){nextComponentSignature = Signature(0b1);}

        template<typename T>
        void registerComponent(){
            const char * typeName = typeid(T).name();

            //map the type name to its Signature
            //insert makes sure typeName doesn't already exist in componentTypes
            componentSignatures.insert({typeName, nextComponentSignature});

            // Create a ComponentArray pointer and add it to the component arrays map
            componentArrays.insert({typeName, std::make_shared<ComponentArray<T>>()});

            //shift to the next bit Signature
            nextComponentSignature <<= 1;
            // ------ TODO - check if maxed out number of components
        }
        
        template<typename T>
	    Signature getComponentSignature(){
            //------ TODO - make sure component exists before returning
            const char* typeName = typeid(T).name();
            return componentSignatures[typeName];
        }

        template<typename T>
	    void addComponent(Entity entity, T component){
            getComponentArray<T>()->addComponent(entity, component);
        }

        template<typename T>
	    void removeComponent(Entity entity){
            getComponentArray<T>()->removeComponent(entity);
        }

        template<typename T>
	    T& getComponent(Entity entity){
            return getComponentArray<T>()->getComponentForEntity(entity);
        }

        void entityDestroyed(Entity entity){
            for(auto const& pair : componentArrays){
                auto const& componentArray = pair.second;
                componentArray->entityDestroyed(entity);
            }
        }

};
