#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "Card/Card.h"
#include "CardManager/CardManager.h"
#include "Hero/Hero.h"
enum PlayerId
{
    PLAYER_1 = 0,
    PLAYER_2,
    MAX_PLAYER
};
class Ui;
class Hero;
class Player
{
public:
    Player(PlayerId playerId, Ui *ui);
    Player(){};
    void drawCard(unsigned int num);
    std::vector<std::shared_ptr<Card>> &getHand();
    std::vector<std::shared_ptr<Card>> &getBattle();
    void updateCard(CardType type);
    PlayerId getId();
    unsigned int pickACardToPlay();
    void setHero(HeroType type);
    void activeCardOnHand(Player &attacker, Player &defender, std::vector<std::shared_ptr<Card>>::iterator cardPlayed);
    std::string getBasicInfo();
    std::shared_ptr<Hero> &getHero();
    void attackOpponent(Player &defender);
    ~Player();
    std::vector<std::string> stats;
    int shamanCout = 0;

protected:
#ifdef GTEST_FRIEND
  GTEST_FRIEND
#endif
    PlayerId Id;
    Ui *playerUi = nullptr;
    std::shared_ptr<Hero> currentHero;
    std::vector<std::shared_ptr<Card>> handCards;
    std::vector<std::shared_ptr<Card>> battleCards;
    CardManager *manager = new CardManager();
};

#endif // PLAYER_H