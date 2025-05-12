#ifndef BATTLE_H
#define BATTLE_H

#include "trainer.h"

class Battle
{
    Trainer &t1, &t2;

public:
    Battle(Trainer &t1, Trainer &t2);
    Trainer &run();
};

#endif