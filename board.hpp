#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include <map>
#include <string>
#include <utility>
#include <iostream>

struct Settlement {
    std::pair<std::string, int> hex1;
    std::pair<std::string, int> hex2;
    std::pair<std::string, int> hex3;
    int settlementId;
    bool occupied;
    std::string playerId; // Who owns the settlement

    void setOccupied(bool occupied) const {
        occupied = occupied;
    }

    void setPlayerId(std::string& playerId) const {
        playerId = playerId;
    }
    
    Settlement(const std::pair<std::string, int>& h1, const std::pair<std::string, int>& h2,
               const std::pair<std::string, int>& h3, const int settlementId)
        : hex1(h1), hex2(h2), hex3(h3), settlementId(settlementId), occupied(false), playerId("NULL") {}

    Settlement(const std::pair<std::string, int>& h1, const std::pair<std::string, int>& h2, const int settlementId)
        : hex1(h1), hex2(h2), hex3({"NULL", 0}), settlementId(settlementId), occupied(false), playerId("NULL") {}
};


struct Edge {
    Settlement* settlement1;
    Settlement* settlement2;
    int roads; // Number of roads on this edge
    int playerId; // Who owns the last road
    Edge(Settlement* s1, Settlement* s2) : settlement1(s1), settlement2(s2), roads(0), playerId(-1) {}
};

class Board {
public:
    Board();
    void initializeBoard();
    void initializeEdges();
    void printBoard();
    void ResourceGuide();
    void BoardGuide();
    bool is3PlaceAvailable(const std::pair<std::string, int> hex1, const std::pair<std::string, int> hex2, const std::pair<std::string, int> hex3, std::string& playerId) const;
    bool is2PlaceAvailable(const std::pair<std::string, int> hex1, const std::pair<std::string, int> hex2, std::string& playerId) const;
    void occupyPlace(const std::vector<std::string>& places, const std::vector<int>& placesNum);
private:
    std::vector<std::pair<std::string, int>> hexes;
    std::vector<Settlement> settlements;
    std::vector<Edge> edges;
};

#endif // BOARD_HPP
