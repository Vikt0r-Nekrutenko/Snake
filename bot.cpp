#include "bot.hpp"

Bot::Bot(const stf::Vec2d &mapSize, const stf::Vec2d &startPos)
    : HunterModel(mapSize)
{}

bool Bot::onUpdate(const float dt)
{
    if(m_target == nullptr) return HunterModel::onUpdate(dt);

    if(m_entity->head().x > m_target->pos().x) A();
    if(m_entity->head().x < m_target->pos().x) D();
    if(m_entity->head().y > m_target->pos().y) W();
    if(m_entity->head().y < m_target->pos().y) S();

    return HunterModel::onUpdate(dt);
}
