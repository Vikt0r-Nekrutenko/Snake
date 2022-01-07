#include "snake.hpp"

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

SegmentedEntity::SegmentedEntity(const stf::Vec2d startPos) { }

bool SegmentedEntity::isHeadOverlapped(const stf::Vec2d &pos) const
{
    return m_body.at(0).diff(pos) < 1;
}

bool SegmentedEntity::isSegmetOverlapped(size_t nOfSeg, const stf::Vec2d &pos) const
{
    return m_body.at(nOfSeg).diff(pos) < 1.f;
}


Snake::Snake(const stf::Vec2d startPos) : SegmentedEntity(startPos)
{
    for(int i = 0; i < 5; ++i)
        m_body.push_back({startPos.x + i, startPos.y});
}

void Snake::feed()
{
    m_body.push_back(m_body.back());
}

bool Snake::isAteHerself() const
{
    for(size_t i = 1; i < m_body.size(); ++i)
        if(head().diff(m_body.at(i)) < 1.f) return true;
    return false;
}

void Snake::update()
{
    moveBody();
    m_body.at(0) += m_vel;
}

void Snake::moveBody()
{
    for(auto it = m_body.end()-1; it > m_body.begin(); --it)
        *it = *(it - 1);
}



void Mouse::update()
{
    m_body[1] += m_vel;
    moveBody();
}

void Mouse::moveBody()
{
    m_body[0] = m_body[1] + m_vel;
    m_body[2] = m_body[1] - m_vel;
}
