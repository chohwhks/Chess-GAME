#ifndef KING_H
#define KING_H

#include "figure.h"

class King : public Figure
{
public:
    King(Color color, int col, int row);

    QVector<QPoint> possibleMoves(const Board &board) const override;
    QString getImageName() const override;
    QString getTypeName() const override;
};

#endif // KING_H
