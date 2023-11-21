#include <iostream>
#include "Engine/Engine.h"
#include "Player/Player.h"
#include "UI/Ui.h"
int main()
{
    Ui *ui = new Ui();
    Player Player_1(PLAYER_1, ui);
    Player Player_2(PLAYER_2, ui);
    Engine *gameEngine = new Engine(Player_1, Player_2, ui);
    gameEngine->startGame();
    delete ui;
    return 0;
}