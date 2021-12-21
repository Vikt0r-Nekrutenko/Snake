#include "model.hpp"
#include "random.hpp"
#include <ctime>

GameModel::GameModel(const stf::Vec2d &mapSize)
    : m_mapSize(mapSize)
{
    snakeMods.push_back(SnakeModel(mapSize));
    snakeMods.push_back(SnakeModel(mapSize, {20,10}));
    snakeMods.push_back(SnakeModel(mapSize, {30,10}));

    m_eats1.resize(mapSize.x * mapSize.y, {-1,-1});
    int i = 0; while(i++ < 5) m_eats.push_back({stf::Random(time(0)).getNum(2, m_mapSize.x-2),
                                                 stf::Random(time(0)).getNum(2, m_mapSize.y-2)});
}

Signal GameModel::onUpdate(const float dt)
{
    for(size_t s = 0; s < snakeModels().size() - 1; ++s) {
        for (size_t s1 = s+1; s1 < snakeModels().size(); ++s1) {
            SnakeModel* deadSnake = snakeMods.at(s).collisionWithSnakeHandler(&snakeMods.at(s1));
            if(deadSnake != nullptr)
                kill(deadSnake);
        }
    }
    for(auto &snakeMod : snakeMods) {
        if(snakeMod.aiIsEnable()) {
            stf::Vec2d *target = &m_eats.front();
            for(auto &eat : m_eats) {
                if(snakeMod.snake().head().diff(eat) < snakeMod.snake().head().diff(*target))
                    target = &eat;
            }

            for(auto &eat : m_eats1) {
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
        for(auto &eat : m_eats1)
            if(snakeMod.isCollideWithEat(eat)) {
                snakeMod.collisionWithEatHandler();
                eat = stf::Vec2d(-1,-1);
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

void GameModel::kill(SnakeModel* snakeMod)
{
    snakeMod->killSnake();
    pasteEat(*snakeMod);
    snakeMod->reset();
}

void GameModel::pasteEat(const SnakeModel &snakeMod)
{
    for(auto &segment : snakeMod.snake().body()) {
        for(stf::Vec2d& emptyCell : m_eats1) {
            if(emptyCell == stf::Vec2d(-1,-1)) {
                emptyCell = segment;
                break;
            }
        }
    }
}
