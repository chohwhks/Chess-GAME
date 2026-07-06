#include "figureitem.h"

FigureItem::FigureItem(Figure *figure, const QPixmap &pixmap)
    : QGraphicsPixmapItem(pixmap), m_figure(figure)
{
}

Figure* FigureItem::getFigure() const
{
    return m_figure;
}
