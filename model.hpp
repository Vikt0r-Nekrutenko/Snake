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
    stf::Vec2d m_eat = {7, 8};
    float m_time = 0.f;
};

#endif // MODEL_HPP
