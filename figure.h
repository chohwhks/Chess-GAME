#ifndef FIGURE_H
#define FIGURE_H

#include <QString>
#include <QVector>
#include <QPoint>

class Board;

enum class Color { White, Black };

class Figure
{
public:
    Figure(Color color, int col, int row);
    virtual ~Figure();

    Color getColor() const;
    int getCol() const;
    int getRow() const;
    void setPosition(int col, int row);

    virtual QVector<QPoint> possibleMoves(const Board &board) const = 0;
    virtual QString getImageName() const = 0;
    virtual QString getTypeName() const = 0;

protected:
    Color m_color;
    int m_col;
    int m_row;

    bool isInsideBoard(int col, int row) const;
    bool tryAddMove(const Board &board, int col, int row, QVector<QPoint> &moves) const;
};

#endif // FIGURE_H
