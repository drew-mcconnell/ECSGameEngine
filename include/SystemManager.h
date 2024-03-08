#pragma once
#include <map>
#include "constants.h"
#include "System.h"

class SystemManager{
    private:
        //map from a system name to the signature of entities it acts upon
        std::map<const char *, Signature> systemSignatures;

        //map from a system name to a pointer to its system
        std::map<const char *, std::shared_ptr<System>> systems{};

    public:
        template<typename T>
        std::shared_ptr<T> registerSystem(){
            const char * typeName = typeid(T).name();

            //------ TODO - make sure system doesn't already exist

            auto system = std::make_shared<T>();
            systems.insert({typeName, system});
            return system;
        }

        template<typename T>
        void setSignature(Signature signature){
            
            //------ TODO - make sure system signature doesn't already exist

            const char * typeName = typeid(T).name();
            systemSignatures[typeName] = signature;//.insert({typeName, signature});
        }

        template<typename T>
        Signature getSignature(){
            const char * typeName = typeid(T).name();
            return systemSignatures[typeName];
        }

        void entityDestroyed(Entity entity){
            //go through all systems and erase the entity
            for(auto & pair : systems){
                //don't need to check if entity exists because entities is a set
                pair.second->entities.erase(entity);
            }
        }

        void entitySignatureChanged(Entity entity, Signature entitySignature){
            //go through all systems and update their entity sets
            for(auto & pair : systems){
                auto const & type = pair.first;
                auto const & system = pair.second;
                auto const & systemSignature = systemSignatures[type];

                //if entity signature matches the system signature, add it to the system's entity set
                //put check to make sure systemSignature is not empty
                if(((entitySignature & systemSignature) == systemSignature) && (systemSignature != 0b0)){
                    system->entities.insert(entity);
                }
                //if entity signature doesn't match the system signature, remove it from the system's entity set
                else{
                    system->entities.erase(entity);
                }
            }
        }

};