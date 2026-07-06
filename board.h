#ifndef BOARD_H
#define BOARD_H

#include <QVector>
#include <QString>
#include "figure.h"

struct Move
{
    int fromCol;
    int fromRow;
    int toCol;
    int toRow;
};

class Board
{
public:
    Board();
    ~Board();

    void clearBoard();
    void setupNewGame();
    void addFigure(Figure *figure);
    Figure* figureAt(int col, int row) const;
    const QVector<Figure*>& getFigures() const;
    void moveFigure(Figure *figure, int col, int row);
    bool applyMove(const Move &move);

    Color getCurrentTurn() const;
    void switchTurn();
    void resetTurn();

    bool isKingInCheck(Color color) const;
    bool isCheckmate(Color color);

    bool saveToFile(const QString &filePath) const;
    bool loadFromFile(const QString &filePath);

    static bool parseMoveLine(const QString &line, Move &move);
    static QVector<Move> readMovesFromFile(const QString &filePath, bool &ok);

private:
    QVector<Figure*> m_figures;
    Color m_currentTurn;

    Figure* createFigure(const QString &typeName, Color color, int col, int row) const;
    QString colorToString(Color color) const;
    Color stringToColor(const QString &text) const;
    Figure* findKing(Color color) const;
};

#endif // BOARD_H
