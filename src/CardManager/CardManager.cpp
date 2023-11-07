#include "CardManager/CardManager.h"
#include "CardManager/CardFactory/CardFactory.h"

#include <iostream>
#include <string>
#include <memory>
CardManager::CardManager()
{
  CardManager_initManager();
  hero.initHero();
}
void CardManager::CardManager_initManager()
{
    std::shared_ptr<CardFactory> factory;
    factory = std::make_unique<MinionCardFactory>();
    std::shared_ptr<Card> firelordCard = factory->createCard(Card::CardType::FIRELORD);
    cardPocket.emplace_back(firelordCard);
    std::shared_ptr<Card> thalnosCard = factory->createCard(Card::CardType::THALNOS);
    cardPocket.emplace_back(thalnosCard);
    std::shared_ptr<Card> techiesCard = factory->createCard(Card::CardType::TECHIES);
    cardPocket.emplace_back(techiesCard);
    factory = std::make_unique<BuffCardFactory>();
    std::shared_ptr<Card> buffCard = factory->createCard(Card::CardType::SHAMAN);
    cardPocket.emplace_back(buffCard);
    factory = std::make_unique<SpellCardFactory>();
    std::shared_ptr<Card> spellCard = factory->createCard(Card::CardType::BRAWL);
    cardPocket.emplace_back(spellCard);
}
void CardManager::CardManager_getCardFromPocket(std::vector<std::shared_ptr<Card>> &playerHand)
{
    for(int i=0; i<10;i++)
    {
      int cardRandom = rand() % cardPocket.size();
      playerHand.push_back(cardPocket[cardRandom]);
    }
}

void CardManager::CardManager_assignHeroToPlayer(std::shared_ptr<Hero> &playerHero)
{
    int cardRandom = rand() % 2;
    playerHero = hero.GetHeroes()[cardRandom];
}
std::shared_ptr<Card> CardManager::CardManager_drawRandomCard()
{
    int cardRandom = rand() % cardPocket.size();
    return cardPocket[cardRandom];
}