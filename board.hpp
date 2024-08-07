#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include <map>
#include <string>
#include <utility>
#include <iostream>


class Settlement {
private:
    int settlementId;
    bool occupied;
    std::string playerId;
    std::pair<std::string, int> hex1;
    std::pair<std::string, int> hex2;
    std::pair<std::string, int> hex3;

public:
    Settlement() 
        : hex1({"NULL", 0}), hex2({"NULL", 0}), hex3({"NULL", 0}), settlementId(-1), occupied(false), playerId("NULL") {}
    
    Settlement(const std::pair<std::string, int>& h1, const std::pair<std::string, int>& h2,
               const std::pair<std::string, int>& h3, const int settlementId)
        : hex1(h1), hex2(h2), hex3(h3), settlementId(settlementId), occupied(false), playerId("NULL") {}

    Settlement(const std::pair<std::string, int>& h1, const std::pair<std::string, int>& h2, const int settlementId)
        : hex1(h1), hex2(h2), hex3({"NULL", 0}), settlementId(settlementId), occupied(false), playerId("NULL") {}

    Settlement(int id) : settlementId(id), occupied(false), playerId("NULL") {}


    void setHex1Int(int value) { hex1.second = value; } 
    void setHex2Int(int value) { hex1.second = value; } 
    void setHex3Int(int value) { hex1.second = value; } 
    void setOccupied(bool occ) { occupied = occ; }
    void setPlayerId(const std::string& id) { playerId = id; }
    bool isOccupied() const { return occupied; }
    std::string PlayerId() const { return playerId; }
    int SettlementId() const { return settlementId; }
    std::pair<std::string, int> Hex1() const { return hex1; }
    std::pair<std::string, int> Hex2() const { return hex2; }
    std::pair<std::string, int> Hex3() const { return hex3; }
};


class Road {
private:
    std::string playerId;

public:
    Road()
        : playerId("NULL") {}

    void setPlayerId(const std::string& id) { playerId = id; }
    std::string PlayerId() const { return playerId; }
};



class Edge {
private:
    int occupied;
    Road* road1;
    Road* road2;
    Road* road3;
    Settlement* settlement1;
    Settlement* settlement2;

public:

    Edge(Settlement* s1, Settlement* s2, Road* road1) : settlement1(s1), settlement2(s2), road1(new Road()), road2(nullptr), road3(nullptr),occupied(false) {}
    
    Edge(Settlement* s1, Settlement* s2, Road* road1, Road* road2) : settlement1(s1), settlement2(s2), road1(new Road()), road2(new Road()), road3(nullptr), occupied(false) {}

    Edge(Settlement* s1, Settlement* s2, Road* road1, Road* road2, Road* road3) : settlement1(s1), settlement2(s2), road1(new Road()), road2(new Road()), road3(new Road()), occupied(false) {}

    
    void setOccupied(bool occ) { occupied = occ; }
    bool isOccupied() const { return occupied; }
    Settlement* Settlement1() const { return settlement1; }
    Settlement* Settlement2() const { return settlement2; }
    Road* Road1() const { return road1; }
    Road* Road2() const { return road2; }
    Road* Road3() const { return road3; }
};

class Board {
public:
    Board();
    void initializeBoard();
    void initializeEdges();
    void printBoard();
    void printEdges();
    void ResourceGuide();
    void settlementGuide();
    void helprint(int from, int to);
    void Guide();
    const Settlement* findSettlementById(int settlementId);
    Settlement* isPlaceAvailable_byID(int settlementId, std::string& playerId);
    bool isRoad(int settlementId, int toSettlementId, std::string& playerId, std::vector<Settlement> playerSettlements);
    bool isRoadAvailable(const Settlement* u, int toSettlementId, std::string& playerId);
    const Edge* findEdgeByUV(const Settlement* u, const Settlement* v, std::string& playerId);
    bool findEdgeFromU(const Settlement* u);
    bool findEdgeToV(const Settlement* v, std::string& playerId) const;
    bool is2road(const Settlement* v, std::string& playerId) const;
    std::vector<std::pair<std::string, int>> getHexes() const { return hexes; }
    std::vector<Settlement> getSettlements() const { return settlements; }
    std::vector<Edge> getEdges() const { return edges; }
private:
    std::vector<std::pair<std::string, int>> hexes;
    std::vector<Settlement> settlements;
    std::vector<Edge> edges;
    // void Roads_init(const Settlement* u, const Settlement* v, std::string& playerId);
};

#endif // BOARD_HPP
