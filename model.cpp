#include "model.hpp"
#include "random.hpp"
#include <ctime>

GameModel::GameModel(const stf::Vec2d &mapSize)
    : snakeMod(mapSize), m_mapSize(mapSize)
{

}

Signal GameModel::onUpdate(const float dt)
{
    if(snakeMod.aiIsEnable())
        snakeMod.aiControl(m_eat);

    if(snakeMod.isCollideWithEat(m_eat)) {
        snakeMod.collisionWithEatHandler();
        m_eat = stf::Vec2d(stf::Random(time(0)).getNum(2, m_mapSize.x-1),
                           stf::Random(time(0)).getNum(2, m_mapSize.y-1));
    }
    snakeMod.onUpdate(dt);
    return Signal::none;
}

Signal GameModel::keyEvents(const int key)
{
    snakeMod.keyEvents(key);
    if(key == ' ') return Signal::pause;
    return Signal::none;
}

void GameModel::aiControl()
{

}

void GameModel::reset()
{
    snakeMod.reset();
    m_eat = stf::Vec2d(stf::Random(time(0)).getNum(2, m_mapSize.x-1),
                       stf::Random(time(0)).getNum(2, m_mapSize.y-1));
}

bool SnakeModel::aiIsEnable() const
{
    return m_aiIsEnable;
}
