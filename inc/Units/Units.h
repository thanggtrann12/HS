#ifndef UNITS_H
#define UNITS_H

#include <string>
#include <memory> // Add this line to include <memory>
enum class CardType
{
    MINION,
    BRAWL,
    TECHIES,
    SHAMAN,
    SPELL,
    HERO
};
class Units
{
public:
    Units(const std::string &name, int maxHP, int attack, CardType type);
    virtual ~Units();

    void takeDamage(int damage);
    int attack(Units *target);

    bool isAlive() const;
    int getAttack() const;
    void setAttack(int newAtk);
    const std::string &getName() const;
    int getCurrentHP() const;
    void boostAttack(int boost);
    bool isActivated();
    void setActivated(bool state);
    std::string getDescription();
    int getMaxHp() const;
    int getTotalDamage();
    CardType getCardType() const;

protected:
    std::string name;
    int maxHP;
    int currentHP;
    int _attack;
    bool isActive = false;
    CardType cardType;
};

#endif // UNITS_H
