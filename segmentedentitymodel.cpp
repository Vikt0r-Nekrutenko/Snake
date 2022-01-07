#include "segmentedentitymodel.hpp"

SegmentedEntityModel::SegmentedEntityModel(const stf::Vec2d &mapSize)
    : m_mapSize(mapSize)
{}

bool SegmentedEntityModel::isCollideWithTarget() const
{
    if(m_target == nullptr) return false;

    if(m_entity->head().diff(m_target->pos()) < 1.f) {
        return true;
    }
    return false;
}

