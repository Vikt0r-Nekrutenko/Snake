#include "mouse.hpp"

void Mouse::update()
{
    m_body[1] += m_vel;
    moveBody();
}

void Mouse::feed()
{

}

void Mouse::moveBody()
{
    m_body[0] = m_body[1] + m_vel;
    m_body[2] = m_body[1] - m_vel;
}
