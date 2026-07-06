#ifndef PAWN_H
#define PAWN_H

#include "figure.h"

class Pawn : public Figure
{
public:
    Pawn(Color color, int col, int row);

    QVector<QPoint> possibleMoves(const Board &board) const override;
    QString getImageName() const override;
    QString getTypeName() const override;
};

#endif // PAWN_H
