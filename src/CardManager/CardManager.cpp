#include "CardManager/CardManager.h"
#include "assets/CardData.h"
#include "Card/CardFactory.h"
#include "Player/Player.h"
#include "Card/Card.h"
#include <iostream>
#include <string>
#include <memory>
CardManager::CardManager()
{
    std::shared_ptr<CardFactory> factory;
    factory = std::make_shared<MinionCardFactory>();
    std::shared_ptr<Card> firelordCard = factory->createCard(FIRELORD);
    cardPocket.emplace_back(firelordCard);
    std::shared_ptr<Card> thalnosCard = factory->createCard(THALNOS);
    cardPocket.emplace_back(thalnosCard);
    std::shared_ptr<Card> techiesCard = factory->createCard(TECHIES);
    cardPocket.emplace_back(techiesCard);
    factory = std::make_shared<BuffCardFactory>();
    std::shared_ptr<Card> buffCard = factory->createCard(SHAMAN);
    cardPocket.emplace_back(buffCard);
    factory = std::make_shared<SpellCardFactory>();
    std::shared_ptr<Card> spellCard = factory->createCard(BRAWL);
    cardPocket.emplace_back(spellCard);
}

std::shared_ptr<Card> CardManager::getCardFromPocket()
{
    int cardRandom = rand() % cardPocket.size();
    std::shared_ptr<Card> cardRet = cardPocket[cardRandom];
    return cardRet;
}

void CardManager::generateCardFromCardType(std::vector<std::shared_ptr<Card>> &playerTable, CardType type)
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

void CardManager::activeCard(Player &attacker,Player &defender, std::vector<std::shared_ptr<Card>>::iterator cardPlayed)
{
  (*cardPlayed)->play(attacker.getId(), attacker, defender);
  if ((*cardPlayed)->getCardType() != CardType::BRAWL)
  {
     generateCardFromCardType(attacker.getBattle(), (*cardPlayed)->getCardType());
  }
  removeFromHand(attacker.getHand(), cardPlayed);
}

void CardManager::removeFromHand(std::vector<std::shared_ptr<Card>> &playerHand, std::vector<std::shared_ptr<Card>>::iterator cardRemove)
{
  playerHand.erase(cardRemove);
}