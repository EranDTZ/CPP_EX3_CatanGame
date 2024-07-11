#include <iostream>
#include "catan.hpp"
#include "player.hpp"
#include "board.hpp"

void commend_guide() {
    std::cout << "commend guide:" << std::endl;
    std::cout << "     insert -   " <<  "                            activate" <<std::endl;

    std::cout << "'use development' or 'use card' or 'use' - to activate the use of a Development card " << std::endl;
    std::cout << "'road' - to buy and place a Road on the board" << std::endl;
    std::cout << "'set' of 'sit' - to buy and place a Settelemnt on the board" << std::endl;
    std::cout << "'buy development' or 'buy card' or 'buy' - to buy a Development card " << std::endl;
    std::cout << "'bank' - to exchange 4 (same Resource card) for 1 " << std::endl;
    std::cout << "'points' - to see your points and where you stend " << std::endl;
    std::cout << "'knights' - to see how many Knights you activated " << std::endl;
    std::cout << "'cards' - to see your pack of Cards " << std::endl;
    std::cout << "'settelemnts' - to see the Settelemnts you own " << std::endl;
    std::cout << "'development' - to see your pack of Development Cards " << std::endl;
    std::cout << "'info' - to see ALL player important info " << std::endl;
    std::cout << "'trade' - to Trade a card of cards whit a chosen player " << std::endl;
    std::cout << "'borad' - to see a Board layout " << std::endl;
    std::cout << "'resource' - to see a Resource color guide " << std::endl;
    std::cout << "'guide' - to see a Settelemnts guide of Resource connected to Settelemnt i " << std::endl;
    std::cout << "'end' - to END your turn " << std::endl;
    std::cout << "'commend' - to see the commend guide\n " << std::endl;
}

int main() {
    std::string p1_name;
    std::string p2_name;
    std::string p3_name;
    std::cout << "Insert player 1 Name: " << std::endl;
    std::cin >> p1_name;
    std::cout << "Insert player 2 Name: " << std::endl;
    std::cin >> p2_name;
    std::cout << "Insert player 3 Name: " << std::endl;
    std::cin >> p3_name;

    Player p1(p1_name);
    Player p2(p2_name);
    Player p3(p3_name);

    Catan catan(p1, p2, p3);

    // Starting of the game. Every player places two settlements and two roads.
    std::string start = catan.ChooseStartingPlayer();
    Board& board = catan.getBoard();
    if (start == p1.getName()) {
        p1.placeSettelemnt(board);
        p1.endTurn();

        p2.placeSettelemnt(board);
        p2.endTurn();

        p3.placeSettelemnt(board);
        p3.endTurn();

        p1.setTurn();
        p1.placeSettelemnt(board);
        p1.endTurn();

        p2.setTurn();
        p2.placeSettelemnt(board);
        p2.endTurn();

        p3.setTurn();
        p3.placeSettelemnt(board);
        p3.endTurn();
    }
    else if (start == p2.getName()) {
        p2.placeSettelemnt(board);
        p2.endTurn();

        p3.placeSettelemnt(board);
        p3.endTurn();

        p1.placeSettelemnt(board);
        p1.endTurn();

        p2.setTurn();
        p2.placeSettelemnt(board);
        p2.endTurn();

        p3.setTurn();
        p3.placeSettelemnt(board);
        p3.endTurn();

        p1.setTurn();
        p1.placeSettelemnt(board);
        p1.endTurn();
    }
    else {
        p3.placeSettelemnt(board);
        p3.endTurn();

        p1.placeSettelemnt(board);
        p1.endTurn();

        p2.placeSettelemnt(board);
        p2.endTurn();

        p3.setTurn();
        p3.placeSettelemnt(board);
        p3.endTurn();

        p1.setTurn();
        p1.placeSettelemnt(board);
        p1.endTurn();

        p2.setTurn();
        p2.placeSettelemnt(board);
        p2.endTurn();
    }
    
    commend_guide();
    std::string cmd;
    while (catan.printWinner()) {
        for (auto& player : catan.getPlayers()) {
            player->setTurn();
            std::cout << player->getName() << " torn:" << std::endl;
            std::cout << player->getName() << " insret a commend: (use or roll)" << std::endl;
            std::cin >> cmd;

            if (cmd == "use development" || cmd == "use card" || cmd == "use") {
                player->useDevelopmentCard(catan,board);
            }

            player->rollDice(catan,board);
            
            while (cmd != "end") {
                if (cmd == "road")
                {
                    player->placeRoad(board);
                }
                if (cmd == "set")
                {
                    player->placeSettelemnt(board);
                }
                if (cmd == "buy development" || cmd == "buy card" || cmd == "buy")
                {
                    player->buyDevelopmentCard(catan);
                }
                if (cmd == "use development" || cmd == "use card" || cmd == "use")
                {
                    player->useDevelopmentCard(catan,board);
                }
                if (cmd == "bank")
                {
                    player->bankTrade();
                }
                if (cmd == "points")
                {
                    player->printPoints();
                }
                if (cmd == "knights")
                {
                    player->getKnights();
                }
                if (cmd == "cards")
                {
                    player->printCards();
                }
                if (cmd == "settlements")
                {
                    player->printSettlements();
                }
                if (cmd == "development")
                {
                    player->printDevelopment();
                }
                if (cmd == "info")
                {
                    player->myInfo();
                }
                if (cmd == "trade")
                {
                    std::string Other;
                    std::cout << "which player you want to trade with?" << std::endl;
                    std::cin >> Other;
                    for (auto& other : catan.getPlayers()) {
                        if (other->getName() == Other) {
                            player->trade(*other);
                        }
                    }
                }
                if (cmd == "borad")
                {
                    board.Guide();
                }
                if (cmd == "resource")
                {
                    board.ResourceGuide();
                }
                if (cmd == "guide")
                {
                    board.settlementGuide();
                }
                if (cmd == "commend")
                {
                    commend_guide();
                }
                std::cout << player->getName() << " insert the command to continue or 'end' to stop" << std::endl;
                std::cout << " if you don't remember the comments insert 'commend' " << std::endl;
                std::cin >> cmd;
            }        
        }
        
        
    }


    return 0;
}