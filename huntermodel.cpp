#include "huntermodel.hpp"
#include <ctime>
#include "random.hpp"

HunterModel::HunterModel(const stf::Vec2d &mapSize)
    : SegmentedEntityModel(mapSize)
{}

bool HunterModel::onUpdate(const float dt)
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

void HunterModel::reset()
{
    m_lvlDuration = hunter_model_settings::MAX_DURATION;
    m_score = 0u;
    m_lvl   = 1u;
}

void HunterModel::collisionWithTargetHandler()
{
    using namespace hunter_model_settings;
    m_entity->feed();
    m_score += m_target->nutritionalValue();
    if(m_lvl < MAX_LEVEL && m_entity->length() % LVLUP_STEP == 0) {
        if(m_lvlDuration > MIN_DURATION) m_lvlDuration -= DURATION_STEP;
        ++m_lvl;
    }
}

SegmentedEntityModel *HunterModel::collisionWithEntityHandler(SegmentedEntityModel *entity)
{
    for(size_t s1 = 0; s1 < m_entity->length(); ++s1) {
        for (size_t s2 = 0; s2 < (*entity)()->length(); ++s2) {
            if(m_entity->isSegmetOverlapped(s1, entity->segmet(s2))) {
                if(m_entity->length() > (*entity)()->length()) {
                    return entity;
                } else {
                    return this;
                }
            }
        }
    }
    return nullptr;
}
