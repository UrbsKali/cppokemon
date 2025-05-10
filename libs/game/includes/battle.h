#include "trainer.h"

class Battle
{
    Trainer &a_, &b_;

public:
    Battle(Trainer &x, Trainer &y);
    Trainer &run();
};