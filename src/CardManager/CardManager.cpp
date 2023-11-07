#include "CardManager/CardManager.h"
#include "CardManager/CardFactory/CardFactory.h"

#include <iostream>
#include <string>
#include <memory>

void CardManager::CardManager_initCardManager()
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
std::vector<std::shared_ptr<Card>> &CardManager::CardManager_getCardFromPocket()
{
    return cardPocket;
}