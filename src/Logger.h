#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <string>

namespace logger {
    extern std::ofstream logger;

    void init();
    void log(std::string tag, std::string msg, int indent);
    void logBoard();
    void close();
}

#endif
