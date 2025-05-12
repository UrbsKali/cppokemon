#include "battle.h"


Battle::Battle(Trainer &t1, Trainer &t2) : t1(t1), t2(t2) {}

Trainer &Battle::run()
{
    cout << "\nCombat: " << t1.name() << " VS " << t2.name() << '\n';
    while (t1.hasPokemon() && t2.hasPokemon())
    {
        Pokemon *atk1 = t1.active();
        Pokemon *def2 = t2.active();
        atk1->attack(*def2, t1.dmgBoost());

        if (def2->fainted())
        {
            cout << def2->name() << " ennemi est K.O. !\n";
            if (!t2.hasPokemon())
                break;
        }
        Pokemon *atk2 = t2.active();
        Pokemon *def1 = t1.active();
        atk2->attack(*def1, t2.dmgBoost());

        if (def1->fainted())
        {
            cout << def1->name() << " est K.O. !\n";
        }
    }
    Trainer &winner = t1.hasPokemon() ? t1 : t2;
    cout << "~~~ " << winner.name() << " l'emporte ! ~~~\n";
    return winner;
}
