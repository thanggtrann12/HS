#include "CardManager/CardManager.h"
#include "CardFactory/Card.h"
#include "CardFactory/CardFactory.h"
#include <iostream>
#include <string>
#include <memory>
CardManager::CardManager()
{
    initManager();
    hero.initHero();
}
void CardManager::initManager()
{
    std::shared_ptr<CardFactory> factory;
    factory = std::make_shared<MinionCardFactory>();
    std::shared_ptr<Card> firelordCard = factory->createCard(CardType::FIRELORD);
    cardPocket.emplace_back(firelordCard);
    std::shared_ptr<Card> thalnosCard = factory->createCard(CardType::THALNOS);
    cardPocket.emplace_back(thalnosCard);
    std::shared_ptr<Card> techiesCard = factory->createCard(CardType::TECHIES);
    cardPocket.emplace_back(techiesCard);
    factory = std::make_shared<BuffCardFactory>();
    std::shared_ptr<Card> buffCard = factory->createCard(CardType::SHAMAN);
    cardPocket.emplace_back(buffCard);
    factory = std::make_shared<SpellCardFactory>();
    std::shared_ptr<Card> spellCard = factory->createCard(CardType::BRAWL);
    cardPocket.emplace_back(spellCard);
}
void CardManager::getCardFromPocket(std::vector<std::shared_ptr<Card>> &playerHand)
{
    for (int i = 0; i < 10; i++)
    {
        int cardRandom = rand() % cardPocket.size();
        playerHand.push_back(cardPocket[cardRandom]);
    }
}

std::shared_ptr<Hero> CardManager::assignHeroToPlayer(unsigned int heroNum)
{

    return std::make_shared<Hero>(*hero.getHero()[heroNum]);
}

std::shared_ptr<Card> CardManager::drawRandomCard()
{
    int cardRandom = rand() % cardPocket.size();
    return cardPocket[cardRandom];
}

void CardManager::pushCardToTable(std::vector<std::shared_ptr<Card>> &playerTable, CardType type)
{
    std::shared_ptr<CardFactory> factory;
    switch (type)
    {
    case CardType::FIRELORD:
        factory = std::make_shared<MinionCardFactory>();
        playerTable.emplace_back(factory->createCard(CardType::FIRELORD));
        break;
    case CardType::THALNOS:
        factory = std::make_shared<MinionCardFactory>();
        playerTable.emplace_back(factory->createCard(CardType::THALNOS));
        break;
    case CardType::TECHIES:
        factory = std::make_shared<MinionCardFactory>();
        playerTable.emplace_back(factory->createCard(CardType::TECHIES));
        break;
    case CardType::SHAMAN:
        factory = std::make_shared<BuffCardFactory>();
        playerTable.emplace_back(factory->createCard(CardType::SHAMAN));
        break;
    case CardType::BRAWL:
        factory = std::make_shared<SpellCardFactory>();
        playerTable.emplace_back(factory->createCard(CardType::BRAWL));
        break;
    }
}