#include "mousebot.hpp"
#include "mouse.hpp"
#include "random.hpp"
#include <ctime>


MouseBotModel::MouseBotModel(const stf::Vec2d &mapSize, const stf::Vec2d &startPos)
    : BotModel(mapSize, startPos)
{
    m_entity = new Mouse(startPos);
}

bool MouseBotModel::onUpdate(const float dt)
{
    if(m_target == nullptr) return HunterModel::onUpdate(dt);

    if(m_entity->body().at(1).x > m_target->pos().x) A();
    if(m_entity->body().at(1).x < m_target->pos().x) D();
    if(m_entity->body().at(1).y > m_target->pos().y) W();
    if(m_entity->body().at(1).y < m_target->pos().y) S();

    return HunterModel::onUpdate(dt);
}

void MouseBotModel::reset() {
    delete m_entity;

    m_entity = new Mouse({stf::Random(time(0)).getNum(2, m_mapSize.x-2),
                          stf::Random(time(0)).getNum(2, m_mapSize.y-2)});
    HunterModel::reset();
}

bool MouseBotModel::isCollideWithTarget() const
{
    if(m_target == nullptr) return false;

    if(m_entity->body().at(1).diff(m_target->pos()) < 1.f) {
        return true;
    }
    return false;
}
