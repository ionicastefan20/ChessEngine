EXE = target/main

build: main.o Piece.o
	g++ target/main.o target/Piece.o -o $(EXE) -Wall -Wextra

main.o:
	g++ -c src/main.cpp -o target/main.o -Wall -Wextra

Piece.o:
	g++ -c src/Piece.cpp -o target/Piece.o -Wall -Wextra

run:
	./target/main