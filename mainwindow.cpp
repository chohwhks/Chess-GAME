#include "mainwindow.h"

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi();
    setWindowTitle("Шахматная доска");
}

void MainWindow::setupUi()
{
    QWidget *central = new QWidget(this);
    QHBoxLayout *mainLayout = new QHBoxLayout(central);

    m_boardWidget = new BoardWidget(central);
    mainLayout->addWidget(m_boardWidget);

    QVBoxLayout *sideLayout = new QVBoxLayout();

    QPushButton *btnNewGame = new QPushButton("Начать новую партию", central);
    QPushButton *btnLoadFile = new QPushButton("Прочитать из файла", central);
    QPushButton *btnSaveFile = new QPushButton("Сохранить в файл", central);
    QPushButton *btnLoadMoves = new QPushButton("Прочитать ходы из файла", central);

    connect(btnNewGame, &QPushButton::clicked, this, &MainWindow::onNewGameClicked);
    connect(btnLoadFile, &QPushButton::clicked, this, &MainWindow::onLoadFileClicked);
    connect(btnSaveFile, &QPushButton::clicked, this, &MainWindow::onSaveFileClicked);
    connect(btnLoadMoves, &QPushButton::clicked, this, &MainWindow::onLoadMovesClicked);

    sideLayout->addWidget(btnNewGame);
    sideLayout->addWidget(btnLoadFile);
    sideLayout->addWidget(btnSaveFile);
    sideLayout->addWidget(btnLoadMoves);
    sideLayout->addStretch();

    mainLayout->addLayout(sideLayout);
    setCentralWidget(central);
}

void MainWindow::onNewGameClicked()
{
    m_boardWidget->newGame();
}

void MainWindow::onLoadFileClicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Выберите файл с координатами",
                                                    QString(), "Текстовые файлы (*.txt)");
    if (filePath.isEmpty())
        return;

    if (!m_boardWidget->loadFromFile(filePath))
        QMessageBox::warning(this, "Ошибка", "Не удалось прочитать файл");
}

void MainWindow::onSaveFileClicked()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Сохранить координаты фигур",
                                                    QString(), "Текстовые файлы (*.txt)");
    if (filePath.isEmpty())
        return;

    if (!m_boardWidget->saveToFile(filePath))
        QMessageBox::warning(this, "Ошибка", "Не удалось сохранить файл");
}

void MainWindow::onLoadMovesClicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Выберите файл с ходами",
                                                    QString(), "Текстовые файлы (*.txt)");
    if (filePath.isEmpty())
        return;

    if (!m_boardWidget->startMovesPlayback(filePath))
        QMessageBox::warning(this, "Ошибка", "Не удалось прочитать файл ходов");
}