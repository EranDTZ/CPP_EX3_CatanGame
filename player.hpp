#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "board.hpp"
#include <string>
#include <vector>

class Player {
    public:
        Player(const std::string& name);
        std::string getName() const;
        void placeSettelemnt(const std::vector<std::string>& places, const std::vector<int>& placesNum, Board& board);
        void placeFirstSettelemnt(const std::vector<std::string>& places, const std::vector<int>& placesNum, Board& board);
        void placeFirstRoad(const std::vector<std::string>& places, const std::vector<int>& placesNum, Board& board);
        void rollDice();
        void endTurn();
        void trade(Player& other, const std::string& give, const std::string& receive, int giveAmount, int receiveAmount);
        void buyDevelopmentCard();
        void printPoints() const;
        int getPoints() const;
        bool buySettelemntCard();
        bool buyRoadCard();
        void placeSettelemnt(Board& board);
    private:
        std::string name;
        int points;
        bool isTurn;
        std::vector<std::string> cards;
    };

#endif
