#ifndef CATAN_HPP
#define CATAN_HPP

#include "board.hpp"
#include "player.hpp"
#include <vector>

class Catan {
public:

    Catan(Player& p1, Player& p2, Player& p3);
    void initializeDevelopmentCard();
    std::string ChooseStartingPlayer();
    Board& getBoard();
    bool printWinner();
    std::vector<Player*> getPlayers() const { return players; } 
    std::string getDevelopmentCard();
    bool Knight(std::string resource, int num, bool boo);
    std::vector<std::string> getDevelopmentCards() { return DevelopmentCard; }

private:
    Board board;
    std::vector<Player*> players;
    int currentPlayerIndex;
    std::vector<std::string> DevelopmentCard;
};

#endif // CATAN_HPP
