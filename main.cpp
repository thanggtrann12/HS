#include <iostream>
#include <memory>
#include "Engine/Engine.h"
#include "Player/Player.h"
#include "UI/Ui.h"

int main()
{
    std::unique_ptr<Ui> ui = std::make_unique<Ui>();
    Player Player_1(PLAYER_1, ui.get());
    Player Player_2(PLAYER_2, ui.get());
    std::unique_ptr<Engine> gameEngine = std::make_unique<Engine>(Player_1, Player_2, ui.get());
    gameEngine->startGame();
    return 0;
}
