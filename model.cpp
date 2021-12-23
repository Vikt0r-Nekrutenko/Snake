#include "model.hpp"
#include "random.hpp"
#include <ctime>

GameModel::GameModel(const stf::Vec2d &mapSize)
    : m_foodModel(mapSize),
      m_mapSize(mapSize)
{
    for(int i = 1; i < 2; ++i)
        m_snakeModels.push_back(SnakeModel(mapSize, {i*10, 10}));
}

Signal GameModel::onUpdate(const float dt)
{
    for(size_t s = 0; s < m_snakeModels.size() - 1; ++s) {
        for (size_t s1 = s+1; s1 < m_snakeModels.size(); ++s1) {
            SnakeModel* deadSnake = m_snakeModels.at(s).collisionWithSnakeHandler(&m_snakeModels.at(s1));
            if(deadSnake != nullptr)
                kill(deadSnake);
        }
    }
    for(auto &snakeModel : m_snakeModels) {
        if(snakeModel.isAteHerself())
            kill(&snakeModel);

        snakeModel.setTarget(m_foodModel.nearestFood(snakeModel.snake().head()));

        if(snakeModel.aiIsEnable())
            snakeModel.aiControl();

        if(snakeModel.isCollideWithTarget()) {
            snakeModel.collisionWithTargetHandler();
            m_foodModel.remove(snakeModel.target());
            snakeModel.setTarget(nullptr);
        }

        if(!snakeModel.onUpdate(dt)) {
            return Signal::end;
        }
    }
    m_foodModel.onUpdate(dt);

    return Signal::none;
}

Signal GameModel::keyEvents(const int key)
{
    for(auto &snakeModel : m_snakeModels)
        snakeModel.keyEvents(key);
    if(key == ' ') return Signal::pause;
    return Signal::none;
}

void GameModel::reset()
{
    for(auto &snakeModel : m_snakeModels)
        snakeModel.reset();
}

void GameModel::kill(SnakeModel* snakeModel)
{
    m_foodModel.pasteFoodFromDeadSnake(snakeModel->snake().body());
    snakeModel->reset();
}
