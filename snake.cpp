#include "snake.hpp"

Snake::Snake(const stf::Vec2d startPos)
{
    for(int i = 0; i < 5; ++i)
        m_body.push_back({startPos.x + i, startPos.y});
}

void Snake::wrapping(const int top, const int left, const int right, const int bottom)
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

bool Snake::isAteHerself() const
{
    for(size_t i = 1; i < m_body.size(); ++i)
        if(head().diff(m_body.at(i)) < 1.f) return true;
    return false;
}

void Snake::update()
{
    if(m_isDead) return;
    moveBody();
    m_body.at(0) += m_vel;
}

void Snake::moveBody()
{
    for(auto it = m_body.end()-1; it > m_body.begin(); --it)
        *it = *(it - 1);
}


