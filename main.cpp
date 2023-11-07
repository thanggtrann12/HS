// #include "GameEngine/GameEngine.h"
#include "CardManager/CardManager.h"
int main()
{
    CardManager manager;
    std::vector<std::shared_ptr<Card>> card;
    manager.CardManager_initCardManager();
    card = manager.CardManager_getCardFromPocket();
    std::cout << card[0]->getHP() << std::endl;
    card[0]->takeDamage(1);
    std::cout << card[0]->getHP() << std::endl;
    return 0;
}
