#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <random>
#include "board.hpp"


Board::Board() {
    initializeBoard();
    initializeEdges();
    printBoard();
    ResourceGuide();
    Guide();
    settlementGuide();
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
    Road* road = nullptr;

    // Define all settlement connections
    std::vector<std::pair<int, int>> oneRoad = {
        {1, 4} ,{2, 5} ,{3, 7} ,{4, 7},{4, 8} ,{5, 8} ,{5, 9} ,{6, 9}, {7, 11}, {8, 12}, {9, 13},
        {10, 15} ,{11, 15} ,{11, 16} ,{12, 16},{12, 17} ,{13, 17} ,{13, 18} ,{14, 18}, {15, 19}, {16, 20}, {17, 21}, {18, 22},
        {19, 23} ,{19, 24} ,{20, 24} ,{20, 25},{21, 25} ,{21, 26} ,{22, 26} ,{22, 27}, {24, 28}, {25, 29}, {26, 30},
        {28, 31} ,{28, 32} ,{29, 32} ,{29, 33},{30, 33} ,{30, 34} ,{32, 35} ,{33, 36}
    };

    std::vector<std::pair<int, int>> towRoad = {
        {1, 2} ,{35, 36}
    };

    std::vector<std::pair<int, int>> threeRoad = {
        {1, 3} ,{2, 6} , {3, 10} ,{6, 14} , {10, 23} ,{14, 27} , {23, 31} ,{27, 34} , {31, 35} ,{34, 36}
    };

    Settlement* settlement1 = new Settlement();
    Settlement* settlement2 = new Settlement();

    Road* r1 = new Road();
    Road* r2 = new Road();
    Road* r3 = new Road();

    for (auto& road : oneRoad)
    {
        int settlementId1 = road.first;
        int settlementId2 = road.second;

        for (auto& settlement : settlements) {
            if (settlement.SettlementId() == settlementId1) {
                settlement1 = &settlement;
            }
            if (settlement.SettlementId() == settlementId2) {
                settlement2 = &settlement;
            }
        }

        if (settlement1 && settlement2) {
            edges.emplace_back(settlement1, settlement2 ,r1);
        }

    }


    for (auto& road : towRoad)
    {
        int settlementId1 = road.first;
        int settlementId2 = road.second;

        for (auto& settlement : settlements) {
            if (settlement.SettlementId() == settlementId1) {
                settlement1 = &settlement;
            }
            if (settlement.SettlementId() == settlementId2) {
                settlement2 = &settlement;
            }
        }

        if (settlement1 && settlement2) {
            edges.emplace_back(settlement1, settlement2, r1, r2);
        }

    }

    for (auto& road : threeRoad)
    {
        int settlementId1 = road.first;
        int settlementId2 = road.second;

        for (auto& settlement : settlements) {
            if (settlement.SettlementId() == settlementId1) {
                settlement1 = &settlement;
            }
            if (settlement.SettlementId() == settlementId2) {
                settlement2 = &settlement;
            }
        }

        if (settlement1 && settlement2) {
            edges.emplace_back(settlement1, settlement2, r1, r2, r3);
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

void Board::printEdges() {
    int i = 0;
    for (auto& edge : edges){
        i++;
        std::cout << "edge " << i << " : from " << edge.Settlement1()->SettlementId() << " to " << edge.Settlement2()->SettlementId() <<std::endl;
    }
    
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
void Board::settlementGuide() {
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
    

    for (auto& settlement : settlements) {
        //If settlement ISN`T Occupied print it.
        if (!settlement.isOccupied() && findEdgeFromU(&settlement))
        {
            std::cout << "settlement " << settlement.SettlementId() << ": <" << colorStringM[settlement.Hex1().first] << "," << settlement.Hex1().second << ">";
            if (settlement.Hex3().first != "NULL")
            {
                std::cout << ", " <<  ": <" << colorStringM[settlement.Hex2().first] << "," << settlement.Hex2().second << ">";
                std::cout << ", " <<  ": <" << colorStringM[settlement.Hex3().first] << "," << settlement.Hex3().second << ">" << std::endl;
            }
            else std::cout << ", " <<  ": <" << colorStringM[settlement.Hex2().first] << "," << settlement.Hex2().second << ">"<< std::endl; 
        }
    }
   
}

void Board::helprint(int from, int to) {
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

    // blue hexagon
    std::map<int, std::string> b = {
        {1, "\033[36m1\033[0m"}, {6, "\033[36m6\033[0m"}, {11, "\033[36m11\033[0m"}, {15, "\033[36m15\033[0m"},
        {2, "\033[36m2\033[0m"}, {7, "\033[36m7\033[0m"}, {12, "\033[36m12\033[0m"}, {16, "\033[36m16\033[0m"},
        {3, "\033[36m3\033[0m"}, {8, "\033[36m8\033[0m"}, {13, "\033[36m13\033[0m"}, {17, "\033[36m17\033[0m"},
        {4, "\033[36m4\033[0m"}, {9, "\033[36m9\033[0m"}, {14, "\033[36m14\033[0m"}, {18, "\033[36m18\033[0m"},
        {5, "\033[36m5\033[0m"}, {10, "\033[36m10\033[0m"}
    };

    for (int i = from; i < (to+1) ; i++)
    {
        if (i == 0 || i == 16)
        {
            std::cout << "       ";
        }
        if (i == 3 || i == 12)
        {
            std::cout << "    ";
        }
        if (i == 7)
        {
            std::cout << "";
        }
        if (hexes[i].second < 10)
        {
            std::cout << "| " << colorMap[hexes[i].first] << b[hexes[i].second] << " ";
        }
        else {
            std::cout << "|" << colorMap[hexes[i].first] << b[hexes[i].second] << " ";
        }
    }
    std::cout << "| " << std::endl;
}


void Board::Guide() { 
    std::cout << "Board Layout:" << std::endl;
    
    std::cout << "         / \\ 1 / \\ 2 / \\" << std::endl;
    std::cout << "        /   \\ /   \\ /   \\" << std::endl;
    helprint(0,2);
    std::cout << "       3     4     5     6 " << std::endl;

    std::cout << "      / \\   / \\   / \\   / \\" << std::endl;
    std::cout << "     /   \\ /   \\ /   \\ /   \\" << std::endl;

    std::cout << "          7     8     9      " << std::endl;
    helprint(3,6);
    std::cout << "   10    11    12    13    14" << std::endl;

    std::cout << "   / \\   / \\   / \\   / \\   / \\" << std::endl;
    std::cout << "  /   \\ /   \\ /   \\ /   \\ /   \\" << std::endl;

    std::cout << "      15    16    17    18      " << std::endl;
    helprint(7,11);
    std::cout << "      19    20    21    22      " << std::endl;
    
    std::cout << "  \\   / \\   / \\   / \\   / \\   /" << std::endl;
    std::cout << "   \\ /   \\ /   \\ /   \\ /   \\ /" << std::endl;

    std::cout << "   23    24    25    26    27" << std::endl;
    helprint(12,15);
    std::cout << "         28    29    30      " << std::endl;
    
    std::cout << "     \\   / \\   / \\   / \\   /" << std::endl;
    std::cout << "      \\ /   \\ /   \\ /   \\ /" << std::endl;

    std::cout << "      31    32    33    34" << std::endl;
    helprint(16,18);
    std::cout << "       \\    / \\   / \\   /" << std::endl;
    std::cout << "        \\  /35 \\ / 36\\ /" << std::endl;
   
}


Settlement* Board::isPlaceAvailable_byID(int settlementId, std::string& playerId) {
    for (auto& settlement : settlements) {
        if (settlement.SettlementId() == settlementId) {
            //If settlement isn`t occupied && there is no occupied settlement one road away
            if (!settlement.isOccupied() && findEdgeFromU(&settlement)){
                settlement.setOccupied(true);
                settlement.setPlayerId(playerId);    
                return &settlement;
            }
            else {
                std::cout << "Settlement is is occupied by " << settlement.PlayerId() << std::endl;
                std::cout << "Select a settlement from the list of unOccupied settlements:" << std::endl;
                settlementGuide();
                return nullptr;
            }
        }
    }
    std::cout << "There is no such settlement in the board!" << std::endl;
    std::cout << "Select a settlement from the list of unOccupied settlements:" << std::endl;
    settlementGuide();
    return nullptr;
}

const Settlement* Board::findSettlementById(int settlementId) {
    for (auto& settlement : settlements) {
        if (settlement.SettlementId() == settlementId) {
            return &settlement;
        }
    }
    return nullptr; // Return nullptr if not found
}


bool Board::isRoadAvailable(const Settlement* u, int toSettlementId, std::string& playerId) {
    const Settlement* v = findSettlementById(toSettlementId);
    if (u != nullptr && v != nullptr){
        for (auto& edge : edges) {
            if (edge.Settlement1()->SettlementId() == u->SettlementId() && edge.Settlement2()->SettlementId() == v->SettlementId()
            || edge.Settlement1()->SettlementId() == v->SettlementId() && edge.Settlement2()->SettlementId() == u->SettlementId()) {

                if (edge.Road1()->PlayerId() == "NULL") {
                    edge.Road1()->setPlayerId(playerId);
                    return true;
                }
                else if (edge.Road2() != nullptr && edge.Road2()->PlayerId() == "NULL") {
                    edge.Road2()->setPlayerId(playerId);
                    return true;
                }
                else if (edge.Road3() != nullptr && edge.Road3()->PlayerId() == "NULL") {
                    edge.Road3()->setPlayerId(playerId);
                    return true;
                }
                else {
                    std::cout << "This Edge is full, it can`t hold anymore Roads!" << std::endl;
                    return false;
                }
            }
        }
    }
    std::cout << "There is no Edge on the board!" << std::endl;
    return false;
}

const Edge* Board::findEdgeByUV(const Settlement* u, const Settlement* v, std::string& playerId) {
    if (u != nullptr && v != nullptr){
        for (const auto& edge : edges) {
            if (edge.Settlement1() == u && edge.Settlement2() == v){
                return &edge;
            }
        }
    }
    return nullptr;
}

bool Board::findEdgeFromU(const Settlement* u) {
    if (u != nullptr){
        for (const auto& edge : edges) {
            if (edge.Settlement1() == u && edge.Settlement2()->PlayerId() != "NULL" || edge.Settlement2() == u && edge.Settlement1()->PlayerId() != "NULL"){
                return false;
            }
        }
    }
    return true;
}

bool Board::findEdgeToV(const Settlement* v, std::string& playerId) const {
    if (v != nullptr){
        for (const auto& edge : edges) {
            if (edge.Settlement1() == v || edge.Settlement2() == v){
                //If Edge is with one Road
                if (edge.Road1() != nullptr && edge.Road2() == nullptr && edge.Road3() == nullptr)
                {
                    if (edge.Road1()->PlayerId() == playerId)
                    {
                        return true;
                    }
                }
                //If Edge is with tow Road
                if (edge.Road1() != nullptr && edge.Road2() != nullptr && edge.Road3() == nullptr)
                {
                    if (edge.Road1()->PlayerId() == playerId && edge.Road2()->PlayerId() == playerId)
                    {
                        return true;
                    }
                }
                //If Edge is with tow Road
                if (edge.Road1() != nullptr && edge.Road2() != nullptr && edge.Road3() != nullptr)
                {
                    if (edge.Road1()->PlayerId() == playerId && edge.Road2()->PlayerId() == playerId && edge.Road3()->PlayerId() == playerId)
                    {
                        return true;
                    }
                }
            }
        }
    }
    std::cout << "Sorry, you don`t own all the Roads to put a settlement here!" << std::endl;
    return false;
}


