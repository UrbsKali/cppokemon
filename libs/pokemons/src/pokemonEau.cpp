#include <pokemonEau.h>

int PokemonEau::attack(Pokemon &target, double dmgBoost)
{
    double m = 1;
    double n = 1;
    if (target.type1() == "Feu" || target.type2() == "Feu")
        m = 2;
    if (target.type1() == "Sol" || target.type2() == "Sol")
        m = 2;
    if (target.type1() == "Roche" || target.type2() == "Roche")
        m = 2;

    if (target.type1() == "Eau" || target.type2() == "Eau")
        n = 0.5;
    if (target.type1() == "Plante" || target.type2() == "Plante")
        n = 0.5;
    if (target.type1() == "Dragon" || target.type2() == "Dragon")
        n = 0.5;
    int dmg = static_cast<int>(baseDmg_ * m * n * dmgBoost);
    target.receive(dmg);
    cout << name_ << " utilise " << attackName_ << " et inflige " << dmg
         << " dégâts à " << target.name() << " !\n";
    if (m * n >= 2)
    {
        cout << "C'est super efficace ! (" << m * n << "x)\n";
    }
    if (m * n < 1)
    {
        cout << "Ce n'est pas très efficace... (" << m * n << "x)\n";
    }
    return dmg;
}