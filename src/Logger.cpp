#include "Logger.h"

extern int board::botColor;
extern int board::squares[64];

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

void logger::logBoard(int squares[]) {

    logger::logger << std::endl << "  |";
    for (int i = 0; i < 25; ++i)
        logger::logger << "-";
    logger::logger << "|" << std::endl;

    for (int i = 7; i >= 0; --i) {
        logger::logger << i+1 << " | ";
        for (int j = 0; j < 8; ++j) {
            std::string color = (squares[i*8+j] & piece::WHITE) ? "w" : "b";

            switch (squares[i*8+j] & 0x7) {
                case piece::PAWN:
                    logger::logger << color + "P ";
                    break;
                case piece::ROOK:
                    logger::logger << color + "R ";
                    break;
                case piece::KNIGHT:
                    logger::logger << color + "N ";
                    break;
                case piece::BISHOP:
                    logger::logger << color + "B ";
                    break;
                case piece::QUEEN:
                    logger::logger << color + "Q ";
                    break;
                case piece::KING:
                    logger::logger << color + "K ";
                    break;
                default:
                    logger::logger << "-- ";
                    break;
            }
        }

        logger::logger << "|" << std::endl;
    }

    logger::logger << "  |";
    for (int i = 0; i < 25; ++i)
        logger::logger << "-";
    logger::logger << "|" << std::endl << "   ";
    for (int i = 0; i < 8; ++i)
        logger::logger << "  " + std::string(1, 'a'+i);
    logger::logger << std::endl << std::endl;
}

void logger::logBoard2(std::vector<bool> squaresAttacked) {

    logger::logger << std::endl << "  |";
    for (int i = 0; i < 25; ++i)
        logger::logger << "-";
    logger::logger << "|" << std::endl;

    for (int i = 7; i >= 0; --i) {
        logger::logger << i+1 << " | ";
        for (int j = 0; j < 8; ++j) {
            logger::logger << squaresAttacked[i*8+j] << " ";
        }

        logger::logger << "|" << std::endl;
    }

    logger::logger << "  |";
    for (int i = 0; i < 25; ++i)
        logger::logger << "-";
    logger::logger << "|" << std::endl << "   ";
    for (int i = 0; i < 8; ++i)
        logger::logger << "  " + std::string(1, 'a'+i);
    logger::logger << std::endl << std::endl;
}

void logger::close() {
    logger::logger.close();
}