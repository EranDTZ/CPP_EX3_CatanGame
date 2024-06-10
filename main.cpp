#include <iostream>
#include "catan.hpp"
#include "player.hpp"
#include "board.hpp"

int main() {
    Player p1("Amit");
    Player p2("Yossi");
    Player p3("Dana");
    Catan catan(p1, p2, p3);

    // Starting of the game. Every player places two settlements and two roads.
    catan.ChooseStartingPlayer();
    Board& board = catan.getBoard();

    board.printBoard();
    board.BoardGuide();
    board.ResourceGuide();
    return 0;
}