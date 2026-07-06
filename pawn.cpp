#include "pawn.h"
#include "board.h"

Pawn::Pawn(Color color, int col, int row)
    : Figure(color, col, row)
{
}

QVector<QPoint> Pawn::possibleMoves(const Board &board) const
{
    QVector<QPoint> moves;
    int direction = (m_color == Color::White) ? 1 : -1;
    int startRow = (m_color == Color::White) ? 1 : 6;

    int oneStepRow = m_row + direction;
    if (isInsideBoard(m_col, oneStepRow) && board.figureAt(m_col, oneStepRow) == nullptr) {
        moves.append(QPoint(m_col, oneStepRow));

        int twoStepRow = m_row + direction * 2;
        if (m_row == startRow && board.figureAt(m_col, twoStepRow) == nullptr)
            moves.append(QPoint(m_col, twoStepRow));
    }

    int captureCols[2] = { m_col - 1, m_col + 1 };
    for (int i = 0; i < 2; i++) {
        int captureCol = captureCols[i];
        if (!isInsideBoard(captureCol, oneStepRow))
            continue;

        Figure *target = board.figureAt(captureCol, oneStepRow);
        if (target != nullptr && target->getColor() != m_color)
            moves.append(QPoint(captureCol, oneStepRow));
    }

    return moves;
}

QString Pawn::getImageName() const
{
    return (m_color == Color::White) ? "w_pawn" : "b_pawn";
}

QString Pawn::getTypeName() const
{
    return "pawn";
}
