#ifndef MODEL_HPP
#define MODEL_HPP

#include "snake.hpp"
#include <cstdint>

enum class Signal : uint8_t
{
    none, start, pause, end,
};

class SnakeModel
{
public:
    SnakeModel(const stf::Vec2d& mapSize)
        : m_mapSize(mapSize)
    {

    }

    void onUpdate(const float dt)
    {
        if(m_snake.isDead()) return;

        if(m_time > m_lvlDuration)
        {
            m_snake.update();

            if(m_snake.isAteHerself())
                m_snake.killSnake();

            m_snake.wrapping(1,1,m_mapSize.x, m_mapSize.y);
            m_time = 0.f;
        }
        m_time += dt;
    }

    void keyEvents(const int key)
    {
        switch (key) {
        case 'w': m_snake.W(); break;
        case 'a': m_snake.A(); break;
        case 's': m_snake.S(); break;
        case 'd': m_snake.D(); break;
        }
    }

    void aiControl(const stf::Vec2d& target)
    {
        if(m_snake.head().x > target.x) m_snake.A();
        if(m_snake.head().x < target.x) m_snake.D();
        if(m_snake.head().y > target.y) m_snake.W();
        if(m_snake.head().y < target.y) m_snake.S();
    }

    void reset()
    {
        m_snake = Snake();
        m_score = 0u; m_lvl = 1u;
        m_lvlDuration = 0.5f;
    }

    inline uint16_t score() const { return m_score; }
    inline uint16_t lvl() const { return m_lvl; }
    inline const Snake& snake() const { return m_snake; }
    inline const stf::Vec2d& mapSize() const { return m_mapSize;}
private:
    Snake m_snake;
    stf::Vec2d m_mapSize = {0,0};
    float m_time = 0.f;
    float m_lvlDuration = 0.5f;
    bool m_aiIsEnable = false;
    uint16_t m_score = 0u;
    uint16_t m_lvl   = 1u;
};

class GameModel
{
public:
    GameModel(const stf::Vec2d& mapSize);

    Signal onUpdate(const float dt);
    Signal keyEvents(const int key);
    void aiControl();
    void reset();

    inline const stf::Vec2d& eat() const { return m_eat;}
    inline const stf::Vec2d& mapSize() const { return m_mapSize;}

    inline const SnakeModel& snakeModel() const { return snakeMod; }
private:
    SnakeModel snakeMod;

    stf::Vec2d m_mapSize = {0,0};
    stf::Vec2d m_eat = {7, 8};
    bool m_aiIsEnable = false;
};

#endif // MODEL_HPP
