#include "snakemodel.hpp"
#include <ctime>
#include "random.hpp"

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
