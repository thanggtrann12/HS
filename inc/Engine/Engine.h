#ifndef ENGINE_H
#define ENGINE_H
#include "Player/Player.h"
#include <vector>
#include <memory>
#include "UI/Ui.h"
#include "MySocket/MySocket.h"
class Engine
{
public:
    Engine(Player &player1, Player &player2, Ui *ui);
    void startGame();
    bool isGameOver(PlayerId playerID);

private:
    void initializeOperationMode();
    void endTurnForPlayer();
    void processPlayerTurn(PlayerId playerID, unsigned int cardPlayed, std::vector<Player> &players);
    void updatePlayerHandCard(Player &hostPlayer, Player &clientPlayer);
    void processHostPlayerTurn();
    void processClientPlayerTurn();
    void processSinglePlayerTurn();
    void registerUiModule(Ui *subUi);
    void onUiStateChange(Ui::UiState state, std::vector<Player> &players, PlayerId playerId, unsigned int &clone);
    ~Engine();
private:


protected:
    std::shared_ptr<MySocket> mySocket = std::make_shared<MySocket>();
    Ui *uiObs;
    std::vector<Player> playerLists;
    unsigned int nextTurn = PLAYER_2;
    unsigned int currentTurn = PLAYER_1;
    MySocket::Mode currentGameMode = MySocket::UNKNOWN;
    PlayerId hostPlayerID = PLAYER_1;
    PlayerId clientPlayerID = PLAYER_2;
    int roundCount = 0;

};

#endif // ENGINE_H