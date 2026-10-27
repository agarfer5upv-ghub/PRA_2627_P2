CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g
BIN = bin

all: check

$(BIN):
	mkdir -p $(BIN)

check: | $(BIN)
	$(CXX) $(CXXFLAGS) -x c++ -c Dict.h -o $(BIN)/Dict.o
	$(CXX) $(CXXFLAGS) -x c++ -c TableEntry.h -o $(BIN)/TableEntry.o
	$(CXX) $(CXXFLAGS) -x c++ -c BSNode.h -o $(BIN)/BSNode.o
	$(CXX) $(CXXFLAGS) -x c++ -c BSTree.h -o $(BIN)/BSTree.o
	$(CXX) $(CXXFLAGS) -x c++ -c HashTable.h -o $(BIN)/HashTable.o
	$(CXX) $(CXXFLAGS) -x c++ -c BSTreeDict.h -o $(BIN)/BSTreeDict.o

clean:
	rm -rf $(BIN) *.o *.gch *.pch

.PHONY: all check clean
