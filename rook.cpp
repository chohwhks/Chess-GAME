#include "rook.h"
#include "board.h"

Rook::Rook(Color color, int col, int row)
    : Figure(color, col, row)
{
}

QVector<QPoint> Rook::possibleMoves(const Board &board) const
{
    QVector<QPoint> moves;
    int directions[4][2] = { {1,0}, {-1,0}, {0,1}, {0,-1} };

    for (int d = 0; d < 4; d++) {
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

QString Rook::getImageName() const
{
    return (m_color == Color::White) ? "w_rook" : "b_rook";
}

QString Rook::getTypeName() const
{
    return "rook";
}
