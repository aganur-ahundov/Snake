#-------------------------------------------------
#
# Project created by QtCreator 2016-05-23T22:36:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = snake_work_version
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    snake.cpp \
    field.cpp \
    gamepainter.cpp

HEADERS  += mainwindow.h \
    snake.h \
    field.h \
    gamepainter.h

FORMS    += mainwindow.ui
