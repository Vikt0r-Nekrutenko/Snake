TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        food.cpp \
        foodmodel.cpp \
        main.cpp \
        model.cpp \
        regularfood.cpp \
        snake.cpp \
        snakemodel.cpp \
        superfood.cpp \
        view.cpp

unix:!macx|win32: LIBS += -L$$PWD/../stf/release/ -lstf

INCLUDEPATH += $$PWD/../stf
DEPENDPATH += $$PWD/../stf

HEADERS += \
    food.hpp \
    foodmodel.hpp \
    model.hpp \
    regularfood.h \
    snake.hpp \
    snakemodel.hpp \
    superfood.hpp \
    view.hpp
