#include "figure.h"
#include "board.h"

Figure::Figure(Color color, int col, int row)
    : m_color(color), m_col(col), m_row(row)
{
}

Figure::~Figure()
{
}

Color Figure::getColor() const
{
    return m_color;
}

int Figure::getCol() const
{
    return m_col;
}

int Figure::getRow() const
{
    return m_row;
}

void Figure::setPosition(int col, int row)
{
    m_col = col;
    m_row = row;
}

bool Figure::isInsideBoard(int col, int row) const
{
    return col >= 0 && col <= 7 && row >= 0 && row <= 7;
}

bool Figure::tryAddMove(const Board &board, int col, int row, QVector<QPoint> &moves) const
{
    if (!isInsideBoard(col, row))
        return false;

    Figure *target = board.figureAt(col, row);

    if (target == nullptr) {
        moves.append(QPoint(col, row));
        return true;
    }

    if (target->getColor() != m_color)
        moves.append(QPoint(col, row));

    return false;
}
