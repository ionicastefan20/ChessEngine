#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>

class ReadInput {

    std::unordered_map<std::string, int> commands;

public:

    ReadInput() {
        commands["xboard"] = 0;
        commands["protover"] = 1;
        commands["new"] = 2;
        commands["force"] = 3;
        commands["go"] = 4;
        commands["quit"] = 5;
    }

    void readInput() {

        while (true) {
            std::string input;
            getline(std::cin, input);

            switch (commands[input.substr(0, input.find(" "))]) {
                case 0: {
                    std::cout << std::endl;
                    std::cout.flush();
                    break;
                }
                case 1: {
                    std::cout << "feature sigint=0 san=0 name=\"chess\"" << std::endl;
                    std::cout.flush();
                    break;
                }
                case 2: {
                    // TODO: Initialize new board
                    break;
                }
                case 3: {
                    // TODO: Stop the bot from playing and halt
                    break;
                }
                case 4: {
                    // TODO: Force the bot to play a move and continue thinking
                    break;
                }
                case 5: { // end the program
                    return;
                }
                default: {
                    std::cout << "move a7a5" << std::endl;
                    std::cout.flush();
                    break;
                }
            }
        }
    }
};

int main() {

    reader.readInput();
}