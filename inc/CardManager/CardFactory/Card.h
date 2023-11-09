#ifndef CARD_H
#define CARD_H
#include <iostream>
#include <string>
#include <memory>
#include "Helper/Helper.h"

class Card
{
public:
    virtual ~Card() = default;
    virtual void play(player_t player, const std::vector<std::shared_ptr<Card>>::iterator &cardPlayed, std::vector<GameData_t> &gameData) = 0;
    enum class CardType
    {
        FIRELORD,
        THALNOS,
        SHAMAN,
        BRAWL,
        TECHIES,
        HERO
    };

    // Getters for basic stats
    const std::string &getName() const { return name; }
    int getHP() const { return hp; }
    int getAttack() const { return attack; }
    void takeDamage(unsigned int damage) { hp = (hp > damage) ? hp - damage : 0; }
    CardType getCardType() const { return type; }
    bool isUsed() { return used; }
    void setUsed() { used = true; }
    void getBuff(int damage) { attack += damage; }
    const std::string &getSkill() const { return skill; }
    virtual std::string getDesciption() = 0;

protected:
    Card(const std::string &name, int hp, int attack, const std::string &skill, CardType type)
        : name(name), hp(hp), attack(attack), skill(skill), type(type) { used = false; }

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
    MinionCard(const std::string &name, int hp, int attack, Card::CardType type);
    void play(player_t player, const std::vector<std::shared_ptr<Card>>::iterator &cardPlayed, std::vector<GameData_t> &gameData) override;
    std::string getDesciption() override;
};

class BuffCard : public Card
{
public:
    BuffCard(const std::string &name, int hp, int attack, const std::string &skill, Card::CardType type);
    void play(player_t player, const std::vector<std::shared_ptr<Card>>::iterator &cardPlayed, std::vector<GameData_t> &gameData) override;
    std::string getDesciption() override;
};

class SpellCard : public Card
{
public:
    SpellCard(const std::string &name, const std::string &skill, Card::CardType type);
    void play(player_t player, const std::vector<std::shared_ptr<Card>>::iterator &cardPlayed, std::vector<GameData_t> &gameData) override;
    std::string getDesciption() override;
};

#endif