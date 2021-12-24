#include "model.hpp"
#include "random.hpp"
#include <ctime>

GameModel::GameModel(const stf::Vec2d &mapSize)
    : m_foodModel(mapSize),
      m_mapSize(mapSize)
{
    m_snakeModels.push_back(new Player(mapSize, {10, 10}));
    for(int i = 2; i < 5; ++i)
        m_snakeModels.push_back(new Bot(mapSize, {i*10, 10}));
}

GameModel::~GameModel()
{
    for(size_t i = 0; i < m_snakeModels.size(); ++i) {
        delete m_snakeModels[i];
    }
    m_snakeModels.clear();
}

Signal GameModel::onUpdate(const float dt)
{
    for(size_t s = 0; s < m_snakeModels.size() - 1; ++s) {
        for (size_t s1 = s+1; s1 < m_snakeModels.size(); ++s1) {
            SnakeModel* deadSnake = m_snakeModels.at(s)->collisionWithSnakeHandler(m_snakeModels.at(s1));
            if(deadSnake != nullptr)
                kill(deadSnake);
        }
    }
    for(auto snakeModel : m_snakeModels) {
        snakeModel->setTarget(m_foodModel.nearestFood(snakeModel->snake().head()));

        if(snakeModel->isAteHerself())
            kill(snakeModel);

        if(snakeModel->isCollideWithTarget()) {
            snakeModel->collisionWithTargetHandler();
            m_foodModel.remove(snakeModel->target());
            snakeModel->setTarget(nullptr);
        }
        snakeModel->onUpdate(dt);
    }
    m_foodModel.onUpdate(dt);

    return dynamic_cast<Player*>(m_snakeModels.at(0))->lifes() != 0 ? Signal::none : Signal::end;
}

Signal GameModel::keyEvents(const int key)
{
    static_cast<Player *>(m_snakeModels.at(0))->keyEvents(key);
    if(key == ' ') return Signal::pause;
    return Signal::none;
}

void GameModel::reset()
{
    for(size_t i = 0; i < m_snakeModels.size(); ++i) {
        delete m_snakeModels[i];
    }
    m_snakeModels.clear();

    m_snakeModels.push_back(new Player(m_mapSize, {10, 10}));
    for(int i = 2; i < 5; ++i)
        m_snakeModels.push_back(new Bot(m_mapSize, {i*10, 10}));
    m_foodModel.reset();
}

void GameModel::kill(SnakeModel* snakeModel)
{
    m_foodModel.pasteFoodFromDeadSnake(snakeModel->snake().body());
    snakeModel->reset();
}
