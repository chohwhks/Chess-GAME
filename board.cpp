#include "board.h"
#include "pawn.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"

#include <QFile>
#include <QTextStream>
#include <QStringList>

Board::Board()
{
}

Board::~Board()
{
    clearBoard();
}

void Board::clearBoard()
{
    for (int i = 0; i < m_figures.size(); i++)
        delete m_figures[i];
    m_figures.clear();
}

void Board::setupNewGame()
{
    clearBoard();

    QString backRank[8] = { "rook", "knight", "bishop", "queen",
                           "king", "bishop", "knight", "rook" };

    for (int col = 0; col < 8; col++) {
        addFigure(createFigure(backRank[col], Color::White, col, 0));
        addFigure(createFigure("pawn", Color::White, col, 1));

        addFigure(createFigure(backRank[col], Color::Black, col, 7));
        addFigure(createFigure("pawn", Color::Black, col, 6));
    }
}

void Board::addFigure(Figure *figure)
{
    if (figure != nullptr)
        m_figures.append(figure);
}

Figure* Board::figureAt(int col, int row) const
{
    for (int i = 0; i < m_figures.size(); i++) {
        if (m_figures[i]->getCol() == col && m_figures[i]->getRow() == row)
            return m_figures[i];
    }
    return nullptr;
}

const QVector<Figure*>& Board::getFigures() const
{
    return m_figures;
}

void Board::moveFigure(Figure *figure, int col, int row)
{
    Figure *target = figureAt(col, row);
    if (target != nullptr && target != figure) {
        m_figures.removeOne(target);
        delete target;
    }
    figure->setPosition(col, row);
}

bool Board::applyMove(const Move &move)
{
    Figure *figure = figureAt(move.fromCol, move.fromRow);
    if (figure == nullptr)
        return false;

    moveFigure(figure, move.toCol, move.toRow);
    return true;
}

Figure* Board::createFigure(const QString &typeName, Color color, int col, int row) const
{
    if (typeName == "pawn")
        return new Pawn(color, col, row);
    if (typeName == "rook")
        return new Rook(color, col, row);
    if (typeName == "knight")
        return new Knight(color, col, row);
    if (typeName == "bishop")
        return new Bishop(color, col, row);
    if (typeName == "queen")
        return new Queen(color, col, row);
    if (typeName == "king")
        return new King(color, col, row);

    return nullptr;
}

QString Board::colorToString(Color color) const
{
    return (color == Color::White) ? "white" : "black";
}

Color Board::stringToColor(const QString &text) const
{
    return (text == "white") ? Color::White : Color::Black;
}

bool Board::saveToFile(const QString &filePath) const
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QTextStream out(&file);
    for (int i = 0; i < m_figures.size(); i++) {
        Figure *figure = m_figures[i];
        QChar colLetter = QChar('a' + figure->getCol());
        int rowNumber = figure->getRow() + 1;

        out << colorToString(figure->getColor()) << " "
            << figure->getTypeName() << " "
            << colLetter << rowNumber << "\n";
    }

    file.close();
    return true;
}

bool Board::loadFromFile(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QVector<Figure*> newFigures;
    QTextStream in(&file);

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty())
            continue;

        QStringList parts = line.split(" ", Qt::SkipEmptyParts);
        if (parts.size() != 3)
            continue;

        Color color = stringToColor(parts[0]);
        QString typeName = parts[1];
        QString square = parts[2];

        if (square.length() < 2)
            continue;

        int col = square[0].toLatin1() - 'a';
        int row = square.mid(1).toInt() - 1;

        Figure *figure = createFigure(typeName, color, col, row);
        if (figure != nullptr)
            newFigures.append(figure);
    }

    file.close();

    if (newFigures.isEmpty())
        return false;

    clearBoard();
    m_figures = newFigures;
    return true;
}

bool Board::parseMoveLine(const QString &line, Move &move)
{
    QString trimmed = line.trimmed();
    if (trimmed.length() != 4)
        return false;

    int fromCol = trimmed[0].toLatin1() - 'a';
    int fromRow = trimmed[1].digitValue() - 1;
    int toCol = trimmed[2].toLatin1() - 'a';
    int toRow = trimmed[3].digitValue() - 1;

    if (fromCol < 0 || fromCol > 7 || fromRow < 0 || fromRow > 7)
        return false;
    if (toCol < 0 || toCol > 7 || toRow < 0 || toRow > 7)
        return false;

    move.fromCol = fromCol;
    move.fromRow = fromRow;
    move.toCol = toCol;
    move.toRow = toRow;
    return true;
}

QVector<Move> Board::readMovesFromFile(const QString &filePath, bool &ok)
{
    QVector<Move> moves;
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        ok = false;
        return moves;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (line.trimmed().isEmpty())
            continue;

        Move move;
        if (parseMoveLine(line, move))
            moves.append(move);
    }

    file.close();
    ok = !moves.isEmpty();
    return moves;
}
