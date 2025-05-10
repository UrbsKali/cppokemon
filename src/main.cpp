#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <ctime>

#include "pokemons.h"
#include "utils.h"

using namespace std;

class GameData
{
public:
    static vector<Pokemon *> loadPokemons(const string &file)
    {
        vector<Pokemon *> out;
        ifstream f(file);
        if (!f)
        {
            cerr << "Erreur ouverture " << file << '\n';
            return out;
        }
        string line;
        getline(f, line);
        while (getline(f, line))
        {
            auto c = utils::splitCSVLine(line);
            if (c.size() < 6)
                continue;

            string t1 = c[1];
            string t2 = c[2].empty() ? "" : c[2];

            if (t1 == "Feu")
            {
                out.push_back(new PokemonFeu(c[0], t1, t2, stoi(c[3]), c[4], stoi(c[5])));
            }
            else if (t1 == "Eau")
            {
                out.push_back(new PokemonEau(c[0], t1, t2, stoi(c[3]), c[4], stoi(c[5])));
            }
            else if (t1 == "Plante")
            {
                out.push_back(new PokemonPlante(c[0], t1, t2, stoi(c[3]), c[4], stoi(c[5])));
            }
            else
            {
                out.push_back(new PokemonGenerique(c[0], t1, t2, stoi(c[3]), c[4], stoi(c[5])));
            }
        }
        return out;
    }
};

class Trainer
{
protected:
    string name_;
    vector<Pokemon *> team_;

public:
    explicit Trainer(string n) : name_(move(n)) {}
    virtual ~Trainer() = default;

    const string &name() const { return name_; }

    void addPokemon(Pokemon *p) { team_.push_back(p); }

    bool hasPokemon() const
    {
        return any_of(team_.begin(), team_.end(), [](Pokemon *p)
                      { return !p->fainted(); });
    }

    Pokemon *active()
    {
        return *find_if(team_.begin(), team_.end(), [](Pokemon *p)
                        { return !p->fainted(); });
    }

    void healAll()
    {
        for (auto &p : team_)
            p->heal();
    }
    virtual double dmgBoost() const { return 1.0; }
};

class Player : public Trainer
{
    int badges_ = 0;
    int wins_ = 0;
    int losses_ = 0;

public:
    using Trainer::Trainer;
    void stats() const
    {
        cout << "Badges: " << badges_ << "  Victoires: " << wins_ << "  Défaites: " << losses_ << '\n';
    }
    void showTeam() const
    {
        for (const auto &p : team_)
        {
            p->display();
        }
    }
    void addWin() { ++wins_; }
    void addLoss() { ++losses_; }
    void addBadge() { ++badges_; }
    int badgeCount() const { return badges_; }
};

class GymLeader : public Trainer
{
    string arene_;
    string badge_;

public:
    GymLeader(string n, string arene, string badge)
        : Trainer(move(n)), arene_(move(arene)), badge_(move(badge))
    {
    }
    const string &badge() const { return badge_; }
    const string &arene() const { return arene_; }
};

class Master : public Trainer
{
public:
    using Trainer::Trainer;
    double dmgBoost() const override { return 1.25; }
};

class Battle
{
    Trainer &a_, &b_;

public:
    Battle(Trainer &x, Trainer &y) : a_(x), b_(y) {}
    Trainer &run()
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
};

class Game
{
    Player player_;
    vector<GymLeader> leaders_;
    vector<Master> masters_;
    unordered_map<string, Pokemon *> dex_;

    Pokemon *dex(const string &n) { return dex_.at(n); }

public:
    Game(Player player,
         vector<Pokemon *> &pokedex,
         vector<GymLeader> leaders,
         vector<Master> masters)
        : player_(move(player)),
          leaders_(move(leaders)),
          masters_(move(masters))
    {

        for (auto &p : pokedex)
        {
            dex_.emplace(p->name(), p);
        }
    }

