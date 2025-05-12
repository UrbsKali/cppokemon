#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>

#include "pokemons.h"
#include "game.h"


using namespace std;

namespace utils
{
    vector<string> splitCSVLine(const string &line);

    vector<Pokemon *> loadPokemons(const string &file);
    Player loadPlayer(const string &file, const vector<Pokemon *> &dex);
    
    template <typename T>
    vector<T> loadTrainers(const string &file, const vector<Pokemon *> &dex);
}
#endif
