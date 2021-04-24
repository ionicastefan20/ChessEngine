#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "Board.h"
#include "Move.h"
#include "MoveGenerator.h"

class ReadInput {

    std::vector<std::string> commands;

    bool isChessBoardNumber(char c) {
        return (49 <= c) && (56 >= c);
    }

    bool isChessBoardLetter(char c) {
        return (97 <= c) && (104 >= c);
    }

    bool isValidMove(string move) {
        if (move.size() != 4)
            return false;

        if (isChessBoardLetter(move[0]) &&
            isChessBoardNumber(move[1]) &&
            isChessBoardLetter(move[2]) &&
            isChessBoardNumber(move[3]))
            return true;

        return false;
    }

    void makeBotThink() {
        if (Board::isPlaying) {
            // Replace
            pair<int, int> move = MoveGenerator::generateMove();

            if (move.first == -1 && move.second == -1)
                std::cout << "resign" << std::endl;
            else {
                string move_str = Board::encodeMove(move);
                std::cout << "move " << move_str << std::endl;
                Board::makeMove(move_str);
            }
        }
    }

public:

    ReadInput() {
        commands.push_back("xboard");
        commands.push_back("protover");
        commands.push_back("new");
        commands.push_back("force");
        commands.push_back("go");
        commands.push_back("quit");
    }

    void readInput() {

        while (true) {
            string input;
            std::getline(std::cin, input);
            string first_word = input.substr(0, input.find(" "));

            if (!first_word.compare(commands[0])) { // xboard
                std::cout << std::endl;
            } else if (!first_word.compare(commands[1])) { // protover
                std::cout << "feature sigint=0 san=0 name=\"true_chess\" done=1" << std::endl;
            } else if (!first_word.compare(commands[2])) { // new
                Board::initBoard();
            } else if (!first_word.compare(commands[3])) { // force
                Board::isPlaying = false;
                // TODO: Stop the bot from playing and halt
            } else if (!first_word.compare(commands[4])) { // go
                Board::isPlaying = true;
                Board::botColor = Board::colorOnMove;
                makeBotThink();
                // TODO: Force the bot to play a move and continue thinking
            } else if (!first_word.compare(commands[5])) { // quit
                exit(0);
                // TODO: end the function, kill all
                return;
            } else if (isValidMove(first_word)) {
                Board::makeMove(first_word); // his move (computer's, oponent's)
                makeBotThink();
            }
        }
    }
};

int main() {
    Board::initBoard();
    Move::initDistancesAndDirections();

    ReadInput reader;
    reader.readInput();
}