#pragma once
#include "Command.h"

class MoveUp : public Command{
    public:
        virtual void execute(Entity entity);
};