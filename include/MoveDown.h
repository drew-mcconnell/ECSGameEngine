#pragma once
#include "Command.h"

class MoveDown : public Command{
    public:
        virtual void execute(Entity e);
};