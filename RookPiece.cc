#include "RookPiece.hh"
#include "ChessBoard.hh"

using Student::RookPiece;

RookPiece::RookPiece(ChessBoard &board, Color color, int row, int column)
    : ChessPiece(board, color, row, column)
{
    type = Rook;
}

bool RookPiece::canMoveToLocation(int toRow, int toColumn)
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

    bool sameRow = (toRow == fromRow);
    bool sameCol = (toColumn == fromCol);

    if (!sameRow && !sameCol)
        return false;

    if (sameRow)
    {
        int colStep = (toColumn > fromCol) ? 1 : -1;
        for (int c = fromCol + colStep; c != toColumn; c += colStep)
        {
            if (board.getPiece(fromRow, c) != nullptr)
                return false;
        }
    }
    else
    {
        int rowStep = (toRow > fromRow) ? 1 : -1;
        for (int r = fromRow + rowStep; r != toRow; r += rowStep)
        {
            if (board.getPiece(r, fromCol) != nullptr)
                return false;
        }
    }

    return true;
}

const char *RookPiece::toString()
{
    return (color == White) ? "\u2656" : "\u265C";
}