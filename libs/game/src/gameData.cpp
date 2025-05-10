#include "gameData.h"


vector<Pokemon *> GameData::loadPokemons(const string &file)
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

Player GameData::loadPlayer(const string &file, const vector<Pokemon *> &dex)
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
vector<T> GameData::loadTrainers(const string &file, const vector<Pokemon *> &dex)
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

template std::vector<Leader> GameData::loadTrainers<Leader>(const std::string&, const std::vector<Pokemon*>&);
template std::vector<Master> GameData::loadTrainers<Master>(const std::string&, const std::vector<Pokemon*>&);