EXE = target/main

build:
	g++ src/main.cpp -o $(EXE) -Wall -Wextra

run:
	./target/main