#include "ChessBoard.hh"
#include "PawnPiece.hh"
#include "RookPiece.hh"
#include "BishopPiece.hh"
#include "KingPiece.hh"

using Student::ChessBoard;

ChessBoard::ChessBoard(int numRow, int numCol)
    : numRows(numRow), numCols(numCol), turn(White)
{
    board = std::vector<std::vector<ChessPiece *>>(
        numRows, std::vector<ChessPiece *>(numCols, nullptr));
}
ChessBoard::~ChessBoard()
{
    for (int r = 0; r < numRows; r++)
        for (int c = 0; c < numCols; c++)
            if (board.at(r).at(c) != nullptr)
            {
                delete board.at(r).at(c);
                board.at(r).at(c) = nullptr;
            }
}
void ChessBoard::createChessPiece(Color col, Type ty, int startRow, int startColumn)
{
    if (board.at(startRow).at(startColumn) != nullptr)
    {
        delete board.at(startRow).at(startColumn);
        board.at(startRow).at(startColumn) = nullptr;
    }

    ChessPiece *newPiece = nullptr;
    switch (ty)
    {
    case Pawn:
        newPiece = new PawnPiece(*this, col, startRow, startColumn);
        break;
    case Rook:
        newPiece = new RookPiece(*this, col, startRow, startColumn);
        break;
    case Bishop:
        newPiece = new BishopPiece(*this, col, startRow, startColumn);
        break;
    case King:
        newPiece = new KingPiece(*this, col, startRow, startColumn);
        break;
    }

    board.at(startRow).at(startColumn) = newPiece;
}
Student::ChessPiece *ChessBoard::findKing(Color color)
{
    for (int r = 0; r < numRows; r++)
        for (int c = 0; c < numCols; c++)
        {
            ChessPiece *piece = board.at(r).at(c);
            if (piece != nullptr && piece->getColor() == color && piece->getType() == King)
                return piece;
        }
    return nullptr;
}
bool ChessBoard::isValidMove(int fromRow, int fromColumn, int toRow, int toColumn)
{
    if (fromRow < 0 || fromRow >= numRows || fromColumn < 0 || fromColumn >= numCols)
        return false;
    if (toRow < 0 || toRow >= numRows || toColumn < 0 || toColumn >= numCols)
        return false;

    ChessPiece *piece = board.at(fromRow).at(fromColumn);
    if (piece == nullptr)
        return false;

    if (!piece->canMoveToLocation(toRow, toColumn))
        return false;

    ChessPiece *captured = board.at(toRow).at(toColumn);
    board.at(toRow).at(toColumn) = piece;
    board.at(fromRow).at(fromColumn) = nullptr;
    piece->setPosition(toRow, toColumn);

    ChessPiece *king = findKing(piece->getColor());
    bool inCheck = false;
    if (king != nullptr)
        inCheck = isPieceUnderThreat(king->getRow(), king->getColumn());

    board.at(fromRow).at(fromColumn) = piece;
    board.at(toRow).at(toColumn) = captured;
    piece->setPosition(fromRow, fromColumn);

    return !inCheck;
}
bool ChessBoard::movePiece(int fromRow, int fromColumn, int toRow, int toColumn)
{
    if (fromRow < 0 || fromRow >= numRows || fromColumn < 0 || fromColumn >= numCols)
        return false;
    if (toRow < 0 || toRow >= numRows || toColumn < 0 || toColumn >= numCols)
        return false;

    ChessPiece *piece = board.at(fromRow).at(fromColumn);
    if (piece == nullptr)
        return false;

    if (piece->getColor() != turn)
        return false;

    if (!isValidMove(fromRow, fromColumn, toRow, toColumn))
        return false;

    if (board.at(toRow).at(toColumn) != nullptr)
    {
        delete board.at(toRow).at(toColumn);
        board.at(toRow).at(toColumn) = nullptr;
    }

    board.at(toRow).at(toColumn) = piece;
    board.at(fromRow).at(fromColumn) = nullptr;
    piece->setPosition(toRow, toColumn);

    turn = (turn == White) ? Black : White;

    return true;
}

bool ChessBoard::isPieceUnderThreat(int row, int column)
{
    ChessPiece *piece = board.at(row).at(column);
    if (piece == nullptr)
        return false;

    Color opponentColor = (piece->getColor() == White) ? Black : White;

    for (int r = 0; r < numRows; r++)
        for (int c = 0; c < numCols; c++)
        {
            ChessPiece *attacker = board.at(r).at(c);
            if (attacker == nullptr)
                continue;
            if (attacker->getColor() != opponentColor)
                continue;
            if (attacker->canMoveToLocation(row, column))
                return true;
        }

    return false;
}

std::ostringstream ChessBoard::displayBoard()
{
    std::ostringstream outputString;
    // top scale
    outputString << "  ";
    for (int i = 0; i < numCols; i++)
    {
        outputString << i << " ";
    }
    outputString << std::endl
                 << "  ";
    // top border
    for (int i = 0; i < numCols; i++)
    {
        outputString << "– ";
    }
    outputString << std::endl;

    for (int row = 0; row < numRows; row++)
    {
        outputString << row << "|";
        for (int column = 0; column < numCols; column++)
        {
            ChessPiece *piece = board.at(row).at(column);
            outputString << (piece == nullptr ? " " : piece->toString()) << " ";
        }
        outputString << "|" << std::endl;
    }

    // bottom border
    outputString << "  ";
    for (int i = 0; i < numCols; i++)
    {
        outputString << "– ";
    }
    outputString << std::endl
                 << std::endl;

    return outputString;
}
