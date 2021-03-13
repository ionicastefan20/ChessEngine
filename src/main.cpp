#include "Piece.h"
#include "Board.h"
#include "dependencies.h"

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

        my_file << "Starting" << std::endl;
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
                // TODO: Initialize new board
            } else if (!first_word.compare(commands[3])) { // force
                // TODO: Stop the bot from playing and halt
            } else if (!first_word.compare(commands[4])) { // go
                // TODO: Force the bot to play a move and continue thinking
            } else if (!first_word.compare(commands[5])) { // quit
                // TODO: end the function, kill all
                return;
            } else if (isValidMove(first_word)) {
                string c = first_word.substr(0, 1);
                cout << "move " + c + "7" + c + "5" << endl;
                // TODO: Generate next move based on the move received from the xboard
            }
        }

        my_file.close();
    }
};

int main() {
    Board b;
    b.initBoard();

    ReadInput reader;
    reader.readInput();
}