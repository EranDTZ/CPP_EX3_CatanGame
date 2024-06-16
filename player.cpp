#include "player.hpp"
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>

using namespace std;

Player::Player(const std::string& name) : name(name), points(0), isTurn(false) , cards() {
        srand(time(0)); // Initialize random seed
        cards.clear();
        playerSettlements.clear();
        playerEdges.clear();

    }

    std::string Player::getName() const {
        return name;
    }

    void Player::rollDice() {
        if (!isTurn) {
            throw runtime_error(name + " tried to roll the dice but it's not their turn.");
        }
        int diceSum = 0;
        for (size_t i = 0; i < 2; i++)
        {
            int diceRoll = rand() % 6 + 1;
            cout << " dice " << i+1 << ": " << diceRoll << endl;
            diceSum += diceRoll;
        }

        cout << name << " rolled a " << diceSum << endl;
    }

    void Player::endTurn() {
        isTurn = false;
        cout << name << " ended their turn." << endl;
    }

    void Player::trade(Player& other, const std::string& give, const std::string& receive, int giveAmount, int receiveAmount) {
        // Logic to trade resources
        cout << name << " trades " << giveAmount << " " << give << " for " << receiveAmount << " " << receive << " with " << other.getName() << endl;
    }

    void Player::buyDevelopmentCard() {
        bool allCardsFound = true;
        std::vector<std::string> cardsToCheck = {"Forest", "Hills", "Pasture", "Fields"};

        for (const auto& card : cardsToCheck) {
            auto iter = std::find(cards.begin(), cards.end(), card);
            if (iter == cards.end()) {
                allCardsFound = false;
                break;
            }
        }

        for (const auto& card : cardsToCheck) {
            auto iter = std::find(cards.begin(), cards.end(), card);
            if (iter != cards.end()) {
                cards.erase(iter);
            }
        }     
        cout << name << " bought a development card." << endl;

        /*Here i can add a section of developed cards (like a night or a monopole or roads a winning point)
        and added the card to the player cards*/

        points ++; // Assuming each development card gives 1 point
    }

    bool Player::buySettelemntCard() {
        bool allCardsFound = true;
        std::vector<std::string> cardsToCheck = {"Forest", "Hills", "Pasture", "Fields"};

        for (const auto& card : cardsToCheck) {
            auto iter = std::find(cards.begin(), cards.end(), card);
            if (iter == cards.end()) {
                allCardsFound = false;
                return false;
            }
        }

        for (const auto& card : cardsToCheck) {
            auto iter = std::find(cards.begin(), cards.end(), card);
            if (iter != cards.end()) {
                cards.erase(iter);
            }
        }
        return true;     
    }

    bool Player::buyRoadCard() {
        bool allCardsFound = true;
        std::vector<std::string> cardsToCheck = {"Forest", "Hills"};

        for (const auto& card : cardsToCheck) {
            auto iter = std::find(cards.begin(), cards.end(), card);
            if (iter == cards.end()) {
                allCardsFound = false;
                return false;
            }
        }

        for (const auto& card : cardsToCheck) {
            auto iter = std::find(cards.begin(), cards.end(), card);
            if (iter != cards.end()) {
                cards.erase(iter);
            }
        }
        return true;   
    }

    void Player::placeSettelemnt(Board& board){
        const Settlement* v = (Settlement*)malloc(sizeof(Settlement));
        int settlementId = -1;
        if (points == 0 || points == 1 || buySettelemntCard())
        {
            std::cout << "A settlement is an intersection of 2 OR 3 resources! Choose Wisely\n";

            std::cout << name << ", choose a place for your settlement by inserting the settlementId: ";
            std::cin >> settlementId;
            if (settlementId > 0 && settlementId < 37)
            {
                v = board.isPlaceAvailable_byID(settlementId,name);
            }
            else {
                std::cout << "settlement ID is incorrect!\n";
                return;
            }
            if (v != nullptr) {
                if (points == 0 || points == 1)
                {
                    playerSettlements.push_back(*v);
                }
                else if (board.findEdgeToV(v,name))
                {
                    playerSettlements.push_back(*v);
                }
            }
            else
            {
                cards.push_back("Forest");
                cards.push_back("Hills");
                cards.push_back("Pasture");
                cards.push_back("Fields");
                throw std::runtime_error("Place already occupied.");
            } 

            if (points == 0 || points == 1)
            {
                int id = v->SettlementId();
                placeRoad(board,id);
            }
            points++;
            return;
        }
        
        else std::cout << "You don't have all tha resourceTypes in your cards" << endl;
    }

    void Player::placeRoad(Board& board, int settlementId) {
        int toSettlementId;
        bool isRoad = false;
        std::cout << name << ", choose the settlement ID that the road leads to: ";
        std::cin >> toSettlementId;
        for (auto& place : playerSettlements) {
            if (place.SettlementId() == settlementId) {
                isRoad = board.isRoadAvailable(&place,toSettlementId,name);
                if (isRoad == true)
                {
                    cout << name << " placed a road from settlement " << place.SettlementId() << " to settlement " << toSettlementId << std::endl;
                }
                break;
            }
            if (isRoad == true)
            {
                break;
            } 
        }
        if (isRoad == false)
        {
            std::cout << "Sorry you can`t place a Road here, the Rode is block." << std::endl;
        }
        return;
    }

    void Player::placeRoad(Board& board) {
        int mySettlementId;
        int toSettlementId;
        bool isRoad = false;

        if (points == 0 || points == 1 || buySettelemntCard()) {

            std::cout << "A road is an edge betwin 1 OR 2 settlement! Choose Wisely\n";
            std::cout << name << ", choose a place for your Road by inserting the settlement ID (from your settlements),\nand the settlement ID that the road leads to : ";
            for (size_t i = 0; i < 2; i++) {
                std::cout << "my Settlement ID " << i << ": "<< std::endl;
                std::cin >> mySettlementId;
                std::cout << "to Settlement ID " << i << ": "<< std::endl;
                std::cin >> toSettlementId;
            }
            for (const auto& place : playerSettlements) {
                if (place.SettlementId() == mySettlementId) {
                    isRoad = board.isRoadAvailable(&place,toSettlementId,name);
                    if (isRoad == true)
                    {
                        cout << name << " placed a road from settlement " << place.SettlementId() << " to settlement " << toSettlementId << std::endl;
                    }
                    break;
                }
                if (isRoad == true)
                {
                    break;
                } 
            }
            if (isRoad == false)
            {
                std::cout << "Sorry you can`t place a Road here, the Rode is block." << std::endl;
                cards.push_back("Forest");
                cards.push_back("Hills");
            }
            /*?? chack if done  ??*/            
        }
    }

    void Player::printPoints() const {
        cout << name << " has " << points << " points." << endl;
    }

    int Player::getPoints() const {
        return points;
    }
