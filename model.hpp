#ifndef MODEL_HPP
#define MODEL_HPP

#include "snake.hpp"
#include <cstdint>

enum class Signal : uint8_t
{
    none, start, pause, end,
};

class Model
{
public:
    Model(const stf::Vec2d& mapSize);

    Signal onUpdate(const float dt);
    Signal keyEvents(const int key);
    void aiControl();

    inline const Snake& snake() const { return m_snake; }
    inline const stf::Vec2d& eat() const { return m_eat;}
    inline const stf::Vec2d& mapSize() const { return m_mapSize;}
private:
    Snake m_snake;
    stf::Vec2d m_mapSize = {0,0};
    stf::Vec2d m_eat = {7, 8};
    float m_time = 0.f;
    bool m_aiIsEnable = false;
};

#endif // MODEL_HPP
