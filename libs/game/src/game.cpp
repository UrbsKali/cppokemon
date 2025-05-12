#include "game.h"
#include <stdlib.h>

// Constructor
Game::Game(Player player, vector<Pokemon *> &pokedex, vector<Leader> leaders, vector<Master> masters)
    : player_(move(player)), leaders_(move(leaders)), masters_(move(masters))
{
    for (auto &p : pokedex)
    {
        pokedex_.emplace(p->name(), p);
    }
}

void Game::mainloop()
{
    bool run = true;
    while (run)
    {
        cout << "\n#------~ MENU ~------#\n"
             << "1 - Mon équipe\n2 - Mes stats \n3 - Soigner l'équipe\n"
             << "4 - Affronter un leader\n5 - Affronter un Maître\n6 - Quitter\nChoix: ";
        int c;
        cin >> c;
        system("clear");

        switch (c)
        {
        case 1:
            player_.showTeam();
            break;
        case 2:
            player_.stats();
            break;
        case 3:
            player_.healAll();
            cout << "Équipe soignée.\n";
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

void Game::fightLeader()
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

void Game::fightMaster()
{
    if (player_.badgeCount() < static_cast<int>(leaders_.size()))
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
