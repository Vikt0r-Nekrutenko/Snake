#include "segmentedentity.hpp"

void SegmentedEntity::wrapping(const int top, const int left, const int right, const int bottom)
{
    if(head().x < left) {
        m_body.at(0).x = right - 1;
    } else if(head().x >= right) {
        m_body.at(0).x = left;
    }

    if(head().y < top) {
        m_body.at(0).y = bottom - 1;
    } else if(head().y >= bottom) {
        m_body.at(0).y = top;
    }
}

bool SegmentedEntity::isHeadOverlapped(const stf::Vec2d &pos) const
{
    return m_body.at(0).diff(pos) < 1;
}

bool SegmentedEntity::isSegmetOverlapped(size_t nOfSeg, const stf::Vec2d &pos) const
{
    return m_body.at(nOfSeg).diff(pos) < 1.f;
}
