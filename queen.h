#ifndef QUEEN_H
#define QUEEN_H

#include "figure.h"

class Queen : public Figure
{
public:
    Queen(Color color, int col, int row);

    QVector<QPoint> possibleMoves(const Board &board) const override;
    QString getImageName() const override;
    QString getTypeName() const override;
};

#endif // QUEEN_H