    void menu()
    {
        bool run = true;
        while (run)
        {
            cout << "\n===== MENU =====\n"
                 << "1. Mon équipe\n2. Soigner l'équipe\n3. Mes stats\n"
                 << "4. Affronter un leader\n5. Affronter un Maître\n6. Quitter\nChoix: ";
            int c;
            cin >> c;
            switch (c)
            {
            case 1:
                player_.showTeam();
                break;
            case 2:
                player_.healAll();
                cout << "Équipe soignée.\n";
                break;
            case 3:
                player_.stats();
                break;
            case 4:
                fightLeader();
                break;
            case 5:
                fightMaster();
                break;
            case 6:
                run = false;
                break;
            default:
                cout << "Choix invalide.\n";
            }
        }
    }

private:
    void fightLeader()
    {
        if (leaders_.empty())
        {
            cout << "Aucun leader.\n";
            return;
        }
        cout << "\nSélectionnez un leader :\n";
        for (size_t i = 0; i < leaders_.size(); ++i)
            cout << i + 1 << ": " << leaders_[i].name()
                 << " (" << leaders_[i].arene() << ")\n";
        size_t idx;
        cin >> idx;
        if (!idx || idx > leaders_.size())
            return;
        Battle b(player_, leaders_[idx - 1]);
        Trainer &w = b.run();
        if (&w == &player_)
        {
            player_.addWin();
            player_.addBadge();
            leaders_[idx - 1].healAll();
            cout << "Vous remportez le badge " << leaders_[idx - 1].badge() << " !\n";
        }
        else
        {
            player_.addLoss();
            player_.healAll();
            leaders_[idx - 1].healAll();
        }
    }

    void fightMaster()
    {
        if (player_.badgeCount() < leaders_.size())
        {
            cout << "Tous les badges sont requis.\n";
            return;
        }
        if (masters_.empty())
        {
            cout << "Aucun maître.\n";
            return;
        }
        size_t idx = rand() % masters_.size();
        Battle b(player_, masters_[idx]);
        Trainer &w = b.run();
        if (&w == &player_)
        {
            player_.addWin();
            cout << "Vous êtes le nouveau Maître Pokémon !\n";
        }
        else
        {
            player_.addLoss();
            player_.healAll();
            masters_[idx].healAll();
        }
    }
};

Player loadPlayer(const string &file, const vector<Pokemon *> &dex)
{
    ifstream f(file);
    if (!f)
        throw runtime_error("Impossible d'ouvrir " + file);

    string line;
    getline(f, line); // header
    if (!getline(f, line))
        throw runtime_error("CSV vide");
    auto c = utils::splitCSVLine(line); // [Nom, Poke1..6]

    Player pl(c[0]);
    for (size_t i = 1; i < c.size(); ++i)
    {
        if (c[i].empty())
            continue;
        auto it = find_if(dex.begin(), dex.end(),
                          [&](Pokemon *p)
                          { return p->name() == c[i]; });
        if (it != dex.end())
            pl.addPokemon(*it);
    }
    return pl;
}

template <typename T>
vector<T> loadTrainers(const string &file, const vector<Pokemon *> &dex)
{
    vector<T> out;
    ifstream f(file);
    string line;
    getline(f, line); // header

    while (getline(f, line))
    {
        if (line.empty())
            continue;
        auto c = utils::splitCSVLine(line);
        if (c.empty())
            continue;

        if constexpr (is_same_v<T, Master>)
        {

            T t(c[0]);
            for (size_t i = 1; i < c.size(); ++i)
            {
                if (c[i].empty())
                    continue;
                auto it = find_if(dex.begin(), dex.end(),
                                  [&](Pokemon *p)
                                  { return p->name() == c[i]; });
                if (it != dex.end())
                    t.addPokemon(*it);
            }
            out.push_back(move(t));
        }
        else
        {

            if (c.size() < 2)
                continue;
            T t(c[0], c[1], c[2]);
            for (size_t i = 2; i < c.size(); ++i)
            {
                if (c[i].empty())
                    continue;
                auto it = find_if(dex.begin(), dex.end(),
                                  [&](Pokemon *p)
                                  { return p->name() == c[i]; });
                if (it != dex.end())
                    t.addPokemon(*it);
            }
            out.push_back(move(t));
        }
    }
    return out;
}

int main()
{
    srand(static_cast<unsigned>(time(nullptr)));
    vector<Pokemon *> pokedex = GameData::loadPokemons("./data/pokemon.csv");

    Player joueur = loadPlayer("./data/joueur.csv", pokedex);
    vector<GymLeader> leaders = loadTrainers<GymLeader>("./data/leaders.csv", pokedex);
    vector<Master> masters = loadTrainers<Master>("./data/maitres.csv", pokedex);

    Game jeu(move(joueur), pokedex, leaders, masters);
    jeu.menu();
    return 0;
}