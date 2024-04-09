#pragma once
#include "SDL.h"
#include "System.h"
#include "Command.h"
#include "Tag.h"

// ---- TODO - MOVE THIS OUT!!! JUST FOR TESTING
#include "MoveUp.h"
#include "MoveDown.h"
#include "NullCommand.h"
#include "StopYMovement.h"

//inheret from System to InputContext can talk to entities
class InputContext : public System{
    private:
        Command * buttonWPressed;
        Command * buttonWReleased;
        Command * buttonSPressed;
        Command * buttonSReleased;

        Command * buttonA;
        Command * buttonD;

        Command * buttonUpPressed;
        Command * buttonUpReleased;
        Command * buttonDownPressed;
        Command * buttonDownReleased;

        Command * buttonLeft;
        Command * buttonRight;

// ---- TODO - MOVE THIS OUT!!! JUST FOR TESTING
        MoveUp moveUp;
        MoveDown moveDown;
        NullCommand nullC;
        StopYMovement stopY;

    public:
        InputContext();

        Entity getEntityFromTag(std::string tag) const;
        virtual void processInput();

        void setW(Command * w){buttonWPressed = w;};
        void setA(Command * a){buttonA = a;};
        void setS(Command * s){buttonSPressed = s;};
        void setD(Command * d){buttonD = d;};
        void setUp(Command * up){buttonUpPressed = up;};
        void setDown(Command * down){buttonDownPressed = down;};
        void setLeft(Command * left){buttonLeft = left;};
        void setRight(Command * right){buttonRight = right;};
        // ----- TODO - add setters for button released case
};