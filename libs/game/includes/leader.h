#ifndef LEADER_H
#define LEADER_H

#include "trainer.h"

class Leader : public Trainer
{
    string arene_;
    string badge_;

public:
    Leader(string n, string arene, string badge)
        : Trainer(move(n)), arene_(move(arene)), badge_(move(badge))
    {
    }
    const string &badge() const { return badge_; }
    const string &arene() const { return arene_; }
};

#endif