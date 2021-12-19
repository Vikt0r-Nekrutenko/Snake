#include "model.hpp"

Model::Model(const stf::Vec2d &mapSize)
    : m_mapSize(mapSize)
{

}

Signal Model::onUpdate(const float dt)
{
    if(m_time > 0.3f)
    {
        m_snake.update();
        m_snake.wrapping(1,1,m_mapSize.x, m_mapSize.y);
        m_time = 0.f;
    }
    m_time += dt;
    return Signal::none;
}
