#include "bot.hpp"

Bot::Bot(const stf::Vec2d &mapSize, const stf::Vec2d &startPos)
    : SnakeModel(mapSize, startPos)
{}

bool Bot::onUpdate(const float dt)
{
    if(m_target == nullptr) return SnakeModel::onUpdate(dt);

    if(m_entity->head().x > m_target->pos().x) A();
    if(m_entity->head().x < m_target->pos().x) D();
    if(m_entity->head().y > m_target->pos().y) W();
    if(m_entity->head().y < m_target->pos().y) S();

    return SnakeModel::onUpdate(dt);
}
