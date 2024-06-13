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
        } else {
            hexes.emplace_back(type, resourceNumbers.back());
            resourceNumbers.pop_back();
        }
    }

    settlements.clear();
    // Initialize settlements (example layout)
    settlements.push_back(Settlement(hexes[0], hexes[1],1));
    settlements.push_back(Settlement(hexes[1], hexes[2],2));

    settlements.push_back(Settlement(hexes[0], hexes[3],3));

    settlements.push_back(Settlement(hexes[0], hexes[1], hexes[4],4));
    settlements.push_back(Settlement(hexes[1], hexes[2], hexes[5],5));

    settlements.push_back(Settlement(hexes[2], hexes[6],6));


    settlements.push_back(Settlement(hexes[0], hexes[3], hexes[4],7));
    settlements.push_back(Settlement(hexes[1], hexes[4], hexes[5],8));
    settlements.push_back(Settlement(hexes[2], hexes[5], hexes[6],9));

    settlements.push_back(Settlement(hexes[3], hexes[7],10));


    settlements.push_back(Settlement(hexes[3], hexes[4], hexes[8],11));
    settlements.push_back(Settlement(hexes[4], hexes[5], hexes[9],12));
    settlements.push_back(Settlement(hexes[5], hexes[6], hexes[10],13));

    settlements.push_back(Settlement(hexes[6], hexes[11],14));

    settlements.push_back(Settlement(hexes[3], hexes[7], hexes[8],15));
    settlements.push_back(Settlement(hexes[4], hexes[8], hexes[9],16));
    settlements.push_back(Settlement(hexes[5], hexes[9], hexes[10],17));
    settlements.push_back(Settlement(hexes[6], hexes[10], hexes[11],18));


    // settlements.push_back(Settlement(hexes[7], hexes[12],18));

    settlements.push_back(Settlement(hexes[7], hexes[8],hexes[12],19));
    settlements.push_back(Settlement(hexes[8], hexes[9], hexes[13],20));
    settlements.push_back(Settlement(hexes[9], hexes[10], hexes[14],21));
    settlements.push_back(Settlement(hexes[10], hexes[11],hexes[15],22));

    settlements.push_back(Settlement(hexes[7], hexes[12],23));

    settlements.push_back(Settlement(hexes[12], hexes[13], hexes[8],24));
    settlements.push_back(Settlement(hexes[13], hexes[14], hexes[9],25));
    settlements.push_back(Settlement(hexes[14], hexes[15], hexes[10],26));

    settlements.push_back(Settlement(hexes[11], hexes[15],27));
    
    settlements.push_back(Settlement(hexes[16],hexes[12], hexes[13],28));
    settlements.push_back(Settlement(hexes[17], hexes[13], hexes[14],29));
    settlements.push_back(Settlement(hexes[18], hexes[14], hexes[15],30));

    settlements.push_back(Settlement(hexes[12], hexes[16],31));

    settlements.push_back(Settlement(hexes[16],hexes[17], hexes[13],32));
    settlements.push_back(Settlement(hexes[17], hexes[18], hexes[14],33));

    settlements.push_back(Settlement(hexes[15], hexes[18],34));

    settlements.push_back(Settlement(hexes[16], hexes[17],35));
    settlements.push_back(Settlement(hexes[17], hexes[18],36));

}

void Board::initializeEdges() {
    edges.clear();

    for (size_t i = 0; i < settlements.size(); ++i) {
        for (size_t j = i + 1; j < settlements.size(); ++j) {
            // Check if settlements share exactly one hex and are adjacent
            int sharedHexes = 0;
            
            if (settlements[i].hex1 == settlements[j].hex1 || settlements[i].hex1 == settlements[j].hex2 || settlements[i].hex1 == settlements[j].hex3) {
                sharedHexes++;
            }
            if (settlements[i].hex2 == settlements[j].hex1 || settlements[i].hex2 == settlements[j].hex2 || settlements[i].hex2 == settlements[j].hex3) {
                sharedHexes++;
            }
            if (settlements[i].hex3 == settlements[j].hex1 || settlements[i].hex3 == settlements[j].hex2 || settlements[i].hex3 == settlements[j].hex3) {
                sharedHexes++;
            }

            // If exactly one shared hex, create an edge
            if (sharedHexes == 1) {
                edges.emplace_back(&settlements[i], &settlements[j]);
            }
        }
    }
}

