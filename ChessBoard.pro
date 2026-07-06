QT += core gui widgets

CONFIG += c++17

TARGET = ChessBoard
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    board.cpp \
    figure.cpp \
    pawn.cpp \
    rook.cpp \
    knight.cpp \
    bishop.cpp \
    queen.cpp \
    king.cpp \
    figureitem.cpp \
    boardwidget.cpp

HEADERS += \
    mainwindow.h \
    board.h \
    figure.h \
    pawn.h \
    rook.h \
    knight.h \
    bishop.h \
    queen.h \
    king.h \
    figureitem.h \
    boardwidget.h

RESOURCES += \
    resources.qrc
