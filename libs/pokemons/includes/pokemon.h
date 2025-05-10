#include <iostream>
#include <string>

#ifndef POKEMON_H
#define POKEMON_H

using namespace std;

class Pokemon
{
protected:
    string name_;
    string t1_, t2_;
    int maxHP_, hp_;
    string attackName_;
    int baseDmg_;

public:
    Pokemon(string n, string a, string b, int hp, string atk, int dmg)
        : name_(move(n)), t1_(a), t2_(b), maxHP_(hp), hp_(hp),
          attackName_(move(atk)), baseDmg_(dmg)
    {
    }

    virtual ~Pokemon() = default;

    const string &name() const { return name_; }
    const string &type1() const { return t1_; }
    const string &type2() const { return t2_; }
    bool fainted() const { return hp_ <= 0; }

    virtual int attack(Pokemon &target, double dmgBoost = 1.0) = 0;
    void receive(int d) { hp_ = max(0, hp_ - d); }
    void heal() { hp_ = maxHP_; }
    void display() const;
    virtual void afficherType() const = 0;
};

#endif // POKEMON_H