void Board::printBoard() {
    // Map resource types to ANSI color codes
    std::map<std::string, std::string> colorMap = {
        {"Forest", "\033[0;32m⬢ \033[0m"},        // Green hexagon
        {"Hills", "\033[38;5;208m⬢ \033[0m"}, // Orange hexagon
        {"Pasture", "\033[37m⬢ \033[0m"},  // White hexagon
        {"Fields", "\033[33m⬢ \033[0m"},         // Yellow hexagon
        {"Mountains", "\033[90m⬢ \033[0m"},     // Gray hexagon
        {"Desert", "\033[31m⬢ \033[0m"},        // Red hexagon
        {"default", "\033[0m⬢ \033[0m"}         // Default hexagon
    };

    // Print the board with colored dots
    std::cout << "Board Layout:" << std::endl;
    std::cout << "       " << colorMap[hexes[0].first] << hexes[0].second
              << "---" << colorMap[hexes[1].first] << hexes[1].second
              << "---" << colorMap[hexes[2].first] << hexes[2].second << std::endl;
    std::cout << "       / \\   / \\   / \\" << std::endl;
    std::cout << "      /   \\ /   \\ /   \\" << std::endl;
    std::cout << "    " << colorMap[hexes[3].first] << hexes[3].second
              << "---" << colorMap[hexes[4].first] << hexes[4].second
              << "---" << colorMap[hexes[5].first] << hexes[5].second
              << "---" << colorMap[hexes[6].first] << hexes[6].second << std::endl;
    std::cout << "    / \\   / \\   / \\   / \\" << std::endl;
    std::cout << "   /   \\ /   \\ /   \\ /   \\" << std::endl;
    std::cout << colorMap[hexes[7].first] << hexes[7].second
              << "---" << colorMap[hexes[8].first] << hexes[8].second
              << "---" << colorMap[hexes[9].first] << hexes[9].second
              << "---" << colorMap[hexes[10].first] << hexes[10].second
              << "---" << colorMap[hexes[11].first] << hexes[11].second << std::endl;
    std::cout << "   \\   / \\   / \\   / \\   /" << std::endl;
    std::cout << "    \\ /   \\ /   \\ /   \\ /" << std::endl;
    std::cout << "    " << colorMap[hexes[12].first] << hexes[12].second
              << "---" << colorMap[hexes[13].first] << hexes[13].second
              << "---" << colorMap[hexes[14].first] << hexes[14].second
              << "---" << colorMap[hexes[15].first] << hexes[15].second << std::endl;
    std::cout << "     \\    / \\   / \\   /" << std::endl;
    std::cout << "      \\  /   \\ /   \\ /" << std::endl;
    std::cout << "       " << colorMap[hexes[16].first] << hexes[16].second
              << "---" << colorMap[hexes[17].first] << hexes[17].second
              << "---" << colorMap[hexes[18].first] << hexes[18].second << std::endl;
}

void Board::ResourceGuide() {
    // Map resource types to ANSI color codes
    std::map<std::string, std::string> colorTypeMap = {
        {"Forest", "\033[0;32m●\033[0m"},        // Green dot
        {"Hills", "\033[38;5;208m●\033[0m"}, // Orange dot
        {"Pasture", "\033[37m●\033[0m"},  // White dot
        {"Fields", "\033[33m●\033[0m"},         // Brown dot (Yellow)
        {"Mountains", "\033[90m●\033[0m"},     // Gray dot
        {"Desert", "\033[31m●\033[0m"},        // red dot
        {"default", "\033[0m●\033[0m"}         // Default dot
    };
    
    //For resource Type Guide
    std::vector<std::string> resourceTypes = {"Forest", 
                                               "Hills", 
                                               "Pasture", 
                                               "Fields",
                                               "Mountains",
                                                "Desert"};

    //Print color resource Type Guide
    for (const auto& type : resourceTypes) {
        std::cout << type << " color: " << colorTypeMap[type] << std::endl;
    }
}

/*printBoardGuide*/
void Board::BoardGuide() const {
    // Map resource types to ANSI color codes
    std::map<std::string, std::string> colorStringM = {
    {"Forest", "\033[0;32mForest\033[0m"},        // Green text
    {"Hills", "\033[38;5;208mHills\033[0m"},      // Orange text
    {"Pasture", "\033[37mPasture\033[0m"},   // White text
    {"Fields", "\033[33mFields\033[0m"}, // Yellow text
    {"Mountains", "\033[90mMountains\033[0m"},    // Gray text
    {"Desert", "\033[31mDesert\033[0m"},          // Red text
    {"default", "\033[0mUnknown\033[0m"}          // Default text
};
    

    for (const auto& settlement : settlements) {
        std::cout << "settlement " << settlement.settlementId << ": <" << colorStringM[settlement.hex1.first] << "," << settlement.hex1.second << ">";
        if (settlement.hex3.first != "NULL")
        {
            std::cout << ", " <<  ": <" << colorStringM[settlement.hex2.first] << "," << settlement.hex2.second << ">";
            std::cout << ", " <<  ": <" << colorStringM[settlement.hex3.first] << "," << settlement.hex3.second << ">" << std::endl;
        }
        else std::cout << ", " <<  ": <" << colorStringM[settlement.hex2.first] << "," << settlement.hex2.second << ">"<< std::endl; 
    }
   
}

