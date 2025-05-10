#ifndef TRAINER_H
#define TRAINER_H

#include "pokemon.h"
#include <vector>
#include <string>
#include <algorithm>
using std::string;
using std::vector;

class Pokemon; // Forward declaration

class Trainer
{
protected:
    string name_;
    vector<Pokemon *> team_;

public:
    explicit Trainer(string n);
    virtual ~Trainer();

    const string &name() const;

    void addPokemon(Pokemon *p);

    bool hasPokemon() const;

    Pokemon *active();

    void healAll();

    virtual double dmgBoost() const;
};

#endif