#include <pokemon.h>


void Pokemon::display() const
{
    cout << name_ << " (" << t1_;
    if (!t2_.empty())
        cout << "/" << t2_;
    cout << ") - HP: " << hp_ << "/" << maxHP_ << '\n';
}
