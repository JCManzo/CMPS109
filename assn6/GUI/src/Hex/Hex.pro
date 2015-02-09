#-------------------------------------------------
#
# Project created by QtCreator 2014-02-23T16:38:55
#
#-------------------------------------------------

QT       += core gui
CONFIG   += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Hex
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        dialog.cpp \
        board.cpp \
        graph.cpp \
        disjointset.cpp \
        ai.cpp

HEADERS  += mainwindow.h \
            dialog.h \
            board.h \
            graph.h \
            disjointset.h \
            ai.h

FORMS    += mainwindow.ui \
         dialog.ui \

RESOURCES += \
    images.qrc
