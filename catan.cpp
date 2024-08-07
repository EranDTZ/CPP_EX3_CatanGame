#include "catan.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

Catan::Catan(Player& p1, Player& p2, Player& p3) : board() {
    players.push_back(&p1);
    players.push_back(&p2);
    players.push_back(&p3);
    initializeDevelopmentCard();
    std::srand(std::time(0));
    currentPlayerIndex = std::rand() % 3;
}

void Catan::initializeDevelopmentCard() {

    std::vector<std::string> development = {"Knight", "Knight", "Knight","Knight", "Knight", "Knight","Knight","Knight", "Knight", "Knight",
                                            "Knight", "Knight", "Knight","Knight", "Knight", "Knight","Knight", // 17 knights
                                            "Point", "Point", "Point","Point", "Point", "Point", // 6 winning Points
                                            "Monopoly", "Monopoly", "Monopoly", "Monopoly", // Four Monopoly
                                            "Resources", "Resources", "Resources", "Resources", // Four Resources
                                            "Roads", "Roads", "Roads", "Roads", // Four Roads
                                            };

    std::random_shuffle(development.begin(), development.end());

    DevelopmentCard.clear();
    for (const auto& card : development) {
        DevelopmentCard.push_back(card);
    }
}

std::string Catan::ChooseStartingPlayer() {
    std::cout << "Starting player: " << players[currentPlayerIndex]->getName() << std::endl;
    return players[currentPlayerIndex]->getName();
}

Board& Catan::getBoard() {
    return board;
}

bool Catan::printWinner() {
    Player* winner = nullptr;
    for (auto player : players) {
        if (player->getPoints() >= 10) {
            if (!winner || player->getPoints() > winner->getPoints()) {
                winner = player;
                break;
            }
        }
    }
    if (winner) {
        std::cout << "Winner: " << winner->getName() << std::endl;
        return false;
    } else {
        std::cout << "No winner yet." << std::endl;
    }
    return true;
}

std::string Catan::getDevelopmentCard() {
    std::string card;
    if (!DevelopmentCard.empty()) {
        // Get the first card
        card = DevelopmentCard.front();
        // Remove the first card
        DevelopmentCard.erase(DevelopmentCard.begin());
    } 
    else {
        std::cout << "The pack is empty." << std::endl;
    }
    return card;
}


bool Catan::Knight(std::string resource, int num, bool boo) {
    if (boo)
    {
        std::cout << "resource number: " << std::endl;
        std::cin >> num;
        std::cout << "resource: " << std::endl;
        std::cin >> resource;
    }
    
    std::vector<std::string> resourceTypes = {"Forest", "Hills", "Pasture", "Fields", "Mountains"};
    auto iter = std::find(resourceTypes.begin(), resourceTypes.end(), resource);
    if (iter == resourceTypes.end()) {
        std::cout << "resource doesn't exsist: bad syntx, try again" << std::endl;
        boo = true;
        Knight(resource,num,boo);
    }

    if (num < 2 || num > 12) {
        std::cout << "resource number doesn't exsist: bad syntx, try again" << std::endl;
        boo = true;
        Knight(resource,num,boo);
    }

    int chang = -1;
    //Set Knighted Hexes int BACK to positive number to cancel the Knight on them.
    for (auto& settlement : board.getSettlements()) {
        if (settlement.Hex1().second < 0)
        {
            settlement.setHex1Int(settlement.Hex1().second * chang);
        }
        if (settlement.Hex2().second < 0)
        {
            settlement.setHex2Int(settlement.Hex1().second * chang);
        }
        if (settlement.Hex3().first != "NULL" && settlement.Hex3().second < 0)
        {
            settlement.setHex3Int(settlement.Hex1().second * chang);
        }
    }

    //Set Hexes int into to negative number to put the Knight on them.
    for (auto& settlement : board.getSettlements()) {
        if (settlement.Hex1().first == resource && settlement.Hex1().second == num)
        {
            settlement.setHex1Int(settlement.Hex1().second * chang);
        }
        if (settlement.Hex2().first == resource && settlement.Hex2().second == num)
        {
            settlement.setHex2Int(settlement.Hex1().second * chang);
        }
        if (settlement.Hex3().first != "NULL" && settlement.Hex3().first == resource && settlement.Hex3().second == num)
        {
            settlement.setHex3Int(settlement.Hex1().second * chang);
        }
    }
    return true;
}

