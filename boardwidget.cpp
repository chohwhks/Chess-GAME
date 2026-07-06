#include "boardwidget.h"
#include <QMouseEvent>
#include <QGraphicsTextItem>
#include <QPixmap>
#include <QPen>
#include <QBrush>

BoardWidget::BoardWidget(QWidget *parent)
    : QGraphicsView(parent), m_selectedFigure(nullptr), m_currentMoveIndex(0), m_gameOver(false)
{
    m_scene = new QGraphicsScene(this);
    setScene(m_scene);
    m_board = new Board();

    int size = OFFSET * 2 + CELL_SIZE * 8;
    setFixedSize(size + 4, size + 4);
    m_scene->setSceneRect(0, 0, size, size);

    m_moveTimer = new QTimer(this);
    connect(m_moveTimer, &QTimer::timeout, this, &BoardWidget::onMoveTimerTick);

    newGame();
}

BoardWidget::~BoardWidget()
{
    delete m_board;
}

void BoardWidget::newGame()
{
    m_moveTimer->stop();
    m_pendingMoves.clear();
    m_currentMoveIndex = 0;
    m_gameOver = false;

    m_board->setupNewGame();
    redraw();
    emit statusMessage("Ход белых");
}

bool BoardWidget::loadFromFile(const QString &filePath)
{
    m_moveTimer->stop();
    m_pendingMoves.clear();
    m_currentMoveIndex = 0;
    m_gameOver = false;

    bool ok = m_board->loadFromFile(filePath);
    if (ok) {
        redraw();
        emit statusMessage("Ход белых");
    }
    return ok;
}

bool BoardWidget::saveToFile(const QString &filePath) const
{
    return m_board->saveToFile(filePath);
}

bool BoardWidget::startMovesPlayback(const QString &filePath)
{
    bool ok = false;
    QVector<Move> moves = Board::readMovesFromFile(filePath, ok);
    if (!ok)
        return false;

    m_moveTimer->stop();
    m_board->setupNewGame();
    m_pendingMoves = moves;
    m_currentMoveIndex = 0;
    m_gameOver = false;
    redraw();

    m_moveTimer->start(MOVE_INTERVAL_MS);
    return true;
}

bool BoardWidget::startPositionAndMovesPlayback(const QString &positionPath, const QString &movesPath)
{
    if (!m_board->loadFromFile(positionPath))
        return false;

    bool ok = false;
    QVector<Move> moves = Board::readMovesFromFile(movesPath, ok);
    if (!ok)
        return false;

    m_moveTimer->stop();
    m_board->resetTurn();
    m_pendingMoves = moves;
    m_currentMoveIndex = 0;
    m_gameOver = false;
    redraw();

    m_moveTimer->start(MOVE_INTERVAL_MS);
    return true;
}

void BoardWidget::onMoveTimerTick()
{
    if (m_gameOver || m_currentMoveIndex >= m_pendingMoves.size()) {
        m_moveTimer->stop();
        return;
    }

    m_board->applyMove(m_pendingMoves[m_currentMoveIndex]);
    m_board->switchTurn();
    m_currentMoveIndex++;
    redraw();
    checkGameStatus();

    if (m_currentMoveIndex >= m_pendingMoves.size())
        m_moveTimer->stop();
}

void BoardWidget::checkGameStatus()
{
    Color turn = m_board->getCurrentTurn();

    if (m_board->isKingInCheck(turn)) {
        if (m_board->isCheckmate(turn)) {
            m_gameOver = true;
            m_moveTimer->stop();
            QString winner = (turn == Color::White) ? "Чёрные" : "Белые";
            emit statusMessage(winner + " выигрывают, мат!");
            return;
        }

        QString colorName = (turn == Color::White) ? "белым" : "чёрным";
        emit statusMessage("Шах " + colorName + "!");
        return;
    }

    QString colorName = (turn == Color::White) ? "белых" : "чёрных";
    emit statusMessage("Ход " + colorName);
}

QPointF BoardWidget::cellTopLeft(int col, int row) const
{
    int x = OFFSET + col * CELL_SIZE;
    int y = OFFSET + (7 - row) * CELL_SIZE;
    return QPointF(x, y);
}

bool BoardWidget::sceneToCell(const QPointF &scenePos, int &col, int &row) const
{
    int x = static_cast<int>(scenePos.x()) - OFFSET;
    int y = static_cast<int>(scenePos.y()) - OFFSET;

    if (x < 0 || y < 0)
        return false;

    col = x / CELL_SIZE;
    row = 7 - (y / CELL_SIZE);

    return col >= 0 && col <= 7 && row >= 0 && row <= 7;
}

