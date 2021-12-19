TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
        model.cpp \
        snake.cpp

unix:!macx|win32: LIBS += -L$$PWD/../stf/release/ -lstf

INCLUDEPATH += $$PWD/../stf
DEPENDPATH += $$PWD/../stf

HEADERS += \
    model.hpp \
    snake.hpp
