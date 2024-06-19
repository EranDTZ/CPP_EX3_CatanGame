#include "player.hpp"
#include "catan.hpp"
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <string.h>
#define SIZE 1024

using namespace std;

Player::Player(const std::string& name) : name(name), points(0), isTurn(false) , cards() {
        srand(time(0)); // Initialize random seed
        cards.clear();
        playerSettlements.clear();
        // playerEdges.clear();

    }

    std::string Player::getName() const {
        return name;
    }


    void Player::rollDice(Catan& catan, Board& board) {
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

        //If player rolled a 7 activate Knight 
        if (diceSum == 7) {
            bool boo = true;
            int num = -1;
            std::string resource;
            std::string player;
            std::cout << "Knight activated. Choose where to put it." << std::endl;
            std::cout << "Resource: " << std::endl;
            std::cin >> resource;
            std::cout << "Resource number: " << std::endl;
            std::cin >> num;
            
            //Chack if Player inserted a currect other player name if not insert agine.
            while (boo)
            {
                std::cout << "Choose a player to steal from:" << std::endl;
                std::cin >> player;

                std::vector<std::string> catanPlayers;

                for (auto& other : catan.getPlayers()) {
                    if (other->getName() != name) {
                        catanPlayers.push_back(other->getName());
                    }
                }
                

                auto iter = std::find(catanPlayers.begin(), catanPlayers.end(), player);
                if (iter == catanPlayers.end()) {
                    std::cout << "Player doesn't exist: bad syntax, try again" << std::endl;
                    boo = true;
                } 
                else {
                    boo = false;
                }
            }
            
            //Chack if resource is good & number is good & player is good & Knight is activated properly
            if (catan.Knight(resource, num, player, boo)){
                //Steal from choosen player
                for (auto& other : catan.getPlayers()) {
                    if (other->getName() == player) { 
                        if(!other->Cards().empty()) {
                            std::string card;
                            // Get the first card
                            card = other->Cards().front();
                            // Remove the first card
                            other->Cards().erase(other->Cards().begin());
                            // Give card to current player
                            cards.push_back(card);
                        } 
                        else {
                            std::cout << player << " pack is empty." << std::endl;
                        }
                        std::cout << "in here$$" << std::endl;
                    }
                } 
            }
        }
        
        //For each player that have a settlements connected to that number give him the resource card 
        for (auto& player : catan.getPlayers())
        {
            for (auto& settlements : player->PlayerSettlements())
            {
                if (settlements.Hex1().second == diceSum)
                {
                    player->Cards().push_back(settlements.Hex1().first);
                }
                if (settlements.Hex2().second == diceSum)
                {
                    player->Cards().push_back(settlements.Hex2().first);
                }
                if (settlements.Hex3().second == diceSum)
                {
                    player->Cards().push_back(settlements.Hex3().first);
                }
                
            }
            
        }
        
    }

    void Player::endTurn() {
        isTurn = false;
        cout << name << " ended their turn." << endl;
    }


    void Player::trade(Player& other) {
        std::cout << "How many cards would you like to exchange?" << std::endl;
        int giveAmount = -1;
        std::cout << "give amount: " ;
        std::cin >> giveAmount;
        int receiveAmount  = -1;
        std::cout << "receive amount: " ;
        std::cin >> receiveAmount;

        std::vector<std::string> cardsToGive;
        cardsToGive.reserve(giveAmount);

        std::vector<std::string> cardsToReceive;
        cardsToGive.reserve(receiveAmount);

        std::string give;
        std::string receive;

        for (size_t i = 0; i < giveAmount; i++) {
            std::cout << "give card "<< i << " :" ;
            std::cin >> give;
            auto iter_currnt = std::find(cards.begin(), cards.end(), give);
            if (iter_currnt != cards.end()) {
                std::cout << "cord doesn't exsist for trade." << std::endl;
                return;
            }
            cardsToGive.push_back(give);
            std::cout << std::endl;
        }

        for (size_t i = 0; i < receiveAmount; i++){
            std::cout << "receive card "<< i << " :" ;
            std::cin >> receive;
            auto iter_other = std::find(other.cards.begin(), other.cards.end(), receive);
            if (iter_other != cards.end()) {
                std::cout << "cord doesn't exsist for trade." << std::endl;
                return;
            }
            cardsToReceive.push_back(give);
            std::cout << std::endl;
        }

        if (isTrade(other))
        {
            for (const auto& card : cardsToGive) {
                auto iter_currnt = std::find(cards.begin(), cards.end(), card);
                cards.erase(iter_currnt);
                other.cards.push_back(card);
                
            }
            for (const auto& card : cardsToReceive) {
                auto iter_other = std::find(other.cards.begin(), other.cards.end(), card);
                other.cards.erase(iter_other);
                cards.push_back(card); 
            }
        }
        std::cout << name << " trades " << giveAmount << " for" << receiveAmount << " with " << other.getName() << endl;
    }

    bool Player::isTrade(Player& other) {
        std::string ans = "NULL";
        std::cout << other.getName() << ", Write 'yes' if you approve the trade or 'no' if you do not approve." << std::endl;
        std::cin >> ans;
        if (ans == "yes")
        {
            return true;
        }
        return false;
    }

    void Player::buyDevelopmentCard(Catan& catan) {
        bool allCardsFound = true;
        std::vector<std::string> cardsToCheck = {"Pasture", "Fields" ,"Mountains"};

        for (const auto& card : cardsToCheck) {
            auto iter = std::find(cards.begin(), cards.end(), card);
            if (iter == cards.end()) {
                allCardsFound = false;
                return;
            }
        }

        for (const auto& card : cardsToCheck) {
            auto iter = std::find(cards.begin(), cards.end(), card);
            if (iter != cards.end()) {
                cards.erase(iter);
            }
        }     
        std::cout << name << " bought a development card." << std::endl;
        developmentCard.push_back(catan.getDevelopmentCard());
    }


    void Player::useDevelopmentCard(Catan& catan ,Board& board) {
        std::string card;
        std::cout << name << ", enter which development card you want to use: " << endl;
        std::cin >> card;

        auto iter = std::find(developmentCard.begin(), developmentCard.end(), card);
        if (iter != developmentCard.end()) {
            std::cout << "cord doesn't exsist." << std::endl;
            return;
        }

        if (card == "Knight")
        {
            bool boo = true;
            int num = -1;
            std::string resource;
            std::string player;
            std::cout << "You activated Knight. Choose where to put it." << std::endl;
            std::cout << "Resource: " << std::endl;
            std::cin >> resource;
            std::cout << "Resource number: " << std::endl;
            std::cin >> num;
            
            while (boo) {
                std::cout << "Choose a player to steal from:" << std::endl;
                std::cin >> player;

                auto iter = std::find_if(catan.getPlayers().begin(), catan.getPlayers().end(), 
                                        [&](Player* p) { return p->getName() == player; });

                if (iter == catan.getPlayers().end()) {
                    std::cout << "Player doesn't exist: bad syntax, try again" << std::endl;
                    boo = true;
                } 
                else {
                    boo = false;
                }
            }
            
            if (catan.Knight(resource, num, player, boo)) {

                for (auto& other : catan.getPlayers()) {
                    if (other->getName() == player) {
                        if(!other->Cards().empty()) {
                            std::string card;
                            // Get the first card
                            card = other->Cards().front();
                            // Remove the first card
                            other->Cards().erase(other->Cards().begin());
                            // Give card to current player
                            cards.push_back(card);
                        } 
                        else {
                            std::cout << player << " pack is empty." << std::endl;
                        }
                    }
                } 
            }
        }

        if (card == "Point")
        {
            points++;
        }

        if (card == "Monopoly")
        {
            int count = 0;
            std::vector<std::string> resourceTypes = {"Forest", "Hills", "Pasture", "Fields","Mountains"};
            std::string resource;
            std::cout << "Choose resource type to take from all players: " << std::endl;
            std::cin >> resource;
            auto iter = std::find(resourceTypes.begin(), resourceTypes.end(), resource);
            if (iter != resourceTypes.end()) {
                std::cout << "resource doesn't exsist: bad syntx" << std::endl;
                return;
            }
            for (auto& player : catan.getPlayers()) {
                for (auto& card : player->cards) {
                    if (card == resource)
                    {
                        auto iter = std::find(player->cards.begin(), player->cards.end(), resource);
                        player->cards.erase(iter);
                        count++;
                    }    
                }
            }

            for (size_t i = 0; i < count; i++)
            {
                cards.push_back(resource);
            } 
        }

        if (card == "Resources")
        {
            std::vector<std::string> resourceTypes = {"Forest", "Hills", "Pasture", "Fields","Mountains"};
            std::string resource1;
            std::string resource2;
            std::cout << "Choose resource type 1 : " << std::endl;
            std::cin >> resource1;
            std::cout << "Choose resource type 2 : " << std::endl;
            std::cin >> resource2;
            
            auto iter = std::find(resourceTypes.begin(), resourceTypes.end(), resource1);
            if (iter != resourceTypes.end()) {
                std::cout << "resource doesn't exsist: bad syntx" << std::endl;
                return;
            }
            iter = std::find(resourceTypes.begin(), resourceTypes.end(), resource2);
            if (iter != resourceTypes.end()) {
                std::cout << "resource doesn't exsist: bad syntx" << std::endl;
                return;
            }
            cards.push_back(resource1);
            cards.push_back(resource2);
        }

        if (card == "Roads")
        {
            placeTowRoads(board);
        }

        developmentCard.erase(iter);
    }


    void Player::bankTrade() {
        std::vector<std::string> resourceTypes = {"Forest", "Hills", "Pasture", "Fields","Mountains"};
        std::string resource_give;
        std::string resource_get;
        int four = 0;
        std::cout << "resource type to give (4) : " << std::endl;
        std::cin >> resource_give;
        std::cout << "resource type to get : " << std::endl;
        std::cin >> resource_get;
        for (auto& card : cards) {
            if (card == resource_give)
            {
                four++;
            }
            if (four == 4)
            {
                break;
            }  
        }
        auto iter = std::find(resourceTypes.begin(), resourceTypes.end(), resource_get);
        if (iter != resourceTypes.end()) {
            std::cout << "resource doesn't exsist: bad syntx" << std::endl;
            return;
        }
        for (size_t i = 0; i < four; i++)
        {
            iter = std::find(cards.begin(), cards.end(), resource_give);
            cards.erase(iter);
        }
        cards.push_back(resource_get);  
    }


    bool Player::buySettelemnt() {
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

    bool Player::buyRoad() {
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
        const Settlement* v = new Settlement();
        int settlementId = -1;
        if (points == 0 || points == 1 || buySettelemnt()) {
            if (points == 0)
                std::cout << "A settlement is an intersection of 2 OR 3 resources! Choose Wisely\n";

            std::cout << name << ", choose a place for your settlement by inserting the settlementId: ";
            std::cin >> settlementId;
            if (settlementId > 0 && settlementId < 37){
                //Chack if place is available by settlement ID & player name.
                v = board.isPlaceAvailable_byID(settlementId,name);
            }
            else {
                std::cout << "settlement ID is incorrect! try again\n";
                placeSettelemnt(board);
            }
            if (v != nullptr) {
                //Chack if it is the first or the second Settlement.
                if (points == 0 || points == 1) {
                    if (points == 1)
                    {
                        cards.push_back(v->Hex1().first);
                        cards.push_back(v->Hex2().first);

                        if (v->Hex3().first != "NULL")
                        {
                            cards.push_back(v->Hex1().first);
                        }
                    }
                    playerSettlements.push_back(*v);
                    //If first or the second Settlement, let the player choose a Road also.
                    placeRoad(board,settlementId);
                    points++;
                    return;

                }
                //Check if a player have a phth to the settlement befor letting him take it.
                else if (board.findEdgeToV(v,name))
                {
                    playerSettlements.push_back(*v);
                    points++;
                    return;
                }
            }
            else {
                placeSettelemnt(board);
                cards.push_back("Forest");
                cards.push_back("Hills");
                cards.push_back("Pasture");
                cards.push_back("Fields");
            } 
        }
        else std::cout << "You don't have all tha resourceTypes in your cards" << std::endl;
    }

    void Player::placeRoad(Board& board, int settlementId) {
        int toSettlementId;
        bool isRoad = false;
        if (points == 0) 
            std::cout << "A road is an edge betwin 1 OR 2 settlement! Choose Wisely\n";

        std::cout << name << ", choose the settlement ID that the road leads to: ";
        std::cin >> toSettlementId;
        for (auto& place : playerSettlements) {
            if (place.SettlementId() == settlementId) {
                isRoad = board.isRoadAvailable(&place,toSettlementId,name);
                if (isRoad == true) {
                    cout << name << " placed a road from settlement " << place.SettlementId() << " to settlement " << toSettlementId << std::endl;
                    return;
                }
                break;
            }
            if (isRoad == true) {
                break;
            } 
        }
        if (isRoad == false)
        {
            std::cout << "You are trying to place a Road from settlement " << settlementId << std::endl;
            std::cout << "Here are a board guide so you can see your options: " << std::endl;
            board.Guide();
            placeRoad(board,settlementId);
        }
        return;
    }

    void Player::placeRoad(Board& board) {
        int mySettlementId;
        int toSettlementId;
        bool isRoad = false;

        if (buyRoad()) {
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
                std::cout << "You are trying to place a Road from settlement " << mySettlementId << std::endl;
                std::cout << "Here are a board guide so you can see your options: " << std::endl;
                board.Guide();
                placeRoad(board,mySettlementId);
            } 
        }
    }


