#include "model.hpp"
#include "random.hpp"
#include <ctime>

GameModel::GameModel(const stf::Vec2d &mapSize)
    : m_mapSize(mapSize)
{
    snakeMods.push_back(SnakeModel(mapSize));
    snakeMods.push_back(SnakeModel(mapSize, {20,10}));
    snakeMods.push_back(SnakeModel(mapSize, {30,10}));

    int i = 0; while(i++ < 15) m_eats.push_back({stf::Random(time(0)).getNum(2, m_mapSize.x-2),
                                                 stf::Random(time(0)).getNum(2, m_mapSize.y-2)});
}

Signal GameModel::onUpdate(const float dt)
{
    for(auto &snakeMod : snakeMods) {
        if(snakeMod.aiIsEnable()) {
            stf::Vec2d *target = &m_eats.front();
            for(auto &eat : m_eats) {
                if(snakeMod.snake().head().diff(eat) < snakeMod.snake().head().diff(*target))
                    target = &eat;
            }
            snakeMod.aiControl(*target);
        }
        for(auto &eat : m_eats)
            if(snakeMod.isCollideWithEat(eat)) {
                snakeMod.collisionWithEatHandler();
                eat = stf::Vec2d(stf::Random(time(0)).getNum(2, m_mapSize.x-2),
                                 stf::Random(time(0)).getNum(2, m_mapSize.y-2));
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
//    m_eat = stf::Vec2d(stf::Random(time(0)).getNum(2, m_mapSize.x-1),
//                       stf::Random(time(0)).getNum(2, m_mapSize.y-1));
}
