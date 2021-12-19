#ifndef MODEL_HPP
#define MODEL_HPP

#include "snake.hpp"

enum class Signal
{
    none, start, pause, end,
};

class Model
{
public:
    Model(const stf::Vec2d& mapSize);

    Signal onUpdate(const float dt);
private:
    Snake m_snake;
    stf::Vec2d m_mapSize = {0,0};
};

#endif // MODEL_HPP
