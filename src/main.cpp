#include <vector>
using std::vector;

#include <string>
using std::string;

#include <fstream>
using std::ofstream;

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include "Board.h"
#include "Move.h"
#include "GeneratePawnMoves.h"

class ReadInput {

    vector <string> commands;

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
        ofstream my_file;
        my_file.open("debug");
        std::ofstream fout3("output3.txt");

        my_file << "Starting" << endl;
        while (true) {
            string input;
            getline(cin, input);
            string first_word = input.substr(0, input.find(" "));


            if (!first_word.compare(commands[0])) { // xboard
                my_file << "why" << endl;
                cout << endl;
            } else if (!first_word.compare(commands[1])) { // protover
                cout << "feature sigint=0 san=0 name=\"true_chess\" done=1" << endl;
            } else if (!first_word.compare(commands[2])) { // new
                Board::initBoard();
            } else if (!first_word.compare(commands[3])) { // force
                // TODO: Stop the bot from playing and halt
            } else if (!first_word.compare(commands[4])) { // go
                // TODO: Force the bot to play a move and continue thinking
            } else if (!first_word.compare(commands[5])) { // quit
                // TODO: end the function, kill all
                return;
            } else if (isValidMove(first_word)) {
                fout3 << first_word << endl;
                Board::makeMove(first_word); // his move (computer's, oponent's)
                pair<int, int> ceva = GeneratePawnMoves::generatePawnMove();
                fout3 << "primu: " << ceva.first << " doi: " << ceva.second << endl;
                cout << "move " + Board::encodeMove(ceva) << endl;
                // string c = first_word.substr(0, 1);
                // cout << "move " + c + "7" + c + "5" << endl;
                // TODO: Generate next move based on the move received from the xboard
            }
        }
        fout3.close();
        my_file.close();
    }
};

int main() {
    Board::initBoard();
    Move::initDistancesAndDirections();

    ReadInput reader;
    reader.readInput();
}