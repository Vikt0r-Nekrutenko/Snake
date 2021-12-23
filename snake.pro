TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        eat.cpp \
        main.cpp \
        model.cpp \
        snake.cpp \
        snakemodel.cpp \
        view.cpp

unix:!macx|win32: LIBS += -L$$PWD/../stf/release/ -lstf

INCLUDEPATH += $$PWD/../stf
DEPENDPATH += $$PWD/../stf

HEADERS += \
    eat.hpp \
    model.hpp \
    snake.hpp \
    snakemodel.hpp \
    view.hpp
