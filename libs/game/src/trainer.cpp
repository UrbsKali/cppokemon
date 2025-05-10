#include "trainer.h"

using std::any_of;
using std::find_if;
using std::move;

Trainer::Trainer(string n) : name_(move(n)) {}

Trainer::~Trainer() = default;

const string &Trainer::name() const
{
    return name_;
}

void Trainer::addPokemon(Pokemon *p)
{
    team_.push_back(p);
}

bool Trainer::hasPokemon() const
{
    return any_of(team_.begin(), team_.end(), [](Pokemon *p)
                  { return !p->fainted(); });
}

Pokemon *Trainer::active()
{
    return *find_if(team_.begin(), team_.end(), [](Pokemon *p)
                    { return !p->fainted(); });
}

void Trainer::healAll()
{
    for (auto &p : team_)
        p->heal();
}

double Trainer::dmgBoost() const
{
    return 1.0;
}
