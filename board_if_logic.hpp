#ifndef BOARD_IF_LOGIC_HPP
#define BOARD_IF_LOGIC_HPP

#include <vector>
#include <map>
#include <string>
#include <utility>
#include <iostream>

struct Settlement {
    std::pair<std::string, int> hex1;
    std::pair<std::string, int> hex2;
    std::pair<std::string, int> hex3;
    bool occupied;
    int playerId;

    Settlement(const std::pair<std::string, int>& h1, const std::pair<std::string, int>& h2,
               const std::pair<std::string, int>& h3)
        : hex1(h1), hex2(h2), hex3(h3), occupied(false), playerId(-1) {}

    Settlement(const std::pair<std::string, int>& h1, const std::pair<std::string, int>& h2)
        : hex1(h1), hex2(h2), hex3({"NULL", 0}), occupied(false), playerId(-1) {}
};


struct Edge {
    Settlement* settlement1;
    Settlement* settlement2;
    int roads; // Number of roads on this edge
    int playerId; // מי הבעלים של הכביש האחרון

    Edge(Settlement* s1, Settlement* s2) : settlement1(s1), settlement2(s2), roads(0), playerId(-1) {}
};

class Board {
public:
    Board();
    void initializeBoard();
    void initializeEdges();
    void printBoard();
    bool isPlaceAvailable(const std::vector<std::string>& places, const std::vector<int>& placesNum) const;
    void occupyPlace(const std::vector<std::string>& places, const std::vector<int>& placesNum);
private:
    std::vector<std::pair<std::string, int>> hexes;
    std::vector<Settlement> settlements;
    std::vector<Edge> edges;
};

#endif // BOARD_HPP
