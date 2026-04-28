#include "BishopPiece.hh"
#include "ChessBoard.hh"
#include <cstdlib>

using Student::BishopPiece;

BishopPiece::BishopPiece(ChessBoard &board, Color color, int row, int column)
    : ChessPiece(board, color, row, column)
{
    type = Bishop;
}

bool BishopPiece::canMoveToLocation(int toRow, int toColumn)
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

    int rowDiff = toRow - fromRow;
    int colDiff = toColumn - fromCol;

    if (std::abs(rowDiff) != std::abs(colDiff))
        return false;

    int rowStep = (rowDiff > 0) ? 1 : -1;
    int colStep = (colDiff > 0) ? 1 : -1;

    int r = fromRow + rowStep;
    int c = fromCol + colStep;
    while (r != toRow && c != toColumn)
    {
        if (board.getPiece(r, c) != nullptr)
            return false;
        r += rowStep;
        c += colStep;
    }

    return true;
}

const char *BishopPiece::toString()
{
    return (color == White) ? "\u2657" : "\u265D";
}