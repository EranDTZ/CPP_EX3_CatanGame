#include "board.hpp"
#include <algorithm>

Board::Board() {
    initializeBoard();
}

void Board::initializeBoard() {
    // List of resource types and their associated numbers
    std::vector<std::string> resourceTypes = {"Forest", "Forest", "Forest", "Forest", // Four Forests
                                               "Hills", "Hills", "Hills", // Three Hills
                                               "Pasture Land", "Pasture Land", "Pasture Land", "Pasture Land", // Four Pasture Lands
                                               "Agricultural Land", "Agricultural Land", "Agricultural Land", "Agricultural Land", // Four Agricultural Lands
                                               "Mountains", "Mountains", "Mountains", // Three Mountains
                                               "Desert"}; // One Desert

    
    std::random_shuffle(resourceTypes.begin(), resourceTypes.end());
    

    std::vector<int> resourceNumbers = {2, 3, 4, 5, 6, 8, 9, 10, 11, 12, 3, 4, 5, 6, 8, 9, 10, 11};

    // Initialize hexes with shuffled resources and numbers
    hexes.clear();
    for (const auto& type : resourceTypes) {
        if (type == "Desert") {
            hexes.emplace_back(type, 0);  // Desert has no number
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
    std::cout << "Board Layout:" << std::endl;
    std::cout << "     " << hexes[0].second << "----" << hexes[1].second << "----" << hexes[2].second << std::endl;
    std::cout << "    / \\    / \\    / \\" << std::endl;
    std::cout << "   /   \\  /   \\  /   \\" << std::endl;
    std::cout << "  " << hexes[3].second << "---" << hexes[4].second << "----" << hexes[5].second << "----" << hexes[6].second << std::endl;
    std::cout << " / \\   / \\   / \\   / \\" << std::endl;
    std::cout << hexes[7].second << "--" << hexes[8].second << "--" << hexes[9].second << "--" << hexes[10].second << "--" << hexes[11].second << std::endl;
    std::cout << " \\ /   \\ /   \\ /   \\ /" << std::endl;
    std::cout << "  " << hexes[12].second << "--" << hexes[13].second << "----" << hexes[14].second << "--" << hexes[15].second << std::endl;
    std::cout << "   \\   / \\   / \\   /" << std::endl;
    std::cout << "     " << hexes[16].second << "--" << (hexes[17].second == 0 ? "Desert" : std::to_string(hexes[17].second)) << std::endl;
}



// bool Board::isPlaceAvailable(const std::vector<std::string>& places, const std::vector<int>& placesNum) const {
//     for (size_t i = 0; i < places.size(); ++i) {
//         auto it = settlements.find({places[i], placesNum[i]});
//         if (it != settlements.end() && it->second) {
//             return false; // If any place is already occupied, return false
//         }
//     }
//     return true;
// }
