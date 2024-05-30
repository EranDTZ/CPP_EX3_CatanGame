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

    Settlement(const std::pair<std::string, int>& h1, const std::pair<std::string, int>& h2,
               const std::pair<std::string, int>& h3)
        : hex1(h1), hex2(h2), hex3(h3), occupied(false) {}

    Settlement(const std::pair<std::string, int>& h1, const std::pair<std::string, int>& h2)
        : hex1(h1), hex2(h2), hex3({"NULL", 0}), occupied(false) {}
};

class Board {
public:
    Board();
    void initializeBoard();
    void printBoard();
    bool isPlaceAvailable(const std::vector<std::string>& places, const std::vector<int>& placesNum) const;
    void occupyPlace(const std::vector<std::string>& places, const std::vector<int>& placesNum);
private:
    std::vector<std::pair<std::string, int>> hexes;
    std::vector<Settlement> settlements;
};

#endif // BOARD_HPP
