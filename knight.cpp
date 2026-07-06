#include "knight.h"
#include "board.h"

Knight::Knight(Color color, int col, int row)
    : Figure(color, col, row)
{
}

QVector<QPoint> Knight::possibleMoves(const Board &board) const
{
    QVector<QPoint> moves;
    int offsets[8][2] = {
        {1,2},{2,1},{2,-1},{1,-2},
        {-1,-2},{-2,-1},{-2,1},{-1,2}
    };

    for (int i = 0; i < 8; i++)
        tryAddMove(board, m_col + offsets[i][0], m_row + offsets[i][1], moves);

    return moves;
}

QString Knight::getImageName() const
{
    return (m_color == Color::White) ? "w_knight" : "b_knight";
}

QString Knight::getTypeName() const
{
    return "knight";
}
