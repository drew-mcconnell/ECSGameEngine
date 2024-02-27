#pragma once
#include "Command.h"

class NullCommand : public Command{
    public:
        virtual void execute(Entity entity){};
};