#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "board.hpp"
#include <string>
#include <vector>

// Forward declaration of Catan class
class Catan;

class Player {
    public:
        Player(const std::string& name);
        std::string getName() const;
        void setTurn(bool turn) { isTurn = turn; }
        void rollDice(Catan& catan);
        void endTurn();
        void trade(Player& other);
        bool isTrade(Player& other);
        void buyDevelopmentCard(Catan& catan);
        void useDevelopmentCard(Catan& catan ,Board& board);
        void bankTrade();
        void printPoints() const;
        int getPoints() const;
        bool buySettelemnt();
        bool buyRoad();
        void placeSettelemnt(Board& board);
        void placeRoad(Board& board, int settlementId);
        void placeRoad(Board& board);
        void placeTowRoads(Board& board);
        std::vector<Settlement> PlayerSettlements() const {return playerSettlements;}
        std::vector<std::string> Cards() {return cards;}
        std::vector<std::string> getDevelopment() {return developmentCard;}
    private:
        std::string name;
        int points;
        bool isTurn;
        std::vector<std::string> cards;
        std::vector<std::string> developmentCard;
        std::vector<Settlement> playerSettlements;
        std::vector<Edge> playerEdges;
    };

#endif
