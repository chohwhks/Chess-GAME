#include "queen.h"
#include "board.h"

Queen::Queen(Color color, int col, int row)
    : Figure(color, col, row)
{
}

QVector<QPoint> Queen::possibleMoves(const Board &board) const
{
    QVector<QPoint> moves;
    int directions[8][2] = {
        {1,0},{-1,0},{0,1},{0,-1},
        {1,1},{1,-1},{-1,1},{-1,-1}
    };

    for (int d = 0; d < 8; d++) {
        int col = m_col;
        int row = m_row;
        while (true) {
            col += directions[d][0];
            row += directions[d][1];
            if (!tryAddMove(board, col, row, moves))
                break;
        }
    }

    return moves;
}

QString Queen::getImageName() const
{
    return (m_color == Color::White) ? "w_queen" : "b_queen";
}

QString Queen::getTypeName() const
{
    return "queen";
}
