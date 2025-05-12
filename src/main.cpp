#include "game.h"
#include "utils.h"

using namespace std;


int main()
{
    srand(static_cast<unsigned>(time(nullptr)));
    vector<Pokemon *> pokedex = utils::loadPokemons("./data/pokemon.csv");

    Player joueur = utils::loadPlayer("./data/joueur.csv", pokedex);
    vector<Leader> leaders = utils::loadTrainers<Leader>("./data/leaders.csv", pokedex);
    vector<Master> masters = utils::loadTrainers<Master>("./data/maitres.csv", pokedex);

    Game jeu(move(joueur), pokedex, leaders, masters);
    jeu.mainloop();
    return 0;
}