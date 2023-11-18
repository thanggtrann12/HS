#ifndef CARD_H
#define CARD_H
#include <iostream>
#include <string>
#include <memory>
#include "Helper/Helper.h"
#include "CardFactory/CardData.h"
class Card
{
public:
    virtual ~Card() = default;
    virtual void play(player_t player, const std::vector<std::shared_ptr<Card>>::iterator &cardPlayed, std::vector<GameData_t> &gameData) = 0;

    // Getters for basic stats
    const std::string &getName() const { return name; }
    int getHP() const { return hp; }
    int getAttack() const { return attack; }
    void takeDamage(unsigned int damage) { hp = (hp > damage) ? hp - damage : 0; }
    CardType getCardType() const { return type; }
    void getBuff(int damage) { attack += damage; }
    const std::string &getSkill() const { return skill; }
    virtual std::string getDesciption() = 0;

protected:
    Card(CardType type)
        : name(cardDatas[type].name), hp(cardDatas[type].health), attack(cardDatas[type].attack), skill(cardDatas[type].skill), type(type) {}

private:
    std::string name;
    int hp;
    int attack;
    CardType type;
    std::string skill;
    bool used;
};

class MinionCard : public Card
{
public:
    MinionCard(CardType type);
    void play(player_t player, const std::vector<std::shared_ptr<Card>>::iterator &cardPlayed, std::vector<GameData_t> &gameData) override;
    std::string getDesciption() override;
};

class BuffCard : public Card
{
public:
    BuffCard(CardType type);
    void play(player_t player, const std::vector<std::shared_ptr<Card>>::iterator &cardPlayed, std::vector<GameData_t> &gameData) override;
    std::string getDesciption() override;
};

class SpellCard : public Card
{
public:
    SpellCard(CardType type);
    void play(player_t player, const std::vector<std::shared_ptr<Card>>::iterator &cardPlayed, std::vector<GameData_t> &gameData) override;
    std::string getDesciption() override;
};

#endif