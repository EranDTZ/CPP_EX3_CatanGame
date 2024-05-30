#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include <map>
#include <string>
#include <utility>
#include <iostream>

class Board {
public:
    Board();
    void initializeBoard();
    void printBoard();
    bool isPlaceAvailable(const std::vector<std::string>& places, const std::vector<int>& placesNum) const;
    std::map<std::pair<std::string, int>, bool> settlements;
private:
    std::vector<std::pair<std::string, int>> hexes;
};

#endif // BOARD_HPP
