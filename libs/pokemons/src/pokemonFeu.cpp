#include <pokemonFeu.h>

int PokemonFeu::attack(Pokemon &target, double dmgBoost)
{
    double m = 1;
    double n = 1;
    if (target.type1() == "Plante" || target.type2() == "Plante")
        m = 2;
    if (target.type1() == "Glace" || target.type2() == "Glace")
        m = 2;
    if (target.type1() == "Insecte" || target.type2() == "Insecte")
        m = 2;
    if (target.type1() == "Acier" || target.type2() == "Acier")
        m = 2;

    if (target.type1() == "Eau" || target.type2() == "Eau")
        n = 0.5;
    if (target.type1() == "Roche" || target.type2() == "Roche")
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