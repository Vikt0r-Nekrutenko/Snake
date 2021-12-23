#include "model.hpp"
#include "random.hpp"
#include <ctime>

GameModel::GameModel(const stf::Vec2d &mapSize)
    : m_foodModel(mapSize),
      m_mapSize(mapSize)
{
    for(int i = 1; i < 3; ++i)
        snakeMods.push_back(SnakeModel(mapSize, {i*10, 10}));
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
        if(snakeMod.isAteHerself())
            kill(&snakeMod);

        if(snakeMod.aiIsEnable()) {
            snakeMod.targ = m_foodModel.nearestFood(snakeMod.snake().head());
            snakeMod.aiControl();
        }

        if(snakeMod.isCollideWithTarget()) {
            snakeMod.collisionWithTargetHandler();
            m_foodModel.remove(snakeMod.targ);
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

void GameModel::reset()
{
    for(auto &snakeMod : snakeMods)
        snakeMod.reset();
}

void GameModel::kill(SnakeModel* snakeMod)
{
    snakeMod->killSnake();
    m_foodModel.pasteFoodFromDeadSnake(snakeMod->snake().body());
    snakeMod->reset();
}
