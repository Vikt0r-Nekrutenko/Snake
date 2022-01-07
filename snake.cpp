#include "snake.hpp"


Snake::Snake(const stf::Vec2d startPos)
{
    for(unsigned int i = 0; i < snake_settings::DEF_LENGHT; ++i) {
        m_body.push_back({startPos.x + i, startPos.y});
    }
}

void Snake::feed()
{
    m_body.push_back(m_body.back());
}

bool Snake::isAteHerself() const
{
    for(size_t i = 1; i < m_body.size(); ++i) {
        if(head().diff(m_body.at(i)) < 1.f) {
            return true;
        }
    }
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
