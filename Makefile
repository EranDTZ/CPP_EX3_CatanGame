CXX = clang++
CXXFLAGS = -std=c++11 -I.

# Object files
OBJ = main.o catan.o player.o board.o
TEST_OBJ = test.o catan.o player.o board.o
DEMO_OBJ = Demo.o catan.o player.o board.o

# Targets
all: game test Demo

game: $(OBJ)
	$(CXX) $(CXXFLAGS) -o game $(OBJ)

test: $(TEST_OBJ)
	$(CXX) $(CXXFLAGS) -o test $(TEST_OBJ)

Demo: $(DEMO_OBJ)
	$(CXX) $(CXXFLAGS) -o Demo $(DEMO_OBJ)

main.o: main.cpp catan.hpp player.hpp board.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

catan.o: catan.cpp catan.hpp
	$(CXX) $(CXXFLAGS) -c catan.cpp

player.o: player.cpp player.hpp
	$(CXX) $(CXXFLAGS) -c player.cpp

board.o: board.cpp board.hpp
	$(CXX) $(CXXFLAGS) -c board.cpp

test.o: test.cpp catan.hpp player.hpp board.hpp
	$(CXX) $(CXXFLAGS) -c test.cpp

Demo.o: Demo.cpp catan.hpp player.hpp board.hpp
	$(CXX) $(CXXFLAGS) -c Demo.cpp

clean:
	rm -f *.o game test Demo

# Run the game
play: game
	./game

# Run the Demo
catan: Demo
	./Demo
