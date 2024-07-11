#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "catan.hpp"
#include "player.hpp"
#include "board.hpp"

/*-------------------------------------------------CATAN--------------------------------------------------------*/

TEST_CASE("Catan Class") {
    Player p1("Alice");
    Player p2("Bob");
    Player p3("Charlie");

    Catan catan(p1, p2, p3);

    SUBCASE("Initialization") {
        CHECK(catan.getPlayers().size() == 3);
    }

    SUBCASE("Initializing Development Cards") {
        catan.initializeDevelopmentCard();
        CHECK(catan.getDevelopmentCards().size() == 25); // Assuming there are 25 development cards
    }

    SUBCASE("Choosing Starting Player") {
        std::string startingPlayer = catan.ChooseStartingPlayer();
        CHECK((startingPlayer == "Alice" || startingPlayer == "Bob" || startingPlayer == "Charlie"));
    }

    SUBCASE("Getting Development Card") {
        std::string card = catan.getDevelopmentCard();
        CHECK(!card.empty()); // Assuming a card is drawn if the deck is not empty
    }

    SUBCASE("Using Knight Card") {
        bool result = catan.Knight("wood", 6, true);
        CHECK(result); // Assuming the function returns true on success
    }

    SUBCASE("Printing Winner") {
        bool hasWinner = catan.printWinner();
        CHECK(!hasWinner); // Initially there should be no winner
    }

}

TEST_CASE("Development Card Functionality") {
    Player p1("Alice");
    Player p2("Bob");
    Player p3("Charlie");

    Catan catan(p1, p2, p3);
    catan.initializeDevelopmentCard();

    SUBCASE("Drawing Cards") {
        for (int i = 0; i < 25; ++i) {
            CHECK(!catan.getDevelopmentCard().empty());
        }
        CHECK(catan.getDevelopmentCard().empty()); // Deck should be empty now
    }

    SUBCASE("Using Knight Card") {
        std::string card = catan.getDevelopmentCard();
        if (card == "Knight") {
            bool result = catan.Knight("wood", 6, true);
            CHECK(result);
        }
    }
}

TEST_CASE("Player Class") {
    Player player("Alice");

    SUBCASE("Initialization") {
        CHECK(player.getName() == "Alice");
        CHECK(player.getPoints() == 0);
        CHECK(player.getKnights() == 0);
    }

    SUBCASE("Placing Settlements") {
        Board board;
        player.placeSettelemnt(board);
        CHECK(board.getSettlements().size() == 1); // Assuming there's a way to get the number of settlements
    }

    SUBCASE("Rolling Dice") {
        Board board;
        Catan catan(player, player, player);
        player.rollDice(catan, board);
    }

    SUBCASE("Placing Roads") {
        Board board;
        player.placeRoad(board);
    }

    SUBCASE("Buying Development Cards") {
        Board board;
        Catan catan(player, player, player);
        player.buyDevelopmentCard(catan);
        CHECK(player.getDevelopment().size() == 1); // Assuming there's a way to get the number of dev cards
    }


    SUBCASE("Trading with Other Player") {
        Player other("Bob");
        player.trade(other);
    }

    SUBCASE("Using Development Cards") {
        Board board;
        Catan catan(player, player, player);
        player.useDevelopmentCard(catan, board);
    }

    SUBCASE("Setting Turn") {
        player.setTurn();
        CHECK(player.isTurn());
    }

    SUBCASE("Ending Turn") {
        player.endTurn();
        CHECK(!player.isTurn());
    }
}


TEST_CASE("Game Flow") {
    Player p1("Alice");
    Player p2("Bob");
    Player p3("Charlie");

    Catan catan(p1, p2, p3);

    SUBCASE("Initial Setup") {
        catan.ChooseStartingPlayer();
        Board& board = catan.getBoard();
        
        p1.placeSettelemnt(board);
        p2.placeSettelemnt(board);
        p3.placeSettelemnt(board);
        CHECK(board.getSettlements().size() == 3);

        p1.placeSettelemnt(board);
        p2.placeSettelemnt(board);
        p3.placeSettelemnt(board);
        CHECK(board.getSettlements().size() == 6);
    }

    SUBCASE("Rolling Dice and Resource Distribution") {
        Board& board = catan.getBoard();
        for (auto player : catan.getPlayers()) {
            player->setTurn();
            player->rollDice(catan, board);
            player->endTurn();
        }
    }

    SUBCASE("Buying and Using Development Cards") {
        p1.setTurn();
        p1.buyDevelopmentCard(catan);
        p1.useDevelopmentCard(catan, catan.getBoard());
        p1.endTurn();

        CHECK(!p1.getDevelopment().empty());
    }

    SUBCASE("Trading Between Players") {
        p1.setTurn();
        p1.trade(p2);
        p1.endTurn();
    }

    SUBCASE("End Game Conditions") {
        p1.setPoints(10);
        CHECK(catan.printWinner());
    }
}