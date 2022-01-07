#include "snakemodel.hpp"
#include <ctime>
#include "food.hpp"

SnakeModel::SnakeModel(const stf::Vec2d &mapSize, const stf::Vec2d &startPos)
    : SegmentedEntityModel(mapSize)
{
    m_entity = new Snake(startPos);
}

bool SnakeModel::onUpdate(const float dt)
{
    if(m_target == nullptr) return true;

    if(m_duration > m_lvlDuration)
    {
        m_entity->update();

        m_entity->wrapping(2, 1, m_mapSize.x-1, m_mapSize.y-1);
        m_duration = 0.f;
    }
    m_duration += dt;
    return true;
}

void SnakeModel::reset()
{
    m_entity = new Snake({stf::Random(time(0)).getNum(2, m_mapSize.x-2),
                          stf::Random(time(0)).getNum(2, m_mapSize.y-2)});
    m_lvlDuration = snake_model_settings::MAX_DURATION;
    m_score = 0u;
    m_lvl   = 1u;
}

bool SnakeModel::isAteHerself() const
{
    return snake()->isAteHerself();
}

SegmentedEntityModel::SegmentedEntityModel(const stf::Vec2d &mapSize)
    : m_mapSize(mapSize)
{

}

bool SegmentedEntityModel::isCollideWithTarget() const
{
    if(m_target == nullptr) return false;

    if(m_entity->head().diff(m_target->pos()) < 1.f)
        return true;
    return false;
}

void SnakeModel::collisionWithTargetHandler()
{
    using namespace snake_model_settings;
    m_entity->feed();
    m_score += m_target->nutritionalValue();
    if(m_lvl < MAX_LEVEL && m_entity->length() % LVLUP_STEP == 0) {
        if(m_lvlDuration > MIN_DURATION) m_lvlDuration -= DURATION_STEP;
        ++m_lvl;
    }
}

SegmentedEntityModel *SnakeModel::collisionWithEntityHandler(SegmentedEntityModel *snakeMod)
{
    for(size_t s1 = 0; s1 < m_entity->length(); ++s1) {
        for (size_t s2 = 0; s2 < (*snakeMod)()->length(); ++s2) {
            if(m_entity->isSegmetOverlapped(s1, snakeMod->segmet(s2))) {
                if(m_score > (*snakeMod)()->length()) {
                    return snakeMod;
                } else {
                    return this;
                }
            }
        }
    }
    return nullptr;
}


Player::Player(const stf::Vec2d &mapSize, const stf::Vec2d &startPos)
    : SnakeModel(mapSize, startPos)
{

}

void Player::keyEvents(const int key)
{
    switch (key) {
    case 'w': W(); break;
    case 'a': A(); break;
    case 's': S(); break;
    case 'd': D(); break;
    }
}

void Player::reset()
{
    --m_lifes;
    if(m_lifes > 0) {
        SnakeModel::reset();
    }
}

Bot::Bot(const stf::Vec2d &mapSize, const stf::Vec2d &startPos)
    : SnakeModel(mapSize, startPos)
{

}

bool Bot::onUpdate(const float dt)
{
    if(m_target == nullptr) return SnakeModel::onUpdate(dt);

    if(m_entity->head().x > m_target->pos().x) A();
    if(m_entity->head().x < m_target->pos().x) D();
    if(m_entity->head().y > m_target->pos().y) W();
    if(m_entity->head().y < m_target->pos().y) S();

    return SnakeModel::onUpdate(dt);
}
