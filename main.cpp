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

    // board.printBoard();
    // board.BoardGuide();
    // board.ResourceGuide();
    // board.printSometing();

    p1.placeSettelemnt(board);
    p1.endTurn();
    p2.placeSettelemnt(board);
    p2.endTurn();
    p3.placeSettelemnt(board);
    p3.endTurn();

    // p1.placeSettelemnt(board);
    // p1.endTurn();
    // p2.placeSettelemnt(board);
    // p2.endTurn();
    // p3.placeSettelemnt(board);
    // p3.endTurn();
    
    return 0;
}