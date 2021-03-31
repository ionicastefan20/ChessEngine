CC=g++
CFLAGS=-Wall -Wextra
SRC_FOLDER=src/
EXE=main

SRCS=$(wildcard $(SRC_FOLDER)*.cpp)
OBJECTS=$(SRCS:.cpp=.o)

.PHONY: run build clean

all: build

build: $(OBJECTS)
	$(CC) $^ -o $(EXE) $(CFLAGS)

%.o: $(SRC_FOLDER)%.cpp
	$(CC) -MMD -MP -c $< -o $@ $(CFLAGS)

run:
	./$(EXE)

clean:
	rm -f $(SRC_FOLDER)*.o main 2> /dev/null
