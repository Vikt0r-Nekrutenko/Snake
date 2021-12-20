#include "model.hpp"
#include "random.hpp"
#include <ctime>

GameModel::GameModel(const stf::Vec2d &mapSize)
    : m_mapSize(mapSize)
{
    snakeMods.push_back(SnakeModel(mapSize));
    snakeMods.push_back(SnakeModel(mapSize, {20,10}));
}

Signal GameModel::onUpdate(const float dt)
{
    for(auto &snakeMod : snakeMods) {
        if(snakeMod.aiIsEnable())
            snakeMod.aiControl(m_eat);

        if(snakeMod.isCollideWithEat(m_eat)) {
            snakeMod.collisionWithEatHandler();
            m_eat = stf::Vec2d(stf::Random(time(0)).getNum(2, m_mapSize.x-1),
                               stf::Random(time(0)).getNum(2, m_mapSize.y-1));
        }
        snakeMod.onUpdate(dt);
    }
    return Signal::none;
}

Signal GameModel::keyEvents(const int key)
{
    for(auto &snakeMod : snakeMods)
        snakeMod.keyEvents(key);
    if(key == ' ') return Signal::pause;
    return Signal::none;
}

void GameModel::aiControl()
{

}

void GameModel::reset()
{
    for(auto &snakeMod : snakeMods)
        snakeMod.reset();
    m_eat = stf::Vec2d(stf::Random(time(0)).getNum(2, m_mapSize.x-1),
                       stf::Random(time(0)).getNum(2, m_mapSize.y-1));
}
