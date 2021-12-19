#include "snake.hpp"

Snake::Snake(const stf::Vec2d startPos)
{
    for(int i = 0; i < 5; ++i)
        m_body.push_back({startPos.x + i, startPos.y});
}

void Snake::show(stf::Renderer& renderer)
{
    for(auto &s : m_body) renderer.drawPixel(s, '#');
}

bool Snake::isAteHerself() const
{
    for(auto &s : m_body)
        if(head().diff(s) < 1.f) return true;
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


