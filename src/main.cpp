#include <iostream>
#include <string>
#include <fstream>
#include <functional>
#include <vector>
#include <unordered_map>

class ReadInput {

    std::vector <std::string> commands

    bool isChessBoardNumber(char c) {
        return (49 <= c) && (56 >= c);
    }

    bool isChessBoardLetter(char c) {
        return (97 <= c) && (104 >= c);
    }

    bool isValidMove(std::string move) {
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

        while (true) {
            std::string input;
            getline(std::cin, input);
            std::string first_word = input.substr(0, input.find(" "));

            if (first_word.compare(commands[0])) {
                std::cout << std::endl;
                std::cout.flush();
            } else if (first_word.compare(commands[1])) {
                std::cout << std::endl;
                std::cout.flush();
            } else if (first_word.compare(commands[2])) {
                // TODO: Initialize new board
            } else if (first_word.compare(commands[3])) {
                // TODO: Stop the bot from playing and halt
            } else if (first_word.compare(commands[4])) {
                // TODO: Force the bot to play a move and continue thinking
            } else if (first_word.compare(commands[5])) {
                // end the function
                return;
            } else if (isValidMove(first_word)) {
                // TODO: Generate next move based on the move received from the xboard
            }
        }
    }
};

int main() {

    reader.readInput();
}