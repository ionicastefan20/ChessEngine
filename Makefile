CC=g++
CFLAGS=-Wall -Wextra
SRC_FOLDER=src/
EXE=target/main

SRCS=$(wildcard $(SRC_FOLDER)*.cpp)
OBJECTS=$(SRCS:.cpp=.o)

.PHONY: run build clean

all: build clean

build: $(OBJECTS)
	$(CC) $^ -o $(EXE) $(CFLAGS)

%.o: $(SRC_FOLDER)%.cpp
	$(CC) -MMD -MP -c $< -o $(TARGET_FOLDER)$@ $(CFLAGS)

run:
	./$(EXE)

clean:
	rm $(SRC_FOLDER)*.o