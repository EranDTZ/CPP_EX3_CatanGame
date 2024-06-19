#ifndef CATAN_HPP
#define CATAN_HPP

#include "board.hpp"
#include "player.hpp"
#include <vector>

class Catan {
public:

    Catan(Player& p1, Player& p2, Player& p3);
    void initializeDevelopmentCard();
    void ChooseStartingPlayer();
    Board& getBoard();
    void printWinner();
    std::vector<Player*> getPlayers() const { return players; } 
    std::string getDevelopmentCard();
    bool Knight(std::string resource, int num, std::string player, bool boo);

private:
    Board board;
    std::vector<Player*> players;
    int currentPlayerIndex;
    std::vector<std::string> DevelopmentCard;
};

#endif // CATAN_HPP
