#include "model.hpp"
#include "player.hpp"
#include "bot.hpp"
#include <ctime>

GameModel::GameModel(const stf::Vec2d &mapSize)
    : m_foodModel(mapSize),
      m_mapSize(mapSize)
{
    reset();
}

GameModel::~GameModel()
{
    for(size_t i = 0; i < m_snakeModels.size(); ++i) {
        delete m_snakeModels[i];
    }
    m_snakeModels.clear();

    for(size_t i = 0; i < m_hunterModels.size(); ++i) {
        delete m_hunterModels[i];
    }
    m_hunterModels.clear();
}

Signal GameModel::onUpdate(const float dt)
{
    for(size_t s = 0; s < m_snakeModels.size() - 1; ++s) {
        for (size_t s1 = s+1; s1 < m_snakeModels.size(); ++s1) {
            SnakeModel* deadSnake = (SnakeModel *)m_snakeModels.at(s)->collisionWithEntityHandler(m_snakeModels.at(s1));
            if(deadSnake != nullptr) {
                killSnakeHandler(deadSnake);
            }
        }
    }
    for(auto snakeModel : m_snakeModels) {
        snakeModel->setTarget(m_foodModel.nearestFood(snakeModel->snake()->head()));

        if(snakeModel->isAteHerself())
            killSnakeHandler(snakeModel);

        if(snakeModel->isCollideWithTarget()) {
            snakeModel->collisionWithTargetHandler();
            m_foodModel.remove(snakeModel->target());
            snakeModel->setTarget(nullptr);
        }
        snakeModel->onUpdate(dt);
    }
    m_foodModel.onUpdate();


    for(size_t s = 0; s < m_hunterModels.size() - 1; ++s) {
        for (size_t s1 = s+1; s1 < m_hunterModels.size(); ++s1) {
            HunterModel* deadSnake = (HunterModel *)m_hunterModels.at(s)->collisionWithEntityHandler(m_hunterModels.at(s1));
            if(deadSnake != nullptr) {
                killHunterHandler(deadSnake);
            }
        }
    }
    for(auto hunterModel : m_hunterModels) {
        hunterModel->setTarget(m_foodModel.nearestFood(hunterModel->hunter()->head()));

//        if(hunterModel->isAteHerself())
//            killSnakeHandler(hunterModel);

        if(hunterModel->isCollideWithTarget()) {
            hunterModel->collisionWithTargetHandler();
            m_foodModel.remove(hunterModel->target());
            hunterModel->setTarget(nullptr);
        }
        hunterModel->onUpdate(dt);
    }
    m_foodModel.onUpdate();


    return dynamic_cast<Player*>(m_snakeModels.at(0))->lifes() != 0 ? Signal::none : Signal::end;
}

Signal GameModel::keyEvents(const int key)
{
//    static_cast<Player *>(m_snakeModels.at(0))->keyEvents(key);

//    if(key == ' ') {
//        return Signal::pause;
//    }

    return Signal::none;
}

void GameModel::reset()
{
    for(size_t i = 0; i < m_snakeModels.size(); ++i) {
        delete m_snakeModels[i];
    }

    m_snakeModels.clear();

    m_snakeModels.push_back(new Player(m_mapSize, snake_settings::DEF_START_POS));
    for(int i = 2; i < 2; ++i) {
//        m_snakeModels.push_back(new Bot(m_mapSize, {i*snake_settings::DEF_START_POS.x, snake_settings::DEF_START_POS.y}));
    }

    m_foodModel.reset();


    for(size_t i = 0; i < m_hunterModels.size(); ++i) {
        delete m_hunterModels[i];
    }

    m_hunterModels.clear();

    m_hunterModels.push_back(new Player(m_mapSize, snake_settings::DEF_START_POS));
    for(int i = 2; i < 5; ++i) {
        m_hunterModels.push_back(new SnakeBot(m_mapSize, {i*snake_settings::DEF_START_POS.x, snake_settings::DEF_START_POS.y}));
    }

    m_foodModel.reset();
}

void GameModel::killSnakeHandler(SnakeModel* snakeModel)
{
    m_foodModel.pasteFoodFromDeadSnake(snakeModel->snake()->body());
    snakeModel->reset();
}

void GameModel::killHunterHandler(HunterModel *hunterModel)
{
    m_foodModel.pasteFoodFromDeadSnake(hunterModel->hunter()->body());
    hunterModel->reset();
}
