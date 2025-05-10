#include "pokemon.h"

class PokemonEau : public Pokemon
{
public:
    PokemonEau(string n, string a, string b, int hp, string atk, int dmg)
        : Pokemon(move(n), move(a), move(b), hp, move(atk), dmg)
    {
    }
    void afficherType() const override { cout << name_ << " (Eau)\n"; }
    int attack(Pokemon &target, double dmgBoost = 1.0) ;
};