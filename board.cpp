#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <random>
#include "board.hpp"

Board::Board() {
    initializeBoard();
}
/*maybe it should be realized using a graph , 
So every Node is a meeting of - 3 resourceTypes OR 2 resourceTypes and NULL,
And every Edge is a meeting of - 2 of the resourceTypes OR 1 of the resourceTypes and NULL,
Evrey player have a color that affects fact that settlement and the road color,
And if Node v contains a settlement an Edge(v,u) can contain 2 Roads of the settlement color ,
If an Edge(v,u) containa 2 Roads of the same color of the player, he can set a settlement in Node u.
*/
void Board::initializeBoard() {
    // List of resource types and their associated numbers
    std::vector<std::string> resourceTypes = {"Forest", "Forest", "Forest", "Forest", // Four Forests
                                               "Hills", "Hills", "Hills", // Three Hills
                                               "Pasture", "Pasture", "Pasture", "Pasture", // Four Pasture Lands
                                               "Fields", "Fields", "Fields", "Fields", // Four Agricultural Lands
                                               "Mountains", "Mountains", "Mountains", // Three Mountains
                                               "Desert"}; // One Desert

    
    std::random_shuffle(resourceTypes.begin(), resourceTypes.end());
    // Shuffle the resource types randomly
    // std::random_device rd;
    // std::mt19937 g(rd());
    // std::shuffle(resourceTypes.begin(), resourceTypes.end(), g);


    std::vector<int> resourceNumbers = {2, 3, 4, 5, 6, 8, 9, 10, 11, 12, 3, 4, 5, 6, 8, 9, 10, 11};

    // Initialize hexes with shuffled resources and numbers
    hexes.clear();
    for (const auto& type : resourceTypes) {
        if (type == "Desert") {
            hexes.emplace_back(type, 7);  // Desert has no number
            resourceNumbers.pop_back();
        } else {
            hexes.emplace_back(type, resourceNumbers.back());
            resourceNumbers.pop_back();
        }
    }

    // Map hexes to the board with initial availability
    for (const auto& hex : hexes) {
        settlements[hex] = false;
    }
}

void Board::printBoard() {
    // Map resource types to ANSI color codes
    // std::map<std::string, std::string> colorMap = {
    //     {"Forest", "\033[0;32m●\033[0m"},        // Green dot
    //     {"Hills", "\033[38;5;208m●\033[0m"}, // Orange dot
    //     {"Pasture", "\033[37m●\033[0m"},  // White dot
    //     {"Fields", "\033[33m●\033[0m"},         // Brown dot (Yellow)
    //     {"Mountains", "\033[90m●\033[0m"},     // Gray dot
    //     {"Desert", "\033[31m●\033[0m"},        // red dot
    //     {"default", "\033[0m●\033[0m"}         // Default dot
    // };

    // Map resource types to ANSI color codes
    std::map<std::string, std::string> colorMap = {
        {"Forest", "\033[0;32m⬢\033[0m"},        // Green hexagon
        {"Hills", "\033[38;5;208m⬢\033[0m"}, // Orange hexagon
        {"Pasture", "\033[37m⬢\033[0m"},  // White hexagon
        {"Fields", "\033[33m⬢\033[0m"},         // Yellow hexagon
        {"Mountains", "\033[90m⬢\033[0m"},     // Gray hexagon
        {"Desert", "\033[31m⬢\033[0m"},        // Red hexagon
        {"default", "\033[0m⬢\033[0m"}         // Default hexagon
    };

    // Create a vector of pairs to store resource type and number
    std::vector<std::pair<std::string, int>> hexes;
    for (const auto& settlement : settlements) {
        hexes.push_back(settlement.first);
    }

    // Print the board with colored dots
    std::cout << "Board Layout:" << std::endl;
    std::cout << "     " << colorMap[hexes[0].first] << hexes[0].second
              << "----" << colorMap[hexes[1].first] << hexes[1].second
              << "----" << colorMap[hexes[2].first] << hexes[2].second << std::endl;
    std::cout << "     / \\   / \\   / \\" << std::endl;
    std::cout << "    /   \\ /   \\ /   \\" << std::endl;
    std::cout << "  " << colorMap[hexes[3].first] << hexes[3].second
              << "----" << colorMap[hexes[4].first] << hexes[4].second
              << "----" << colorMap[hexes[5].first] << hexes[5].second
              << "----" << colorMap[hexes[6].first] << hexes[6].second << std::endl;
    std::cout << "  / \\   / \\   / \\   / \\" << std::endl;
    std::cout << " /   \\ /   \\ /   \\ /   \\" << std::endl;
    std::cout << colorMap[hexes[7].first] << hexes[7].second
              << "---" << colorMap[hexes[8].first] << hexes[8].second
              << "----" << colorMap[hexes[9].first] << hexes[9].second
              << "----" << colorMap[hexes[10].first] << hexes[10].second
              << "----" << colorMap[hexes[11].first] << hexes[11].second << std::endl;
    std::cout << " \\   / \\   / \\   / \\   /" << std::endl;
    std::cout << "  \\ /   \\ /   \\ /   \\ /" << std::endl;
    std::cout << "  " << colorMap[hexes[12].first] << hexes[12].second
              << "----" << colorMap[hexes[13].first] << hexes[13].second
              << "----" << colorMap[hexes[14].first] << hexes[14].second
              << "----" << colorMap[hexes[15].first] << hexes[15].second << std::endl;
    std::cout << "   \\    / \\   / \\   /" << std::endl;
    std::cout << "    \\  /   \\ /   \\ /" << std::endl;
    std::cout << "     " << colorMap[hexes[16].first] << hexes[16].second
              << "----" << colorMap[hexes[17].first] << hexes[17].second
              << "----" << colorMap[hexes[18].first] << hexes[18].second << std::endl;
}


bool Board::isPlaceAvailable(const std::vector<std::string>& places, const std::vector<int>& placesNum) const {
    for (size_t i = 0; i < places.size(); ++i) {
        auto it = settlements.find({places[i], placesNum[i]});
        if (it != settlements.end() && it->second) {
            return false; // If any place is already occupied, return false
        }
    }
    return true;
}
