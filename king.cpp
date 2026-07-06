#include "king.h"
#include "board.h"

King::King(Color color, int col, int row)
    : Figure(color, col, row)
{
}

QVector<QPoint> King::possibleMoves(const Board &board) const
{
    QVector<QPoint> moves;
    int offsets[8][2] = {
        {1,0},{1,1},{0,1},{-1,1},
        {-1,0},{-1,-1},{0,-1},{1,-1}
    };

    for (int i = 0; i < 8; i++)
        tryAddMove(board, m_col + offsets[i][0], m_row + offsets[i][1], moves);

    return moves;
}

QString King::getImageName() const
{
    return (m_color == Color::White) ? "w_king" : "b_king";
}

QString King::getTypeName() const
{
    return "king";
}
