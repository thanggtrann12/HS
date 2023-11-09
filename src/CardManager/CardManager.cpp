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
    factory = std::make_shared<MinionCardFactory>();
    std::shared_ptr<Card> firelordCard = factory->createCard(Card::CardType::FIRELORD);
    cardPocket.emplace_back(firelordCard);
    std::shared_ptr<Card> thalnosCard = factory->createCard(Card::CardType::THALNOS);
    cardPocket.emplace_back(thalnosCard);
    std::shared_ptr<Card> techiesCard = factory->createCard(Card::CardType::TECHIES);
    cardPocket.emplace_back(techiesCard);
    factory = std::make_shared<BuffCardFactory>();
    std::shared_ptr<Card> buffCard = factory->createCard(Card::CardType::SHAMAN);
    cardPocket.emplace_back(buffCard);
    factory = std::make_shared<SpellCardFactory>();
    std::shared_ptr<Card> spellCard = factory->createCard(Card::CardType::BRAWL);
    cardPocket.emplace_back(spellCard);
}
void CardManager::CardManager_getCardFromPocket(std::vector<std::shared_ptr<Card>> &playerHand)
{
    for (int i = 0; i < 10; i++)
    {
        int cardRandom = rand() % cardPocket.size();
        playerHand.push_back(cardPocket[cardRandom]);
    }
}

std::shared_ptr<Hero> CardManager::CardManager_assignHeroToPlayer(unsigned int heroNum)
{

    return std::make_shared<Hero>(*hero.getHero()[heroNum]);
}

std::shared_ptr<Card> CardManager::CardManager_drawRandomCard()
{
    int cardRandom = rand() % cardPocket.size();
    return cardPocket[cardRandom];
}

void CardManager::CardManager_pushCardToTable(std::vector<std::shared_ptr<Card>> &playerTable, Card::CardType type)
{
    std::shared_ptr<CardFactory> factory;
    switch (type)
    {
    case Card::CardType::FIRELORD:
        factory = std::make_shared<MinionCardFactory>();
        playerTable.emplace_back(factory->createCard(Card::CardType::FIRELORD));
        break;
    case Card::CardType::THALNOS:
        factory = std::make_shared<MinionCardFactory>();
        playerTable.emplace_back(factory->createCard(Card::CardType::THALNOS));
        break;
    case Card::CardType::TECHIES:
        factory = std::make_shared<MinionCardFactory>();
        playerTable.emplace_back(factory->createCard(Card::CardType::TECHIES));
        break;
    case Card::CardType::SHAMAN:
        factory = std::make_shared<BuffCardFactory>();
        playerTable.emplace_back(factory->createCard(Card::CardType::SHAMAN));
        break;
    case Card::CardType::BRAWL:
        factory = std::make_shared<SpellCardFactory>();
        playerTable.emplace_back(factory->createCard(Card::CardType::BRAWL));
        break;
    }
}