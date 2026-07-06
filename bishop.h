#ifndef BISHOP_H
#define BISHOP_H

#include "figure.h"

class Bishop : public Figure
{
public:
    Bishop(Color color, int col, int row);

    QVector<QPoint> possibleMoves(const Board &board) const override;
    QString getImageName() const override;
    QString getTypeName() const override;
};

#endif // BISHOP_H
