#ifndef MASTER_H
#define MASTER_H

#include "trainer.h"


class Master : public Trainer
{
public:
    using Trainer::Trainer;
    double dmgBoost() const override { return 1.25; }
};

#endif