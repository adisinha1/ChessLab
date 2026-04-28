#include "PawnPiece.hh"
#include "ChessBoard.hh"

using Student::PawnPiece;

PawnPiece::PawnPiece(ChessBoard &board, Color color, int row, int column)
    : ChessPiece(board, color, row, column)
{
    type = Pawn;
}

bool PawnPiece::canMoveToLocation(int toRow, int toColumn)
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

    int direction = (color == Black) ? 1 : -1;

    int startRow = (color == Black) ? 1 : (board.getNumRows() - 2);

    int rowDiff = toRow - fromRow;
    int colDiff = toColumn - fromCol;

    if (colDiff == 1 || colDiff == -1)
    {
        if (rowDiff == direction)
        {
            return (dest != nullptr && dest->getColor() != color);
        }
        return false;
    }

    if (colDiff != 0)
        return false;

    if (rowDiff == direction)
    {
        return (dest == nullptr);
    }

    if (rowDiff == 2 * direction && fromRow == startRow)
    {
        ChessPiece *intermediate = board.getPiece(fromRow + direction, fromCol);
        return (dest == nullptr && intermediate == nullptr);
    }

    return false;
}

const char *PawnPiece::toString()
{
    return (color == White) ? "\u2659" : "\u265F";
}