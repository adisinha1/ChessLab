#include "KingPiece.hh"
#include "ChessBoard.hh"
#include <cstdlib>

using Student::KingPiece;

KingPiece::KingPiece(ChessBoard &board, Color color, int row, int column)
    : ChessPiece(board, color, row, column)
{
    type = King;
}

bool KingPiece::canMoveToLocation(int toRow, int toColumn)
{
    int fromRow = this->row;
    int fromCol = this->column;

    if (toRow == fromRow && toColumn == fromCol)
        return false;

    if (toRow < 0 || toRow >= board.getNumRows() ||
        toColumn < 0 || toColumn >= board.getNumCols())
        return false;

    ChessPiece *dest = board.getPiece(toRow, toColumn);
    if (dest != nullptr && dest->getColor() == color)
        return false;

    int rowDiff = std::abs(toRow - fromRow);
    int colDiff = std::abs(toColumn - fromCol);

    return (rowDiff <= 1 && colDiff <= 1);
}

const char *KingPiece::toString()
{
    return (color == White) ? "\u2654" : "\u265A";
}