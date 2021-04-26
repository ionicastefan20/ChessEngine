#include "Logger.h"

#include "Board.h"

extern int board::botColor;

namespace logger {
    std::ofstream logger;
}

void logger::init() {
    std::string s1 = (board::botColor == piece::WHITE) ? "white" : "black";
    std::string s2 = "_out";
    logger::logger.open(s1 + s2, std::ofstream::app);
    logger::logger << s1 + " bot" << std::endl << std::endl;
}

void logger::log(std::string tag, std::string msg, int indent) {
    for (int i = 0; i < indent; ++i)
        logger::logger << "\t";
    logger::logger << "[" << tag << "]: " << msg << std::endl;
}

void logger::close() {
    logger::logger.close();
}