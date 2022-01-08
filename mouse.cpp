#include "mouse.hpp"
#include "renderer.hpp"

Mouse::Mouse(const stf::Vec2d startPos)
{
    for(int i = 0; i < 3; ++i) {
        m_body.push_back({startPos.x + i, startPos.y});
    }
}

void Mouse::update()
{
    m_body[1] += m_vel;
    moveBody();
}

void Mouse::feed()
{

}

void Mouse::show(stf::Renderer &renderer, const stf::Vec2d &camera)
{
    if(head() - m_body.at(1) == stf::Vec2d(0, -1)) {
        renderer.drawPixel(m_body.at(0) - camera, 'A');
        renderer.drawPixel(m_body.at(2) - camera, '|');
    } else if(head() - m_body.at(1) == stf::Vec2d(0, +1)) {
        renderer.drawPixel(m_body.at(0) - camera, 'V');
        renderer.drawPixel(m_body.at(2) - camera, '|');
    } else if(head() - m_body.at(1) == stf::Vec2d(+1, 0)) {
        renderer.drawPixel(m_body.at(0) - camera, '>');
        renderer.drawPixel(m_body.at(2) - camera, '-');
    } else if(head() - m_body.at(1) == stf::Vec2d(-1, 0)) {
        renderer.drawPixel(m_body.at(0) - camera, '<');
        renderer.drawPixel(m_body.at(2) - camera, '-');
    }

    renderer.drawPixel(m_body.at(1), 'O');
}

void Mouse::moveBody()
{
    m_body[0] = m_body[1] + m_vel;
    m_body[2] = m_body[1] - m_vel;
}
