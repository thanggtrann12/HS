#include <iostream>
#include <string>
#include <memory>

// class Card
// {
// public:
//     virtual ~Card() = default;
//     virtual void play() = 0;

//     // Getters for basic stats
//     const std::string &getName() const { return name; }
//     int getHP() const { return hp; }
//     int getAttack() const { return attack; }
//     const std::string &getSkill() const { return skill; }

// protected:
//     Card(const std::string &name, int hp, int attack, const std::string &skill)
//         : name(name), hp(hp), attack(attack), skill(skill) {}

// private:
//     std::string name;
//     int hp;
//     int attack;
//     std::string skill;
// };

// class MinionCard : public Card
// {
// public:
//     MinionCard(const std::string &name, int hp, int attack);
//     void play() override;
// };

// class BuffCard : public Card
// {
// public:
//     BuffCard(const std::string &name, int hp, int attack, const std::string &skill);
//     void play() override;
// };

// class SpellCard : public Card
// {
// public:
//     SpellCard(const std::string &name);
//     void play() override;
// };

// MinionCard::MinionCard(const std::string &name, int hp, int attack)
//     : Card(name, hp, attack, "No Skill") {}

// void MinionCard::play()
// {
//     std::cout << "Playing Minion Card: " << getName() << " (HP: " << getHP() << ", Attack: " << getAttack() << ")." << std::endl;
// }

// BuffCard::BuffCard(const std::string &name, int hp, int attack, const std::string &skill)
//     : Card(name, hp, attack, skill) {}

// void BuffCard::play()
// {
//     std::cout << "Playing Buff Card: " << getName() << " (HP: " << getHP() << ", Attack: " << getAttack() << "). Skill: " << getSkill() << std::endl;
// }

// SpellCard::SpellCard(const std::string &name)
//     : Card(name, 0, 0, "No Skill") {}

// void SpellCard::play()
// {
//     std::cout << "Playing Spell Card: " << getName() << "." << std::endl;
// }

// class CardFactory
// {
// public:
//     virtual std::unique_ptr<Card> createCard() = 0;
// };

// class MinionCardFactory : public CardFactory
// {
// public:
//     std::unique_ptr<Card> createCard() override
//     {
//         return std::make_unique<MinionCard>("Generic Minion", 2, 2);
//     }
// };

// class BuffCardFactory : public CardFactory
// {
// public:
//     std::unique_ptr<Card> createCard() override
//     {
//         return std::make_unique<BuffCard>("Generic Buff", 1, 1, "Generic Skill");
//     }
// };

// class SpellCardFactory : public CardFactory
// {
// public:
//     std::unique_ptr<Card> createCard() override
//     {
//         return std::make_unique<SpellCard>("Generic Spell");
//     }
// };

// // int main()
// // {
// //     std::unique_ptr<CardFactory> factory;

// //     // Create a Minion card
// //     factory = std::make_unique<MinionCardFactory>();
// //     std::unique_ptr<Card> minionCard = factory->createCard();
// //     minionCard->play();

// //     // Create a Buff card
// //     factory = std::make_unique<BuffCardFactory>();
// //     std::unique_ptr<Card> buffCard = factory->createCard();
// //     buffCard->play();

// //     // Create a Spell card
// //     factory = std::make_unique<SpellCardFactory>();
// //     std::unique_ptr<Card> spellCard = factory->createCard();
// //     spellCard->play();

// //     return 0;
// // }
