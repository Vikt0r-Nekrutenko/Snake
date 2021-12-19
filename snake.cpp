#include "snake.hpp"

Snake::Snake(const stf::Vec2d startPos)
{
    for(int i = 0; i < 5; ++i)
        m_body.push_back({startPos.x + i, startPos.y});
}

void Snake::moveBody()
{
    for(auto it = m_body.end()-1; it > m_body.begin(); --it)
        *it = *(it - 1);
}
