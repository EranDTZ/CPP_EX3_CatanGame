#ifndef CATAN_HPP
#define CATAN_HPP

#include "board.hpp"
#include "player.hpp"
#include <vector>

class Catan {
public:
    Catan(Player& p1, Player& p2, Player& p3);
    void ChooseStartingPlayer();
    Board& getBoard();
    void printWinner();

private:
    Board board;
    std::vector<Player*> players;
    int currentPlayerIndex;
};

#endif // CATAN_HPP
