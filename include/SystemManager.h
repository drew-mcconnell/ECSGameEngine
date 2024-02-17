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
            systemSignatures.insert({typeName, signature});
        }

        void entityDestroyed(Entity entity){
            

        }

        void entitySignatureChanged(Entity entity, Signature entitySignature){

        }

};