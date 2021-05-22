#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <string>
#include "Move.h"
#include "Board.h"

namespace logger {
    extern std::ofstream logger;

    void init();
    void log(std::string tag, std::string msg, int indent);
    void logBoard(int squares[]);
    void close();
    void logBoard2();
}

#endif
