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

    void setOccupied(bool occ) { occupied = occ; }
    void setPlayerId(const std::string& id) { playerId = id; }
    bool isOccupied() const { return occupied; }
    std::string PlayerId() const { return playerId; }
    int SettlementId() const { return settlementId; }
    std::pair<std::string, int> Hex1() const { return hex1; }
    std::pair<std::string, int> Hex2() const { return hex2; }
    std::pair<std::string, int> Hex3() const { return hex3; }
};


class Edge {
private:
    int edgeId;
    int roads;
    std::string playerId;
    std::string roadThief;
    Settlement* settlement1;
    Settlement* settlement2;

public:
    Edge()
        : settlement1(nullptr), settlement2(nullptr), roads(0), playerId("NULL"), roadThief("NULL") {}
    
    Edge(Settlement* s1, Settlement* s2) : settlement1(s1), settlement2(s2), roads(0), playerId("NULL"), roadThief("NULL")  {}

    Edge(int id, Settlement* s1, Settlement* s2) : edgeId(id), roads(0), playerId(""), settlement1(s1), settlement2(s2) {}

    void setRoads(int r) { roads = r; }
    void setPlayerId(const std::string& id) { playerId = id; }
    void setRoadThief(const std::string& id) { roadThief = id; }
    int getEdgeId() const { return edgeId; }
    int Roads() const { return roads; }
    std::string PlayerId() const { return playerId; }
    std::string RoadThief() const { return roadThief; }
    Settlement* Settlement1() const { return settlement1; }
    Settlement* Settlement2() const { return settlement2; }
};

class Board {
public:
    Board();
    void initializeBoard();
    void initializeEdges();
    void printBoard();
    void ResourceGuide();
    void BoardGuide() const;
    void printSometing();
    Settlement* is3PlaceAvailable(const std::pair<std::string, int> hex1, const std::pair<std::string, int> hex2, const std::pair<std::string, int> hex3, std::string& playerId);
    Settlement* is2PlaceAvailable(const std::pair<std::string, int> hex1, const std::pair<std::string, int> hex2, std::string& playerId);
    const Settlement* findSettlementById(int settlementId);
    Settlement* isPlaceAvailable_byID(int settlementId, std::string& playerId);
    bool isRoadAvailable(const Settlement* u, int settlementId, std::string& playerId);
    const Edge* findEdgeByUV(const Settlement* u, const Settlement* v, std::string& playerId);
    bool findEdgeToV(const Settlement* v, std::string& playerId) const;
    void occupyPlace(const std::vector<std::string>& places, const std::vector<int>& placesNum);
private:
    std::vector<std::pair<std::string, int>> hexes;
    std::vector<Settlement> settlements;
    std::vector<Edge> edges;
};

#endif // BOARD_HPP
