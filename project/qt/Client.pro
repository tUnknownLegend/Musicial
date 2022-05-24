TEMPLATE = app
TARGET = Client

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

LIBS += -lcurl

SOURCES +=  main.cpp \
    CustomWidgets.cpp \
    MainWindow.cpp \
    playlistcreator.cpp

HEADERS += \
    CustomWidgets.h \
    MainWindow.h \
    playlistcreator.h \

DISTFILES += \

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../builtLibs/release/ -lserverLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../builtLibs/debug/ -lserverLib
else:unix: LIBS += -L$$PWD/../builtLibs/ -lserverLib

INCLUDEPATH += $$PWD/../builtLibs
DEPENDPATH += $$PWD/../builtLibs

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../builtLibs/release/libserverLib.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../builtLibs/debug/libserverLib.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../builtLibs/release/serverLib.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../builtLibs/debug/serverLib.lib
else:unix: PRE_TARGETDEPS += $$PWD/../builtLibs/libserverLib.a
