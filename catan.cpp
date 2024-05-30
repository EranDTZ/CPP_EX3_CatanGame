#include "catan.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

Catan::Catan(Player& p1, Player& p2, Player& p3) : board() {
    players.push_back(&p1);
    players.push_back(&p2);
    players.push_back(&p3);
    std::srand(std::time(0));
    currentPlayerIndex = std::rand() % 3;
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
