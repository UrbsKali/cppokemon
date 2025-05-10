#include "gameData.h"
#include "player.h"
#include "leader.h"
#include "master.h"
#include "battle.h"

class Game
{
public:
    Game(Player player,
         vector<Pokemon *> &pokedex,
         vector<Leader> leaders,
         vector<Master> masters);

    void menu();

private:
    Player player_;
    vector<Leader> leaders_;
    vector<Master> masters_;
    unordered_map<string, Pokemon *> dex_;

    Pokemon *dex(const string &n) { return dex_.at(n); }
    
    void fightLeader();
    void fightMaster();
};
