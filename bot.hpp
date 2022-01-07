#ifndef BOT_HPP
#define BOT_HPP

#include "huntermodel.hpp"
#include "snake.hpp"
#include "mouse.hpp"


#include "random.hpp"
#include <ctime>

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

    bool onUpdate(const float dt) override
    {
        if(m_target == nullptr) return HunterModel::onUpdate(dt);

        if(m_entity->body().at(1).x > m_target->pos().x) A();
        if(m_entity->body().at(1).x < m_target->pos().x) D();
        if(m_entity->body().at(1).y > m_target->pos().y) W();
        if(m_entity->body().at(1).y < m_target->pos().y) S();

        return HunterModel::onUpdate(dt);
    }

    void reset() override {
        delete m_entity;

        m_entity = new Mouse({stf::Random(time(0)).getNum(2, m_mapSize.x-2),
                              stf::Random(time(0)).getNum(2, m_mapSize.y-2)});
        HunterModel::reset();
    }

    bool isCollideWithTarget() const override
    {
        if(m_target == nullptr) return false;

        if(m_entity->body().at(1).diff(m_target->pos()) < 1.f) {
            return true;
        }
        return false;
    }
};

#endif // BOT_HPP
