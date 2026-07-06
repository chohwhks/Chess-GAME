#ifndef FIGUREITEM_H
#define FIGUREITEM_H

#include <QGraphicsPixmapItem>
#include "figure.h"

class FigureItem : public QGraphicsPixmapItem
{
public:
    FigureItem(Figure *figure, const QPixmap &pixmap);

    Figure* getFigure() const;

private:
    Figure *m_figure;
};

#endif // FIGUREITEM_H
