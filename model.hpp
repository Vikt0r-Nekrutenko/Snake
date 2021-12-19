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
    void reset();

    inline uint16_t score() const { return m_score; }
    inline uint16_t lvl() const { return m_lvl; }
    inline const Snake& snake() const { return m_snake; }
    inline const stf::Vec2d& eat() const { return m_eat;}
    inline const stf::Vec2d& mapSize() const { return m_mapSize;}
private:
    Snake m_snake;
    stf::Vec2d m_mapSize = {0,0};
    stf::Vec2d m_eat = {7, 8};
    float m_time = 0.f;
    float m_lvlDuration = 0.5f;
    bool m_aiIsEnable = false;
    uint16_t m_score = 0u;
    uint16_t m_lvl   = 1u;
};

#endif // MODEL_HPP
