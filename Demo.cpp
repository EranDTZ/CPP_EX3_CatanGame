/**
 * Demo file for Ex3.
 *
 */
#include <iostream>
#include <stdexcept>
#include <vector>
#include "catan.hpp"
#include "player.hpp"
#include "board.hpp"
using namespace std;

int main()
{
    Player p1("Amit");
    Player p2("Yossi");
    Player p3("Dana");
    Catan catan(p1, p2, p3);
    // Starting of the game. Every player places two settlements and two roads.
    catan.ChooseStartingPlayer();   // should print the name of the starting player, assume it is Amit.
    Board board = catan.getBoard(); // get the board of the game.

    //players placing first settlements
    p1.placeSettelemnt(board);

    p2.placeSettelemnt(board);

    p3.placeSettelemnt(board);

    p1.placeSettelemnt(board);

    p2.placeSettelemnt(board);

    p3.placeSettelemnt(board);

    for (size_t i = 0; i < 3; i++)
    {
        p1.setTurn();
        p1.rollDice(catan,board);                         
        p1.endTurn(); // p1 ends his turn.

        p2.setTurn();
        p2.rollDice(catan,board); 
        p2.endTurn();  // p2 ends his turn.

        p3.setTurn();
        p3.rollDice(catan,board); 
        p3.endTurn();  // p3 ends his turn.
    }

    try
    {
        p2.rollDice(catan,board); // p2 tries to roll the dice again, but it's not his turn.
    }
    catch (const std::exception &e)
    {
        cout << e.what() << endl;
    }

    p1.setTurn();
    p1.placeRoad(board); // p1 trying to build a road.

    p1.rollDice(catan,board);
    p1.trade(p2); // p1 trades 1 wood for 1 brick with p2.
    p1.endTurn(); // p1 ends his turn.

    p2.setTurn();
    p2.rollDice(catan,board); 
    p2.buyDevelopmentCard(catan); // p2 tring to buy a development card.
    p2.endTurn(); // p2 ends his turn.

    p1.printPoints(); 
    p2.printPoints(); 
    p3.printPoints(); 

    catan.printWinner(); // Should print None because no player reached 10 points.
}