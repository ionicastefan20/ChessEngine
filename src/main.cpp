#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "Board.h"
#include "Move.h"
#include "MoveGenerator.h"
#include "Logger.h"

extern int board::colorOnMove;
extern int board::botColor;
extern bool board::isPlaying;
extern int board::kingPos;
extern int board::whiteKingPos;
extern int board::blackKingPos;

extern std::unordered_map<std::string, int> move::directions;
extern std::vector<std::unordered_map<std::string, int>> move::numUntilEdge;
extern std::vector<bool> move::squaresAttacked;
extern std::unordered_map<int, std::vector<int>> move::moves;

class ReadInput {

    std::vector<std::string> commands;

    bool isChessBoardNumber(char c) {
        return (49 <= c) && (56 >= c);
    }

    bool isChessBoardLetter(char c) {
        return (97 <= c) && (104 >= c);
    }

    bool isValidMove(std::string move) {
        if (move.size() != 4 && move.size() != 5 )
            return false;

        if (isChessBoardLetter(move[0]) &&
            isChessBoardNumber(move[1]) &&
            isChessBoardLetter(move[2]) &&
            isChessBoardNumber(move[3])) // add condition for the 5-th char
            return true;

        return false;
    }

    void makeBotThink() {
        // std::string s1 = "out";
        // std::string s2 = (board::botColor & piece::WHITE) ? "White" : "Black";
        // std::ofstream fout1(s1 + s2, std::ofstream::app);
        // fout1 << "think: in: " << board::isPlaying << std::endl;
        if (board::isPlaying) {
            std::pair<std::string, std::pair<int, int>> move =
                                                moveGenerator::generateMove();

            if (move.second.first == -1 && move.second.second == -1)
                std::cout << "resign" << std::endl;
            else {
                // fout1 << "before: " << "white: " << board::whiteKingPos << " black: " << board::blackKingPos << std::endl;
                if (move.second.first == board::whiteKingPos)
                    board::whiteKingPos = move.second.second;
                if (move.second.first == board::blackKingPos)
                    board::blackKingPos = move.second.second;

                if (board::colorOnMove == piece::BLACK)
                    board::kingPos = board::blackKingPos;
                else
                    board::kingPos = board::whiteKingPos;

                // fout1 << "after: " << "white: " << board::whiteKingPos << " black: " << board::blackKingPos << std::endl;

                std::string move_str = board::encodeMove(move.second);
                std::cout << "move " << move_str + move.first << std::endl;
                // fout1 << "move " << move_str + move.first << std::endl;
                if (board::squares[move.second.first] == piece::PAWN) {
                    // fout1 << "yes i am a pawn" << std::endl;
                    // fout1 << (move.second.second - move.second.first) % 2 << " " << board::squares[move.second.second] << std::endl;
                    if (((move.second.second - move.second.first) % 2) &&
                            (board::squares[move.second.second] == 0)) {
                        // fout1 << "yes i am doing an en passant" << std::endl;
                        board::squares[move.second.second + 8 * ((board::botColor & piece::WHITE) ? -1 : 1)] = 0;
                    }
                }

                board::makeMove(move_str);

                logger::logBoard();
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
            // logger::init();

            std::string input;
            std::getline(std::cin, input);
            std::string first_word = input.substr(0, input.find(" "));

            if (!first_word.compare(commands[0])) { // xboard
                std::cout << std::endl;
            } else if (!first_word.compare(commands[1])) { // protover
                std::cout << "feature sigint=0 san=0 name=\"true_chess\" done=1" << std::endl;
            } else if (!first_word.compare(commands[2])) { // new
                board::initBoard();
            } else if (!first_word.compare(commands[3])) { // force
                board::isPlaying = false;
            } else if (!first_word.compare(commands[4])) { // go
                board::isPlaying = true;
                board::botColor = board::colorOnMove;

                logger::init();
                makeBotThink();
            } else if (!first_word.compare(commands[5])) { // quit
                exit(0);
                return;
            } else if (isValidMove(first_word)) {
                board::makeMove(first_word); // his move (computer's, oponent's)
                makeBotThink();
            }
        }
    }
};

int main() {
    board::initBoard();
    move::initDistancesAndDirections();

    ReadInput reader;
    reader.readInput();


    logger::close();
}