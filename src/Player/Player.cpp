#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "Player/Player.h"
#include "UI/Ui.h"
#include "Hero/Hero.h"
Player::Player(PlayerId playerId, Ui *ui) : Id(playerId), playerUi(ui)
{
    std::cout << "Initialize ID[" << Id + 1 << "]" << std::endl;
}

PlayerId Player::getId()
{
    return Id;
}

void Player::drawCard(unsigned int num)
{
    for (size_t i = 0; i < num; i++)
    {
        std::shared_ptr<Card> cardFromPocket = manager->getCardFromPocket();
        handCards.emplace_back(cardFromPocket);
    }
}

void Player::updateCard(CardType type)
{
    manager->generateCardFromCardType(handCards, type);
}

std::vector<std::shared_ptr<Card>> &Player::getHand()
{
    return handCards;
}

std::vector<std::shared_ptr<Card>> &Player::getBattle()
{
    return battleCards;
}

unsigned int Player::pickACardToPlay()
{
    unsigned int cardChoiced;
    std::vector<Player> playerVector;
    if (Id == PLAYER_1)
    {
        playerVector = {*this, Player()};
    }
    if (Id == PLAYER_2)
    {
        playerVector = {Player(), *this};
    }

    playerUi->onUiStateChangeOnState(Ui::CHOOSING_CARD, playerVector, Id, cardChoiced);

    return cardChoiced;
}

void Player::activeCardOnHand(Player &attacker,Player &defender, std::vector<std::shared_ptr<Card>>::iterator cardPlayed)
{
  attackOpponent(defender);
  manager->activeCard(attacker, defender, cardPlayed);
}

void Player::setHero(HeroType type)
{
    currentHero = std::make_shared<Hero>(type);
}

std::string Player::getBasicInfo()
{
    return "Player [" + std::to_string(this->Id + 1) + "]'s Hero: " + currentHero->getDescription();
}

std::shared_ptr<Hero> &Player::getHero()
{
    return currentHero;
}
void Player::attackOpponent(Player &defender)
{
  defender.getHero()->takeDamage(this->getHero()->getAttack());
}

Player::~Player()
{
    std::cout << "Destroy ID[" << Id + 1 << "]" << std::endl;
}