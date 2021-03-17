CC=g++
CFLAGS=-Wall -Wextra
SRC_FOLDER=src/
EXE = target/main

.PHONY: run build

all: build run

build: main.o Piece.o Board.o
	$(CC) $^ -o $(EXE) $(CFLAGS)
	rm *.o

main.o: $(SRC_FOLDER)main.cpp
	$(CC) -c $^ -o $(TARGET_FOLDER)$@ $(CFLAGS)

Move.o: $(SRC_FOLDER)Move.cpp
	$(CC) -c $^ -o $(TARGET_FOLDER)$@ $(CFLAGS)

Piece.o: $(SRC_FOLDER)Piece.cpp
	$(CC) -c $^ -o $(TARGET_FOLDER)$@ $(CFLAGS)

Board.o: $(SRC_FOLDER)Board.cpp
	$(CC) -c $^ -o $(TARGET_FOLDER)$@ $(CFLAGS)

GeneratePawnMoves.o: $(SRC_FOLDER)GeneratePawnMoves.cpp
	$(CC) -c $^ -o $(TARGET_FOLDER)$@ $(CFLAGS)

run:
	./$(EXE)