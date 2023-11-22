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
    void attackOpponent(Player &defender);
    PlayerId getId();
    unsigned int pickACardToPlay();
    void activeCardOnHand(Player &attacker,Player &defender, std::vector<std::shared_ptr<Card>>::iterator cardPlayed);
    void setHero(HeroType type);
    std::string getBasicInfo();
    std::shared_ptr<Hero> &getHero();
    std::vector<std::string> stats;
    int shamanCout = 0;
    ~Player();

protected:
    PlayerId Id;
    Ui *playerUi = nullptr;
    std::shared_ptr<Hero> currentHero;
    std::vector<std::shared_ptr<Card>> handCards;
    std::vector<std::shared_ptr<Card>> battleCards;
    CardManager *manager = new CardManager();
};

#endif // PLAYER_H
