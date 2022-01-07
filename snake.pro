TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        bot.cpp \
        food.cpp \
        foodmodel.cpp \
        main.cpp \
        meatfood.cpp \
        model.cpp \
        mouse.cpp \
        player.cpp \
        regularfood.cpp \
        segmentedentity.cpp \
        segmentedentitymodel.cpp \
        snake.cpp \
        snakemodel.cpp \
        superfood.cpp \
        view.cpp

unix:!macx|win32: LIBS += -L$$PWD/../stf/release/ -lstf

INCLUDEPATH += $$PWD/../stf
DEPENDPATH += $$PWD/../stf

HEADERS += \
    bot.hpp \
    food.hpp \
    foodmodel.hpp \
    meatfood.hpp \
    model.hpp \
    mouse.hpp \
    player.hpp \
    regularfood.hpp \
    segmentedentity.hpp \
    segmentedentitymodel.hpp \
    snake.hpp \
    snakemodel.hpp \
    superfood.hpp \
    view.hpp
