#include "pokemon.h"


class PokemonGenerique : public Pokemon
{
public:
    PokemonGenerique(string n, string a, string b, int hp, string atk, int dmg)
        : Pokemon(move(n), move(a), move(b), hp, move(atk), dmg)
    {
    }
    void afficherType() const override { cout << name_ << "(" << t1_ << ")\n"; }
    int attack(Pokemon &target, double dmgBoost = 1.0);
};