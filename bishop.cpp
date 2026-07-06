#include "bishop.h"
#include "board.h"

Bishop::Bishop(Color color, int col, int row)
    : Figure(color, col, row)
{
}

QVector<QPoint> Bishop::possibleMoves(const Board &board) const
{
    QVector<QPoint> moves;
    int directions[4][2] = { {1,1}, {1,-1}, {-1,1}, {-1,-1} };

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

QString Bishop::getImageName() const
{
    return (m_color == Color::White) ? "w_bishop" : "b_bishop";
}

QString Bishop::getTypeName() const
{
    return "bishop";
}
