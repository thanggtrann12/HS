#ifndef HERO_H
#define HERO_H

#include "Units/Units.h"
#include "Units/Minion.h"
#include <vector>
#include <memory>

class Hero : public Units
{
public:
    Hero(const std::string &name, int maxHP, int attack);

    void addCard(std::shared_ptr<Minion> card);
    void removeBattleCard(std::shared_ptr<Minion> card);
    std::shared_ptr<Minion> playCard(int index);
    int getNumCards() const;
    void displayHand() const;
    void addToBattle(std::shared_ptr<Minion> card);
    std::vector<std::shared_ptr<Minion>> &getMinions();
    std::vector<std::shared_ptr<Minion>> &getBattleCard();

private:
    std::vector<std::shared_ptr<Minion>> battleCards;
    std::vector<std::shared_ptr<Minion>> hand;
    std::vector<std::shared_ptr<Minion>> minions;
};

#endif // HERO_H
