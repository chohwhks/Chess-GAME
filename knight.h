#ifndef KNIGHT_H
#define KNIGHT_H

#include "figure.h"

class Knight : public Figure
{
public:
    Knight(Color color, int col, int row);

    QVector<QPoint> possibleMoves(const Board &board) const override;
    QString getImageName() const override;
    QString getTypeName() const override;
};

#endif // KNIGHT_H
