#ifndef BOARDWIDGET_H
#define BOARDWIDGET_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QVector>
#include <QTimer>
#include "board.h"
#include "figureitem.h"

class BoardWidget : public QGraphicsView
{
    Q_OBJECT

public:
    explicit BoardWidget(QWidget *parent = nullptr);
    ~BoardWidget();

    void newGame();
    bool loadFromFile(const QString &filePath);
    bool saveToFile(const QString &filePath) const;
    bool startMovesPlayback(const QString &filePath);
    bool startPositionAndMovesPlayback(const QString &positionPath, const QString &movesPath);

signals:
    void statusMessage(const QString &message);

protected:
    void mousePressEvent(QMouseEvent *event) override;

private slots:
    void onMoveTimerTick();

private:
    static const int CELL_SIZE = 60;
    static const int OFFSET = 30;
    static const int MOVE_INTERVAL_MS = 700;

    QGraphicsScene *m_scene;
    Board *m_board;
    Figure *m_selectedFigure;
    QVector<QGraphicsRectItem*> m_highlightItems;

    QTimer *m_moveTimer;
    QVector<Move> m_pendingMoves;
    int m_currentMoveIndex;
    bool m_gameOver;

    void redraw();
    void drawBoard();
    void drawCoordinates();
    void drawFigures();
    void clearHighlights();
    void highlightMoves(const QVector<QPoint> &moves);
    void checkGameStatus();
    bool sceneToCell(const QPointF &scenePos, int &col, int &row) const;
    QPointF cellTopLeft(int col, int row) const;
};

#endif // BOARDWIDGET_H
