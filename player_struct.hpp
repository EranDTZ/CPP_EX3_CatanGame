#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "board.hpp"
#include <string>
#include <vector>

class Player {
    public:
        Player(const std::string& name);
        std::string getName() const;
        void rollDice();
        void endTurn();
        void trade(Player& other, const std::string& give, const std::string& receive, int giveAmount, int receiveAmount);
        void buyDevelopmentCard();
        void printPoints() const;
        int getPoints() const;
        bool buySettelemntCard();
        bool buyRoadCard();
        void placeSettelemnt(Board& board);
        void placeRoad(Board& board, int settlementId);
        void placeRoad(Board& board);
    private:
        std::string name;
        int points;
        bool isTurn;
        std::vector<std::string> cards;
        std::vector<Settlement> playerSettlements;
        std::vector<Edge> playerEdges;
    };

#endif
