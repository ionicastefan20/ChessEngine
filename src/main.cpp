#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "Board.h"
#include "Move.h"
#include "MoveGenerator.h"

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
        std::ofstream fout1("out1", std::ofstream::app);
        for (int i = 7; i >= 0; i--) {
            for (int j = 0; j < 8; j++)
                fout1 << board::squares[8 * i + j] << " ";
            fout1 << std::endl;
        }


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
                board::makeMove(move_str);
                // fout1 << "very after\n";
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
        std::ofstream fout3("out3", std::ofstream::app);

        while (true) {
            std::string input;
            std::getline(std::cin, input);
            std::string first_word = input.substr(0, input.find(" "));

            fout3 << first_word << " " << board::isPlaying << std::endl;
            if (!first_word.compare(commands[0])) { // xboard
                std::cout << std::endl;
            } else if (!first_word.compare(commands[1])) { // protover
                std::cout << "feature sigint=0 san=0 name=\"true_chess\" done=1" << std::endl;
            } else if (!first_word.compare(commands[2])) { // new
                board::initBoard();
            } else if (!first_word.compare(commands[3])) { // force
                board::isPlaying = false;
                // TODO: Stop the bot from playing and halt
            } else if (!first_word.compare(commands[4])) { // go
                board::isPlaying = true;
                board::botColor = board::colorOnMove;
                fout3 << "go: in" << std::endl;

                // if (board::colorOnMove & piece::WHITE)
                //     board::kingPos = board::whiteKingPos;
                // else
                //     board::kingPos = board::blackKingPos;

                makeBotThink();
                fout3 << "go: out" << std::endl;
                // TODO: Force the bot to play a move and continue thinking
            } else if (!first_word.compare(commands[5])) { // quit
                exit(0);
                // TODO: end the function, kill all
                return;
            } else if (isValidMove(first_word)) {
                fout3 << "move: " << first_word << std::endl;
                board::makeMove(first_word); // his move (computer's, oponent's)
                makeBotThink();
                fout3 << "move: out" << std::endl;
            }
        }
    }
};

int main() {
    // std::ofstream fout6("out6", std::ofstream::app);
    // fout6 << "amintrat" << std::endl;
    
    board::initBoard();
    move::initDistancesAndDirections();

    ReadInput reader;
    reader.readInput();
}