void Player::placeTowRoads(Board& board) {
        int mySettlementId;
        int toSettlementId;
        bool isRoad = false;
        for (size_t i = 0; i < 2; i++)
        {
            if (points == 0) 
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
                std::cout << "try again using this board guide." << std::endl;
                board.Guide();
                placeTowRoads(board);
            }
        }
    }

    void Player::printPoints() const {
        cout << name << " has " << points << " points." << endl;
    }

    int Player::getPoints() const {
        return points;
    }

    void Player::printCards() {
        if (!Cards().empty()) {
            std::cout << "You have " << Cards().size() << " cards" << std::endl;  
            std::cout << "Your cards:" << std::endl;  
            for (auto& card : Cards()) {
                std::cout << card << ", ";
            }
            std::cout << "." << std::endl;  
        }
        std::cout << "You dont have any cards ):" << std::endl;  
    }

    void Player::printSettlements() {
            std::cout << "You have " << PlayerSettlements().size() << " Settlements" << std::endl;  
            std::cout << "Your Settlements:" << std::endl;  
            for (auto& settlement : PlayerSettlements()) {
                std::cout << settlement.SettlementId() << ", ";
            }
            std::cout << "." << std::endl;  
    }

    void Player::printDevelopment() {
        if (!getDevelopment().empty()) {
            std::cout << "You have " << getDevelopment().size() << " development cards" << std::endl;  
            std::cout << "Your development cards:" << std::endl;  
            for (auto& development : getDevelopment()) {
                std::cout << development << ", ";
            }
            std::cout << "." << std::endl;  
        }
        std::cout << "You dont have any development cards ):" << std::endl;  
    }

    void Player::myInfo() {
        printSettlements();
        printDevelopment();
        printCards();
    }
