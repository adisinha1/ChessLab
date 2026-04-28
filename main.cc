#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Chess.h"
#include "ChessBoard.hh"
#include "ChessPiece.hh"

std::string stripComments(const std::string &line)
{
    size_t commentPos = line.find("//");
    std::string stripped = (commentPos != std::string::npos) ? line.substr(0, commentPos) : line;
    while (!stripped.empty() && std::isspace(stripped.back()))
        stripped.pop_back();
    return stripped;
}

void runConfigFile(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Could not open file: " << filename << std::endl;
        return;
    }

    std::string line;

    // First line: score (ignore)
    std::getline(file, line);

    // Second line: board dimensions
    int numRows, numCols;
    file >> numRows >> numCols;
    file.ignore();

    Student::ChessBoard board(numRows, numCols);

    // Read piece placements until '~'
    while (std::getline(file, line))
    {
        line = stripComments(line);
        if (line.empty())
            continue;
        if (line == "~")
            break;

        std::istringstream ss(line);
        char colorChar, typeChar;
        int row, col;
        ss >> colorChar >> typeChar >> row >> col;

        Color color = (colorChar == 'w') ? White : Black;
        Type type;
        if (typeChar == 'r')
            type = Rook;
        else if (typeChar == 'b')
            type = Bishop;
        else if (typeChar == 'p')
            type = Pawn;
        else
            type = King;

        board.createChessPiece(color, type, row, col);
    }

    // Execute commands after '~'
    while (std::getline(file, line))
    {
        line = stripComments(line);
        if (line.empty())
            continue;

        std::istringstream ss(line);
        std::string command;
        ss >> command;

        if (command == "isValidScan")
        {
            for (int fr = 0; fr < numRows; fr++)
                for (int fc = 0; fc < numCols; fc++)
                    for (int tr = 0; tr < numRows; tr++)
                        for (int tc = 0; tc < numCols; tc++)
                            std::cout << board.isValidMove(fr, fc, tr, tc) << "\n";
        }
        else if (command == "movePiece")
        {
            int fr, fc, tr, tc;
            ss >> fr >> fc >> tr >> tc;
            std::cout << board.movePiece(fr, fc, tr, tc) << "\n";
        }
        else if (command == "underThreatScan")
        {
            for (int r = 0; r < numRows; r++)
                for (int c = 0; c < numCols; c++)
                    std::cout << board.isPieceUnderThreat(r, c) << "\n";
        }
    }
}

int main(int argc, char **argv)
{
    for (int i = 1; i < argc; i++)
        runConfigFile(argv[i]);

    return EXIT_SUCCESS;
}