#include <iostream>
#include <string>
#include <memory>

class Card
{
public:
    virtual ~Card() = default;
    virtual void play() = 0;

    // Getters for basic stats
    const std::string &getName() const { return name; }
    int getHP() const { return hp; }
    int getAttack() const { return attack; }
    const std::string &getSkill() const { return skill; }

protected:
    Card(const std::string &name, int hp, int attack, const std::string &skill)
        : name(name), hp(hp), attack(attack), skill(skill) {}

private:
    std::string name;
    int hp;
    int attack;
    std::string skill;
};

class MinionCard : public Card
{
public:
    MinionCard(const std::string &name, int hp, int attack);
    void play() override;
};

class BuffCard : public Card
{
public:
    BuffCard(const std::string &name, int hp, int attack, const std::string &skill);
    void play() override;
};

class SpellCard : public Card
{
public:
    SpellCard(const std::string &name);
    void play() override;
};

MinionCard::MinionCard(const std::string &name, int hp, int attack)
    : Card(name, hp, attack, "No Skill") {}

void MinionCard::play()
{
    std::cout << "Playing Minion Card: " << getName() << " (HP: " << getHP() << ", Attack: " << getAttack() << ")." << std::endl;
}

BuffCard::BuffCard(const std::string &name, int hp, int attack, const std::string &skill)
    : Card(name, hp, attack, skill) {}

void BuffCard::play()
{
    std::cout << "Playing Buff Card: " << getName() << " (HP: " << getHP() << ", Attack: " << getAttack() << "). Skill: " << getSkill() << std::endl;
}

SpellCard::SpellCard(const std::string &name)
    : Card(name, 0, 0, "No Skill") {}

void SpellCard::play()
{
    std::cout << "Playing Spell Card: " << getName() << "." << std::endl;
}

int main()
{
    std::unique_ptr<Card> ragnarosCard = std::make_unique<MinionCard>("Ragnaros the Firelord", 1, 3);
    ragnarosCard->play();

    std::unique_ptr<Card> buffCard = std::make_unique<BuffCard>("Flametongue Totem", 3, 0, "Provides +1 Attack to alliance minions");
    buffCard->play();

    std::unique_ptr<Card> spellCard = std::make_unique<SpellCard>("Brawl");
    spellCard->play();

    return 0;
}
