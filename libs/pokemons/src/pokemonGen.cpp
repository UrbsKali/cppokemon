#include <pokemonGen.h>

int PokemonGenerique::attack(Pokemon &target, double dmgBoost)
{
    int dmg = static_cast<int>(baseDmg_ * dmgBoost);
        target.receive(dmg);
        cout << name_ << " utilise " << attackName_ << " et inflige " << dmg
             << " dégâts à " << target.name() << " !\n";
        return dmg;
}