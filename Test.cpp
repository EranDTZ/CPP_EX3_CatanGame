#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "catan.hpp"
#include "player.hpp"
#include "board.hpp"


#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "catan.hpp"
#include "player.hpp"
#include "board.hpp"

TEST_CASE("Testing Board initialization") {
    Board board;
    // Add tests related to board initialization
}

TEST_CASE("Testing Player actions") {
    Player p1("Amit");
    Player p2("Yossi");
    Player p3("Dana");
    // Add tests related to player actions
}
// using namespace ariel;

// TEST_CASE("Player functionality") {
//     Player p("TestPlayer");
//     CHECK(p.getName() == "TestPlayer");
//     CHECK(p.getPoints() == 0);

//     Board board;
//     p.placeSettelemnt({"Forest", "Hills"}, {5, 6}, board);
//     p.placeRoad({"Forest", "Hills"}, {5, 6}, board);
//     CHECK(p.getPoints() == 1); // 1 point for settlement
// }

// TEST_CASE("Catan game functionality") {
//     Player p1("Amit");
//     Player p2("Yossi");
//     Player p3("Dana");
//     Catan catan(p1, p2, p3);

//     catan.ChooseStartingPlayer();
//     Board board = catan.getBoard();
    
//     std::vector<std::string> places = {"Forest", "Hills"};
//     std::vector<int> placesNum = {5, 6};
//     p1.placeSettelemnt(places, placesNum, board);
//     p1.placeRoad(places, placesNum, board);
    
//     places = {"Agricultural Land", "Desert"};
//     placesNum = {3, 4};
//     p1.placeSettelemnt(places, placesNum, board);
//     p1.placeRoad(places, placesNum, board);
    
//     places = {"Mountains", "Pasture Land"};
//     placesNum = {4, 9};
//     p2.placeSettelemnt(places, placesNum, board);
//     p2.placeRoad(places, placesNum, board);
    
//     try {
//         p3.placeSettelemnt(places, placesNum, board); // p3 tries to place a settlement in the same location as p2.
//     } catch (const std::exception &e) {
//         CHECK(std::string(e.what()) == "Settlement already exists in this location.");
//     }

//     places = {"Forest", "Pasture Land"};
//     placesNum = {5, 9};
//     p2.placeSettelemnt(places, placesNum, board);
//     p2.placeRoad(places, placesNum, board);
    
//     places = {"Mountains", "Pasture Land"};
//     placesNum = {3, 8};
//     p3.placeSettelemnt(places, placesNum, board);
//     p3.placeRoad(places, placesNum, board);

//     p1.rollDice();
//     p1.placeRoad({"Forest", "Hills"}, {5, 6}, board);
//     p1.endTurn();

//     p2.rollDice();
//     p2.endTurn();

//     p3.rollDice();
//     p3.endTurn();

//     try {
//         p2.rollDice(); // p2 tries to roll the dice again, but it's not his turn.
//     } catch (const std::exception &e) {
//         CHECK(std::string(e.what()) == "Yossi tried to roll the dice but it's not their turn.");
//     }

//     p1.rollDice();
//     p1.trade(p2, "wood", "brick", 1, 1);
//     p1.endTurn();

//     p2.rollDice();
//     p2.buyDevelopmentCard();
//     p2.endTurn();

//     CHECK(p1.getPoints() == 2); // 2 points for settlements
//     CHECK(p2.getPoints() == 3); // 2 points for settlements + 1 point for development card
//     CHECK(p3.getPoints() == 2); // 2 points for settlements
// }
