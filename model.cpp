#include "model.hpp"
#include "random.hpp"
#include <ctime>

GameModel::GameModel(const stf::Vec2d &mapSize)
    : snakeMod(mapSize), m_mapSize(mapSize)
{

}

Signal GameModel::onUpdate(const float dt)
{
    /*if(m_time > m_lvlDuration)
    {
        m_snake.update();
        if(m_aiIsEnable)
            aiControl();

        if(m_snake.head().diff(m_eat) < 1.f) {
            m_snake.feed();
            m_eat = stf::Vec2d(stf::Random(time(0)).getNum(2, m_mapSize.x-1),
                               stf::Random(time(0)).getNum(2, m_mapSize.y-1));
            ++m_score;
            if(m_score != 1 && m_lvl < 20 && m_score % 5 == 0) {
                m_lvlDuration -= 0.025f;
                ++m_lvl;
            }
        }

        if(m_snake.isAteHerself()) return Signal::end;

        m_snake.wrapping(1,1,m_mapSize.x, m_mapSize.y);
        m_time = 0.f;
    }
    m_time += dt;
    */
    snakeMod.onUpdate(dt);
    return Signal::none;
}

Signal GameModel::keyEvents(const int key)
{
    switch (key) {
    case 'w': m_snake.W(); break;
    case 'a': m_snake.A(); break;
    case 's': m_snake.S(); break;
    case 'd': m_snake.D(); break;
    case ' ': return Signal::pause;
    }
    return Signal::none;
}

void GameModel::aiControl()
{
    if(m_snake.head().x > m_eat.x) m_snake.A();
    if(m_snake.head().x < m_eat.x) m_snake.D();
    if(m_snake.head().y > m_eat.y) m_snake.W();
    if(m_snake.head().y < m_eat.y) m_snake.S();
}

void GameModel::reset()
{
    m_snake = Snake();
    m_score = 0u; m_lvl = 1u;
    m_lvlDuration = 0.5f;
    m_eat = stf::Vec2d(stf::Random(time(0)).getNum(2, m_mapSize.x-1),
                       stf::Random(time(0)).getNum(2, m_mapSize.y-1));
}
