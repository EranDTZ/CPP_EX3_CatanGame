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

void Catan::ChooseStartingPlayer() {
    std::cout << "Starting player: " << players[currentPlayerIndex]->getName() << std::endl;
}

Board& Catan::getBoard() {
    return board;
}

void Catan::printWinner() {
    Player* winner = nullptr;
    for (auto player : players) {
        if (player->getPoints() >= 10) {
            if (!winner || player->getPoints() > winner->getPoints()) {
                winner = player;
            }
        }
    }
    if (winner) {
        std::cout << "Winner: " << winner->getName() << std::endl;
    } else {
        std::cout << "No winner yet." << std::endl;
    }
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
