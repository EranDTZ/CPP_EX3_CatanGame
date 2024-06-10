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
    }

    std::string Player::getName() const {
        return name;
    }


    // void Player::placeFirstSettelemnt(const std::vector<std::string>& places, const std::vector<int>& placesNum, Board& board) {
    //     // Logic to place a settlement
    //     if (board.isPlaceAvailable(places,placesNum))
    //     {
    //         cout << name << " placed a settlement at ";
    //         for (const auto& place : places) {
    //             cout << place << " ";
    //             /*Here i need to placeFirstRoad but to where? and hoe do i keep track?*/
    //         }
    //         cout << endl;
    //         points ++; // Assuming each settlement gives 1 point
    //         cards.push_back(places[1]);//isert a card of the second resourceTypes
    //     }
    //     else
    //     {
    //         std::cout << "place is already occupied" << endl;
    //         std::cout << "choose another places and placesNum for your settlements";
    //     }
    // }

    void Player::placeFirstRoad(const std::vector<std::string>& places, const std::vector<int>& placesNum, Board& board) {
        // Logic to place a road
        cout << name << " placed a road at ";
        for (const auto& place : places) {
            cout << place << " ";
        }
        cout << endl;
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

    // void Player::trade(Player& other, const std::string& give, const std::string& receive, int giveAmount, int receiveAmount) {
    //     // Logic to trade resources
    //     cout << name << " trades " << giveAmount << " " << give << " for " << receiveAmount << " " << receive << " with " << other.getName() << endl;
    // }

    void Player::buyDevelopmentCard() {
        bool allCardsFound = true;
        std::vector<std::string> cardsToCheck = {"Forest", "Hills", "Pasture Land", "Agricultural Land"};

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
        std::vector<std::string> cardsToCheck = {"Forest", "Hills", "Pasture Land", "Agricultural Land"};

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
        if (points == 0 || buySettelemntCard())
        {
            bool available = false;
            std::pair<std::string, int> hex1;
            std::pair<std::string, int> hex2;
            std::pair<std::string, int> hex3;
            std::string type = "NULL";
            int resources = 0;
            int number = 0;
            std::cout << "A settlement is an intersection of 2 OR 3 resources! Choose Wisely\n";
            std::cout << "insert the number of resources in your settlement: \n";
            std::cin >> resources;
            std::cout << name << ", choose a place for your settlement by inserting the resources types & Numbers: ";
            for (int i = 0; i < 3; i++)
            {
                std::cout << "resource " << i << " type: "<< std::endl;
                std::cin >> type;
                std::cout << "resource " << i << " number: "<< std::endl;
                std::cin >> number;
                if (i == 0)
                {
                    hex1.first = type;
                    hex1.second = number;
                }
                if (i == 1)
                {
                    hex2.first = type;
                    hex2.second = number;
                }
                if (i == 2)
                {
                    hex3.first = type;
                    hex3.second = number;
                }
                if (resources == 2 && i == 1)
                {
                    break;
                }
            }
            
            if (resources == 2)
            {
                available = board.is2PlaceAvailable(hex1,hex2,name);
            }
            else{
                available = board.is3PlaceAvailable(hex1,hex2,hex3,name);
            }
            if (!available) {
                cards.push_back("Forest");
                cards.push_back("Hills");
                cards.push_back("Pasture Land");
                cards.push_back("Agricultural Land");
                throw std::runtime_error("Place already occupied.");
            }
            points++;
            return;
        }
        else std::cout << "You don't have all tha resourceTypes in your cards" << endl;
    }

    void Player::printPoints() const {
        cout << name << " has " << points << " points." << endl;
    }

    int Player::getPoints() const {
        return points;
    }
