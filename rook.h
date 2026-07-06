#ifndef ROOK_H
#define ROOK_H

#include "figure.h"

class Rook : public Figure
{
public:
    Rook(Color color, int col, int row);

    QVector<QPoint> possibleMoves(const Board &board) const override;
    QString getImageName() const override;
    QString getTypeName() const override;
};

#endif // ROOK_H