void BoardWidget::drawBoard()
{
    for (int col = 0; col < 8; col++) {
        for (int row = 0; row < 8; row++) {
            QPointF topLeft = cellTopLeft(col, row);
            bool isDark = (col + row) % 2 == 0;
            QColor color = isDark ? QColor(118, 150, 86) : QColor(238, 238, 210);

            QGraphicsRectItem *cell = m_scene->addRect(
                topLeft.x(), topLeft.y(), CELL_SIZE, CELL_SIZE,
                QPen(Qt::NoPen), QBrush(color));
            cell->setZValue(0);
        }
    }
}

void BoardWidget::drawCoordinates()
{
    QString letters = "abcdefgh";

    for (int col = 0; col < 8; col++) {
        QGraphicsTextItem *text = m_scene->addText(letters.mid(col, 1));
        QPointF pos = cellTopLeft(col, 0);
        text->setPos(pos.x() + CELL_SIZE / 2 - 5, pos.y() + CELL_SIZE + 4);
    }

    for (int row = 0; row < 8; row++) {
        QGraphicsTextItem *text = m_scene->addText(QString::number(row + 1));
        QPointF pos = cellTopLeft(0, row);
        text->setPos(pos.x() - 20, pos.y() + CELL_SIZE / 2 - 10);
    }
}

void BoardWidget::drawFigures()
{
    const QVector<Figure*> &figures = m_board->getFigures();

    for (int i = 0; i < figures.size(); i++) {
        Figure *figure = figures[i];
        QString path = ":/images/" + figure->getImageName() + ".png";
        QPixmap pixmap(path);
        pixmap = pixmap.scaled(CELL_SIZE - 6, CELL_SIZE - 6,
                               Qt::KeepAspectRatio, Qt::SmoothTransformation);

        FigureItem *item = new FigureItem(figure, pixmap);
        QPointF topLeft = cellTopLeft(figure->getCol(), figure->getRow());
        item->setPos(topLeft.x() + 3, topLeft.y() + 3);
        item->setZValue(1);
        m_scene->addItem(item);
    }
}

void BoardWidget::clearHighlights()
{
    for (int i = 0; i < m_highlightItems.size(); i++) {
        m_scene->removeItem(m_highlightItems[i]);
        delete m_highlightItems[i];
    }
    m_highlightItems.clear();
}

void BoardWidget::highlightMoves(const QVector<QPoint> &moves)
{
    for (int i = 0; i < moves.size(); i++) {
        QPointF topLeft = cellTopLeft(moves[i].x(), moves[i].y());
        QGraphicsRectItem *rect = m_scene->addRect(
            topLeft.x(), topLeft.y(), CELL_SIZE, CELL_SIZE,
            QPen(QColor(255, 0, 0), 3), QBrush(Qt::NoBrush));
        rect->setZValue(2);
        m_highlightItems.append(rect);
    }
}

void BoardWidget::redraw()
{
    clearHighlights();
    m_scene->clear();
    m_selectedFigure = nullptr;

    drawBoard();
    drawCoordinates();
    drawFigures();
}

void BoardWidget::mousePressEvent(QMouseEvent *event)
{
    if (m_gameOver)
        return;

    QPointF scenePos = mapToScene(event->pos());
    int col, row;

    if (!sceneToCell(scenePos, col, row)) {
        clearHighlights();
        m_selectedFigure = nullptr;
        return;
    }

    if (m_selectedFigure != nullptr) {
        QVector<QPoint> moves = m_selectedFigure->possibleMoves(*m_board);
        if (moves.contains(QPoint(col, row))) {
            m_board->moveFigure(m_selectedFigure, col, row);
            m_board->switchTurn();
            redraw();
            checkGameStatus();
            return;
        }
    }

    Figure *clickedFigure = m_board->figureAt(col, row);
    clearHighlights();

    if (clickedFigure == nullptr || clickedFigure == m_selectedFigure) {
        m_selectedFigure = nullptr;
        return;
    }

    if (clickedFigure->getColor() != m_board->getCurrentTurn()) {
        m_selectedFigure = nullptr;
        return;
    }

    m_selectedFigure = clickedFigure;
    QVector<QPoint> moves = m_selectedFigure->possibleMoves(*m_board);
    highlightMoves(moves);
}
