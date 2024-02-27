#pragma once
#include "Command.h"

class StopYMovement : public Command{
    public:
        virtual void execute(Entity entity);
};