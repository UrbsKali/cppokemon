#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "leader.h"
#include "master.h"
#include "battle.h"

#include <unordered_map>

class Game
{
public:
    Game(Player player,
         vector<Pokemon *> &pokedex,
         vector<Leader> leaders,
         vector<Master> masters);

    void mainloop();

private:
    Player player_;
    vector<Leader> leaders_;
    vector<Master> masters_;
    unordered_map<string, Pokemon *> pokedex_;

    Pokemon *dex(const string &n) { return pokedex_.at(n); }
    
    void fightLeader();
    void fightMaster();
};

#endif