const Settlement* Board::is3PlaceAvailable(const std::pair<std::string, int> hex1,const std::pair<std::string, int> hex2,const std::pair<std::string, int> hex3, std::string& playerId) const {
    for (const auto& settlement : settlements) {
        if ((settlement.hex1.first == hex1.first && settlement.hex1.second == hex1.second) &&
            (settlement.hex2.first == hex2.first && settlement.hex2.second == hex2.second) &&
            (settlement.hex3.first == hex3.first && settlement.hex3.second == hex3.second) ||
            (settlement.hex1.first == hex2.first && settlement.hex1.second == hex2.second) &&
            (settlement.hex2.first == hex3.first && settlement.hex2.second == hex3.second) &&
            (settlement.hex3.first == hex1.first && settlement.hex3.second == hex1.second) ||
            (settlement.hex1.first == hex3.first && settlement.hex1.second == hex3.second) &&
            (settlement.hex2.first == hex1.first && settlement.hex2.second == hex1.second) &&
            (settlement.hex3.first == hex2.first && settlement.hex3.second == hex2.second)) {
            if (!settlement.occupied) {
                settlement.setOccupied(true);
                settlement.setPlayerId(playerId);
                //SET setOccupied;
                //SET setplayerId;
                return &settlement;
            }
            std::cout << "Settlement is occupied by " << settlement.playerId << std::endl;
            std::cout << "Select a settlement from the list of unoccupied settlements:" << std::endl;
            BoardGuide();
            return nullptr;
        }
    }
    std::cout << "There is no such settlement in the board!" << std::endl;
    std::cout << "Select a settlement from the list of unoccupied settlements:" << std::endl;
    BoardGuide();
    return nullptr;
}

const Settlement* Board::is2PlaceAvailable(const std::pair<std::string, int> hex1, const std::pair<std::string, int> hex2, std::string& playerId) const {
    for (const auto& settlement : settlements) {
        if ((settlement.hex1.first == hex1.first && settlement.hex1.second == hex1.second) &&
            (settlement.hex2.first == hex2.first && settlement.hex2.second == hex2.second) &&
            (settlement.hex3.first == "NULL" && settlement.hex3.second == 0) ||
            (settlement.hex1.first == hex2.first && settlement.hex1.second == hex2.second) &&
            (settlement.hex2.first == hex1.first && settlement.hex2.second == hex1.second) &&
            (settlement.hex3.first == "NULL" && settlement.hex3.second == 0)) {
            if (!settlement.occupied) {
                settlement.setOccupied(true);
                settlement.setPlayerId(playerId);
                //SET setOccupied;
                //SET setplayerId;
                return &settlement;
            }
            else {
                std::cout << "Settlement is occupied by " << settlement.playerId << std::endl;
                std::cout << "Select a settlement from the list of unoccupied settlements:" << std::endl;
                BoardGuide();
                return nullptr;
            }
        }
    }
    std::cout << "There is no such settlement in the board!" << std::endl;
    std::cout << "Select a settlement from the list of unoccupied settlements:" << std::endl;
    BoardGuide();
    return nullptr;
}

const Settlement* Board::findSettlementById(int settlementId) const {
    for (auto& settlement : settlements) {
        if (settlement.settlementId == settlementId) {
            return &settlement;
        }
    }
    return nullptr; // Return nullptr if not found
}

const Settlement* Board::isPlaceAvailable_byID(int settlementId, std::string& playerId) const {
    const Settlement* settlement;
    settlement = findSettlementById(settlementId);
    if (settlement != nullptr)
    {
        if (!(*settlement).occupied){
                (*settlement).setOccupied(true);
                (*settlement).setPlayerId(playerId);
                //SET setOccupied;
                //SET setplayerId;
                return &(*settlement);
            }
            else {
                std::cout << "Settlement is occupied by " << (*settlement).playerId << std::endl;
                std::cout << "Select a settlement from the list of unoccupied settlements:" << std::endl;
                BoardGuide();
                return nullptr;
            }
    }
    std::cout << "There is no such settlement in the board!" << std::endl;
    std::cout << "Select a settlement from the list of unoccupied settlements:" << std::endl;
    BoardGuide();
    return nullptr;
}

