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
    for(size_t s = 0; s < snakeModels().size() - 1; ++s) {
        for (size_t s1 = s+1; s1 < snakeModels().size(); ++s1) {
            if(!snakeMods.at(s).snake().isDead() && !snakeMods.at(s1).snake().isDead()) {
                for(auto &sn : snakeMods.at(s1).snake().body()) {
                    if(snakeMods.at(s).snake().head().diff(sn) < 2.f) {
                        if(snakeMods.at(s).score() > snakeMods.at(s1).score()) {
                            kill(s);
                            break;
                        } else {
                            kill(s1);
                            break;
                        }
                    }
                }
            }
        }
    }
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

void GameModel::kill(size_t s)
{
    snakeMods.at(s).killSnake();
    for(auto &segn : snakeMods.at(s).snake().body()) {
        m_eats.push_back(segn);
    }
    snakeMods.at(s).reset();
}
