#ifndef ENGINE_H
#define ENGINE_H
#include "Player/Player.h"
#include <vector>
#include "UI/Ui.h"
#include "MySocket/MySocket.h"
class Engine
{
private:
    enum Mode
    {
        HOST = 1,
        CLIENT,
        SINGLE,
        UNKNOWN
    };

public:
    Engine(Player &player1, Player &player2, Ui *ui);
    void startGame();
    bool isEndGame(PlayerId playerID);

private:
    void endTurn();
    void handlingPlayerTurn(PlayerId playerID, unsigned int cardPlayed, std::vector<Player> &players);
    void generateCardsForEachMode(MySocket *host, Player &hostPlayer, MySocket *client, Player &clientPlayer);
    void startHostMode(MySocket *host);
    void startClientMode(MySocket *client);
    void startSingleMode();
    void addUiObserver(Ui *subUi);
    void updateUi(Ui::UiState state, std::vector<Player> &players, PlayerId playerId, unsigned int &clone);
    ~Engine();

protected:
    Ui *uiObs;
    std::vector<Player> playerLists;
    unsigned int nextTurn = PLAYER_2;
    unsigned int currentTurn = PLAYER_1;
    Mode currentGameMode = UNKNOWN;
    PlayerId hostPlayerID = PLAYER_1;
    PlayerId clientPlayerID = PLAYER_2;
    int roundCount = 0;
};

#endif // ENGINE_H