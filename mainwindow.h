#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "boardwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void onNewGameClicked();
    void onLoadFileClicked();
    void onSaveFileClicked();
    void onLoadMovesClicked();
    void onStatusMessage(const QString &message);

private:
    BoardWidget *m_boardWidget;

    void setupUi();
};

#endif // MAINWINDOW_H
