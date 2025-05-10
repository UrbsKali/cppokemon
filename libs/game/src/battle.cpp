#include "battle.h"


Battle::Battle(Trainer &x, Trainer &y) : a_(x), b_(y) {}

Trainer &Battle::run()
{
    cout << "\nCombat: " << a_.name() << " VS " << b_.name() << '\n';
    while (a_.hasPokemon() && b_.hasPokemon())
    {
        Pokemon *atkA = a_.active();
        Pokemon *defB = b_.active();
        atkA->attack(*defB, a_.dmgBoost());

        if (defB->fainted())
        {
            cout << defB->name() << " ennemi est K.O. !\n";
            if (!b_.hasPokemon())
                break;
        }
        Pokemon *atkB = b_.active();
        Pokemon *defA = a_.active();
        atkB->attack(*defA, b_.dmgBoost());

        if (defA->fainted())
        {
            cout << defA->name() << " est K.O. !\n";
        }
    }
    Trainer &winner = a_.hasPokemon() ? a_ : b_;
    cout << "*** " << winner.name() << " l'emporte ! ***\n";
    return winner;
}
