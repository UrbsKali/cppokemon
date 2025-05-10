#include "utils.h"
#include "pokemons.h"

#include "player.h"
#include "master.h"
#include "leader.h"


class GameData
{
public:
    static vector<Pokemon *> loadPokemons(const string &file);
    static Player loadPlayer(const string &file, const vector<Pokemon *> &dex);
    
    template <typename T>
    static vector<T> loadTrainers(const string &file, const vector<Pokemon *> &dex);
};