// const Settlement* Board::isPlaceAvailable_byID(int settlementId, std::string& playerId) const {
//     for (const auto& settlement : settlements) {
//         if (settlement.settlementId == settlementId) {
//             if (!settlement.occupied){
//                 settlement.setOccupied(true);
//                 settlement.setPlayerId(playerId);
//                 //SET setOccupied;
//                 //SET setplayerId;
//                 return &settlement;
//             }
//             else {
//                 std::cout << "Settlement is occupied by " << settlement.playerId << std::endl;
//                 std::cout << "Select a settlement from the list of unoccupied settlements:" << std::endl;
//                 BoardGuide();
//                 return nullptr;
//             }
//         }
//     }
//     std::cout << "There is no such settlement in the board!" << std::endl;
//     std::cout << "Select a settlement from the list of unoccupied settlements:" << std::endl;
//     BoardGuide();
//     return nullptr;
// }

const Edge* Board::isRoadAvailable(const Settlement* u, int settlementId, std::string& playerId) const {
    const Settlement* v = findSettlementById(settlementId);
    if (u != nullptr && v != nullptr){
        for (const auto& edge : edges) {
            if (edge.settlement1 == u && edge.settlement1 == v)
            {
                if (edge.roads == 0)
                {
                    edge.setRoads(1);
                    edge.setPlayerId(playerId);
                }
                if (edge.roads == 1 && edge.playerId == playerId)
                {
                    edge.setRoads(2);
                }
                if (edge.roads == 1 && edge.playerId != playerId && edge.settlement2->playerId != playerId)
                {
                    edge.setRoads(2);
                    edge.setRoadThief(playerId);
                }
                return &edge;
            }
        }
    }
    return nullptr;
}

const Edge* Board::findEdgeByUV(const Settlement* u, const Settlement* v, std::string& playerId) const {
    if (u != nullptr && v != nullptr){
        for (const auto& edge : edges) {
            if (edge.settlement1 == u && edge.settlement1 == v){
                return &edge;
            }
        }
    }
    return nullptr;
}

void Board::printSometing() { 
    // Map resource types to ANSI color codes
    std::map<std::string, std::string> colorMap = {
        {"Forest", "\033[0;32m⬢ \033[0m"},        // Green hexagon
        {"Hills", "\033[38;5;208m⬢ \033[0m"}, // Orange hexagon
        {"Pasture", "\033[37m⬢ \033[0m"},  // White hexagon
        {"Fields", "\033[33m⬢ \033[0m"},         // Yellow hexagon
        {"Mountains", "\033[90m⬢ \033[0m"},     // Gray hexagon
        {"Desert", "\033[31m⬢ \033[0m"},        // Red hexagon
        {"default", "\033[0m⬢ \033[0m"}         // Default hexagon
    };

    // Print the board with colored dots
    std::cout << "Board Layout:" << std::endl;
    
    std::cout << "         / \\ 1 / \\ 2 / \\" << std::endl;
    std::cout << "        /   \\ /   \\ /   \\" << std::endl;

    std::cout << "       |     |     |     | " << std::endl;
    
    std::cout << "       3     4     5     6 " << std::endl;

    std::cout << "      / \\   / \\   / \\   / \\" << std::endl;
    std::cout << "     /   \\ /   \\ /   \\ /   \\" << std::endl;

    std::cout << "          7     8     9      " << std::endl;
    std::cout << "    |     |     |     |     |" << std::endl;
    std::cout << "   10    11    12    13    14" << std::endl;

    std::cout << "   / \\   / \\   / \\   / \\   / \\" << std::endl;
    std::cout << "  /   \\ /   \\ /   \\ /   \\ /   \\" << std::endl;

    std::cout << "      15    16    17    18      " << std::endl;
    std::cout << " |     |     |     |     |     |" << std::endl;
    std::cout << "      19    20    21    22      " << std::endl;
    
    std::cout << "  \\   / \\   / \\   / \\   / \\   /" << std::endl;
    std::cout << "   \\ /   \\ /   \\ /   \\ /   \\ /" << std::endl;

    std::cout << "   23    24    25    26    27" << std::endl;
    std::cout << "    |     |     |     |     |" << std::endl;
    std::cout << "         28    29    30      " << std::endl;
    
    std::cout << "     \\   / \\   / \\   / \\   /" << std::endl;
    std::cout << "      \\ /   \\ /   \\ /   \\ /" << std::endl;

    std::cout << "      31    32    33    34" << std::endl;
    std::cout << "       |     |     |     |" << std::endl;
    
    std::cout << "       \\    / \\   / \\   /" << std::endl;
    std::cout << "        \\  /35 \\ / 36\\ /" << std::endl;
   
}



// void Board::occupyPlace(const std::vector<std::string>& places, const std::vector<int>& placesNum) {
//     for (auto& settlement : settlements) {
//         if ((settlement.hex1.first == places[0] && settlement.hex1.second == placesNum[0]) ||
//             (settlement.hex2.first == places[1] && settlement.hex2.second == placesNum[1]) ||
//             (settlement.hex3.first == places[2] && settlement.hex3.second == placesNum[2])) {
//             settlement.occupied = true;
//         }
//     }
// }