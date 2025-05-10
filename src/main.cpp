#include "game.h"

using namespace std;


int main()
{
    srand(static_cast<unsigned>(time(nullptr)));
    vector<Pokemon *> pokedex = GameData::loadPokemons("./data/pokemon.csv");

    Player joueur = GameData::loadPlayer("./data/joueur.csv", pokedex);
    vector<Leader> leaders = GameData::loadTrainers<Leader>("./data/leaders.csv", pokedex);
    vector<Master> masters = GameData::loadTrainers<Master>("./data/maitres.csv", pokedex);

    Game jeu(move(joueur), pokedex, leaders, masters);
    jeu.menu();
    return 0;
}