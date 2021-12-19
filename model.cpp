#include "model.hpp"
#include "random.hpp"
#include <ctime>

Model::Model(const stf::Vec2d &mapSize)
    : m_mapSize(mapSize)
{

}

Signal Model::onUpdate(const float dt)
{
    if(m_time > 0.3f)
    {
        m_snake.update();

        if(m_snake.head().diff(m_eat) < 1.f) {
            m_snake.feed();
            m_eat = stf::Vec2d(stf::Random(time(0)).getNum(2, m_mapSize.x-1),
                               stf::Random(time(0)).getNum(2, m_mapSize.y-1));
        }

        if(m_snake.isAteHerself()) return Signal::end;

        m_snake.wrapping(1,1,m_mapSize.x, m_mapSize.y);
        m_time = 0.f;
    }
    m_time += dt;
    return Signal::none;
}
