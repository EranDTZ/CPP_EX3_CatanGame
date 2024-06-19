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
        bool isTurn() { return isturn; }
        void setTurn();
        void rollDice(Catan& catan, Board& board);
        void endTurn();
        void trade(Player& other);
        bool isTrade(Player& other);
        void buyDevelopmentCard(Catan& catan);
        void useDevelopmentCard(Catan& catan ,Board& board);
        void bankTrade();
        void printPoints() const;
        int getPoints() const;
        void setPoints(int more) { points += more; }
        int getKnights() const;
        bool getKnightKing() { return knightsKing; }
        void setKnightKing(bool boo) { knightsKing = boo; }
        void knightsCheck(Catan& catan);
        bool buySettelemnt();
        bool buyRoad();
        void placeSettelemnt(Board& board);
        void placeRoad(Board& board, int settlementId);
        void placeRoad(Board& board);
        void placeTowRoads(Board& board);
        void printCards();
        void printSettlements();
        void printDevelopment();
        void myInfo();
        std::vector<Settlement> PlayerSettlements() const {return playerSettlements;}
        std::vector<std::string> Cards() {return cards;}
        std::vector<std::string> getDevelopment() {return developmentCard;}
    private:
        std::string name;
        int points;
        bool isturn;
        int knights;
        bool knightsKing;
        std::vector<std::string> cards;
        std::vector<std::string> developmentCard;
        std::vector<Settlement> playerSettlements;
        // std::vector<Edge> playerEdges;
    };

#endif
