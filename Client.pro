TEMPLATE = app
TARGET = Client

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES +=  main.cpp \
    CustomWidgets.cpp \
    MainWindow.cpp \
    playlistcreator.cpp

HEADERS += \
    CustomWidgets.h \
    MainWindow.h \
    playlistcreator.h

DISTFILES += \
