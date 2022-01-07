#ifndef BOT_HPP
#define BOT_HPP

#include "huntermodel.hpp"
#include "snake.hpp"
#include "mouse.hpp"

class Bot : public HunterModel
{
public:
    Bot(const stf::Vec2d& mapSize, const stf::Vec2d& startPos = {10,10});
    bool onUpdate(const float dt) override;
};

class SnakeBot : public Bot {
public:
    SnakeBot(const stf::Vec2d& mapSize, const stf::Vec2d& startPos = {10, 10})
        : Bot(mapSize, startPos)
    {
        m_entity = new Snake(startPos);
    }
};

class MouseBot : public Bot {
public:
    MouseBot(const stf::Vec2d& mapSize, const stf::Vec2d& startPos = {10, 10})
        : Bot(mapSize, startPos)
    {
        m_entity = new Mouse(startPos);
    }
};

#endif // BOT_HPP
