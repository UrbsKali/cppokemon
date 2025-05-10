#ifndef PLAYER_H
#define PLAYER_H

#include "trainer.h"

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

#endif