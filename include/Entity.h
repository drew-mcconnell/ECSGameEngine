#pragma once
#include "constants.h"

class Entity{
    private:
        uint8_t ID;
        Signature signature;

    public:
        Entity(){};
        Entity(uint8_t id, Signature signature):ID(id),signature(signature){};
        uint8_t getID(){return ID;};
        void setSignature(Signature sig){signature = sig;};
        Signature getSignature(){return signature;};
};