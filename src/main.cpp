#include <iostream>
#include <string>
#include <unordered_map>

class ReadInput {

    std::unordered_map<std::string, int> commands;

public:

    ReadInput() {
        commands["xboard"] = 0;
        commands["protover"] = 1;
        commands["feature"] = 2;
        commands["a2a4"] = 3;
    }

    void readInput() {
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
            default: {
                std::cout << "move a7a6" << std::endl;
            }
        }
    }
};

int main() {

    ReadInput reader;
    reader.readInput();

}