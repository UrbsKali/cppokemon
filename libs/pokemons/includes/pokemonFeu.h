#include "pokemon.h"

class PokemonFeu : public Pokemon
{
public:
    PokemonFeu(string n, string a, string b, int hp, string atk, int dmg)
        : Pokemon(move(n), move(a), move(b), hp, move(atk), dmg)
    {
    }
    void afficherType() const override { cout << name_ << " (Feu)\n"; }
    int attack(Pokemon &target, double dmgBoost = 1.0);

};