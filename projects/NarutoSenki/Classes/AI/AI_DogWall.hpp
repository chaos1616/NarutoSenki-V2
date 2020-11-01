#pragma once
#include "Characters.h"

class AI_DogWall : public Hero
{
public:
    void perform();
};

void AI_DogWall::perform()
{

    this->attack(NAttack);
}
