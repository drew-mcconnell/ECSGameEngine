/*#include "ComponentManager.h"

template<typename T>
void ComponentManager::registerComponent(){
    const char * typeName = typeid(T).name();

    //map the type name to its Signature
    //insert makes sure typeName doesn't already exist in componentTypes
    componentSignatures.insert({typeName, nextComponentSignature});

    // Create a ComponentArray pointer and add it to the component arrays map
	componentArrays.insert({typeName, std::make_shared<ComponentArray<T>>()});

    //shift to the next bit Signature
    nextComponentSignature <<= 1;
}

//return the signature associated with a component type
template<typename T>
Signature ComponentManager::getComponentSignature(){
    //------ TODO - make sure component exists before returning
    const char* typeName = typeid(T).name();
    return componentSignatures[typeName];
}

//add a component to a component array
template<typename T>
void ComponentManager::addComponent(Entity entity, T component){
    getComponentArray<T>()->addComponent(entity, component);
}

//remove a component from a component array
template<typename T>
void ComponentManager::removeComponent(Entity entity){
    getComponentArray<T>()->removeComponent(entity);
}

//return the address to a component in a component array
template<typename T>
T& ComponentManager::getComponent(Entity entity){
    return getComponentArray<T>()->getComponentForEntity(entity);
}

//go through all component arrays and notify that the entity has been destroyed
//each component array will determine if it has a component for that entity, and if so, will remove it
void ComponentManager::entityDestroyed(Entity entity){
    for(auto const& pair : componentArrays){
        auto const& componentArray = pair.second;
        componentArray->entityDestroyed(entity);
    }
}

template<typename T>
std::shared_ptr<ComponentArray<T>> ComponentManager::getComponentArray(){
    const char * typeName = typeid(T).name();

    //----- TODO - make sure type exists first

    return std::static_pointer_cast<ComponentArray<T>>(componentArrays[typeName]);
}*/

/*
//explicitly declare instances of the different template classes for the compiler/linker
template class ComponentArray<TransformComponent>;
template class ComponentArray<PhysicsComponent>;
template class ComponentArray<RenderComponent>;*/