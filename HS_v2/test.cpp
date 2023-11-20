#include <iostream>
enum PlayerId
{
    PLAYER_1,
    PLAYER_2
};

class Player
{
private:
    PlayerId Id;
    // Other member variables and functions...

public:
    Player(PlayerId playerId);
    PlayerId getId();
    // Other member functions...
};

Player::Player(PlayerId playerId) : Id(playerId)
{
    // Other constructor initialization...
}

PlayerId Player::getId()
{
    return Id;
}

int main()
{
    Player player1(PLAYER_1);
    Player player2(PLAYER_2);

    std::cout << "Assign player [" << player1.getId() << "] and [" << player2.getId() << "]" << std::endl;

    // Rest of your code...
    return 0;
}
