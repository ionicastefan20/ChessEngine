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

run_ubuntu:
	rm -f *_out
	make build
	xboard -fcp "make run"

debug_ubuntu:
	rm -f *_out
	make build
	xboard -fcp "make run" -debug

run_wsl:
	rm -f *_out
	make build
	rm -f *_out && DISPLAY=:0 xboard -fcp "make run"

debug_wsl:
	rm -f *_out
	make build
	DISPLAY=:0 xboard -fcp "make run" -debug

clean:
	rm -f *_out xboard.debug
	rm -f $(SRC_FOLDER)*.o main

run_pulsar:
	rm -f *_out
	make build
	DISPLAY=:0 xboard -variant 3check -fcp "pulsar2009-9b-64 mxT-2" -scp "make run"
