# Catan Game in C++

This project is a C++ implementation of the popular board game "Catan". This README provides an in-depth overview of the classes, functions, and their interactions within the game.

## Table of Contents
- [Overview](#overview)
- [Classes and Their Functions](#classes-and-their-functions)
  - [Catan Class](#catan-class)
  - [Board Class](#board-class)
  - [Player Class](#player-class)
- [Functionality](#functionality)
- [Interactions Between Classes](#interactions-between-classes)
- [How to Compile and Run](#how-to-compile-and-run)
- [Game Flow](#game-flow)
- [Command Guide](#command-guide)
- [Contributing](#contributing)
- [License](#license)

## Overview

This implementation of Catan simulates the main features of the game, including placing settlements, building roads, rolling dice, trading, and using development cards. The game supports three players and includes various classes to handle different aspects of the game: `Catan`, `Board`, and `Player`.

## Classes and Their Functions

### Catan Class

The `Catan` class manages the overall game state, including the players, the board, and development cards.

#### Members:
- **Board board**: The game board.
- **std::vector<Player*> players**: List of players in the game.
- **int currentPlayerIndex**: Index of the current player.
- **std::vector<std::string> DevelopmentCard**: Deck of development cards.

#### Methods:
- **Catan(Player& p1, Player& p2, Player& p3)**: Constructor that initializes the board, players, and shuffles the development cards.
- **void initializeDevelopmentCard()**: Initializes and shuffles the deck of development cards.
- **std::string ChooseStartingPlayer()**: Randomly selects and returns the starting player.
- **Board& getBoard()**: Returns the game board.
- **bool printWinner()**: Checks if any player has won the game and prints the winner.
- **std::vector<Player*> getPlayers() const**: Returns the list of players.
- **std::string getDevelopmentCard()**: Draws a development card from the deck.
- **bool Knight(std::string resource, int num, bool boo)**: Handles the knight card effect on specified resources and hexes.

### Board Class

The `Board` class represents the game board, including hexes and settlements.

#### Members:
- **std::vector<Settlement> settlements**: List of settlements on the board.

#### Methods:
- **Board()**: Constructor that initializes the board.
- **std::vector<Settlement>& getSettlements()**: Returns the list of settlements.
- **void Guide()**: Provides a guide to the board layout.
- **void ResourceGuide()**: Provides a guide to resource colors.
- **void settlementGuide()**: Provides a guide to resources connected to each settlement.

### Player Class

The `Player` class represents a player in the game.

#### Members:
- **std::string name**: The player's name.
- **int points**: The player's points.
- **int knights**: Number of knights the player has used.
- **bool turn**: Indicator of whether it's the player's turn.

#### Methods:
- **Player(std::string name)**: Constructor that initializes the player's name.
- **std::string getName() const**: Returns the player's name.
- **int getPoints() const**: Returns the player's points.
- **void setTurn()**: Sets the player's turn.
- **void endTurn()**: Ends the player's turn.
- **void placeSettelemnt(Board& board)**: Places a settlement on the board.
- **void rollDice(Catan& catan, Board& board)**: Simulates rolling dice and resource distribution.
- **void placeRoad(Board& board)**: Places a road on the board.
- **void buyDevelopmentCard(Catan& catan)**: Buys a development card.
- **void useDevelopmentCard(Catan& catan, Board& board)**: Uses a development card.
- **void bankTrade()**: Trades resources with the bank.
- **void printPoints() const**: Prints the player's points.
- **int getKnights() const**: Returns the number of knights used by the player.
- **void printCards() const**: Prints the player's resource cards.
- **void printSettlements() const**: Prints the player's settlements.
- **void printDevelopment() const**: Prints the player's development cards.
- **void myInfo() const**: Prints the player's information.
- **void trade(Player& other)**: Trades resources with another player.

## Functionality

### Game Initialization

The game is initialized by creating three `Player` objects and passing them to the `Catan` class. The `Catan` constructor initializes the board and players, shuffles the development cards, and randomly selects the starting player.

### Development Cards

The `initializeDevelopmentCard` method initializes a deck of development cards with predefined types (e.g., Knight, Point, Monopoly, Resources, Roads). The deck is then shuffled.

### Player Actions

Players can perform various actions during their turn:
- **Placing Settlements**: Players place settlements on the board.
- **Rolling Dice**: Players roll dice to collect resources.
- **Building Roads**: Players build roads on the board.
- **Trading**: Players trade resources with each other or with the bank.
- **Using Development Cards**: Players use development cards they have drawn.

### Checking for a Winner

The `printWinner` method checks if any player has reached the winning condition (10 points). If a player has won, their name is printed, and the game ends.

## Interactions Between Classes

- **Catan and Player**: The `Catan` class holds references to `Player` objects and manages the game flow by interacting with players.
- **Catan and Board**: The `Catan` class contains a `Board` object that represents the game board and its state.
- **Player and Board**: Players interact with the board to place settlements and roads, and to collect resources based on dice rolls.

## How to Compile and Run

### Requirements
- C++11 or later
- A C++ compiler (e.g., g++, clang++)

### Compilation
To compile the program, use the provided Makefile. In the terminal, navigate to the directory containing the source files and run:
```sh
make
```

### Running the Game
To run the game, execute the following command:
```sh
./game
```

To run the demo, execute:
```sh
./Demo
```

### Clean Up
To clean up the compiled files, run:
```sh
make clean
```

## Game Flow

1. **Initialize Players and Board**: The game starts by initializing three players and the board.
2. **Choose Starting Player**: A random player is selected to start the game.
3. **Place Initial Settlements and Roads**: Each player places two settlements and two roads.
4. **Turn-Based Actions**: Players take turns to roll dice, trade, build, and use development cards.
5. **Check for Winner**: After each turn, the game checks if any player has reached 10 points.
6. **End Game**: The game ends when a player reaches 10 points and is declared the winner.

## Command Guide

### General Commands:
- **use development** / **use card** / **use**: Activate a development card.
- **road**: Buy and place a road on the board.
- **set** / **sit**: Buy and place a settlement on the board.
- **buy development** / **buy card** / **buy**: Buy a development card.
- **bank**: Trade 4 of the same resource card for 1 different resource card.
- **points**: View your points and standing.
- **knights**: View the number of knights you have activated.
- **cards**: View your resource cards.
- **settlements**: View your settlements.
- **development**: View your development cards.
- **info**: View important information about all players.
- **trade**: Trade resources with another player.
- **board**: View the board layout.
- **resource**: View a resource color guide.
- **guide**: View a settlements guide of resources connected to settlements.
- **end**: End your turn.
- **commend**: View the command guide.

## Contributing

Contributions are welcome! Please fork this repository and submit a pull request with your changes.

