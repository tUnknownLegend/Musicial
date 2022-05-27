TEMPLATE = app
TARGET = Client

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20

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

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../builtLibs/release/ -lQT_LIB
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../builtLibs/debug/ -lQT_LIB
else:unix: LIBS += -L$$PWD/../builtLibs/ -lQT_LIB

INCLUDEPATH += $$PWD/../builtLibs
DEPENDPATH += $$PWD/../builtLibs

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../builtLibs/release/libQT_LIB.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../builtLibs/debug/libQT_LIB.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../builtLibs/release/QT_LIB.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../builtLibs/debug/QT_LIB.lib
else:unix: PRE_TARGETDEPS += $$PWD/../builtLibs/libQT_LIB.a

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../builtLibs/release/ -lMusicial_API_LIB
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../builtLibs/debug/ -lMusicial_API_LIB
else:unix: LIBS += -L$$PWD/../builtLibs/ -lMusicial_API_LIB

INCLUDEPATH += $$PWD/../builtLibs
DEPENDPATH += $$PWD/../builtLibs

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../builtLibs/release/libMusicial_API_LIB.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../builtLibs/debug/libMusicial_API_LIB.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../builtLibs/release/Musicial_API_LIB.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../builtLibs/debug/Musicial_API_LIB.lib
else:unix: PRE_TARGETDEPS += $$PWD/../builtLibs/libMusicial_API_LIB.a

LIBS += -lcurl
