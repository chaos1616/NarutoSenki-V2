#pragma once
#include "Characters.h"

class AI_DogWall : public Hero
{
    void perform()
    {

        this->attack(NAttack);
    }
};
