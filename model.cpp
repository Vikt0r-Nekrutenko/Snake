#include "model.hpp"
#include "player.hpp"
#include "mousebot.hpp"
#include "snakebot.hpp"
#include "random.hpp"
#include <ctime>

GameModel::GameModel(const stf::Vec2d &mapSize, uint8_t snakes, uint8_t mouses)
    : m_foodModel(mapSize),
      m_mapSize(mapSize)
{
    reset(snakes, mouses);
}

GameModel::~GameModel()
{
    for(size_t i = 0; i < m_hunterModels.size(); ++i) {
        delete m_hunterModels[i];
    }
    m_hunterModels.clear();
}

stf::smv::ModelBaseState GameModel::update(const float dt)
{
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
        if(hunterModel->isCollideWithTarget()) {
            hunterModel->collisionWithTargetHandler();
            m_foodModel.remove(hunterModel->target());
            hunterModel->setTarget(nullptr);
        }
        if(!hunterModel->onUpdate(dt))
            killHunterHandler(hunterModel);
    }
    m_foodModel.onUpdate();

    return dynamic_cast<Player*>(m_hunterModels.at(0))->lifes() != 0 ?
                stf::smv::ModelBaseState::none :
                stf::smv::ModelBaseState::end;
}

stf::smv::ModelBaseState GameModel::keyEventsHandler(const int key)
{
    static_cast<Player *>(m_hunterModels.at(0))->keyEvents(key);
    return stf::smv::BaseModel::keyEventsHandler(key);
}

void GameModel::reset(uint8_t snakes, uint8_t mouses)
{
    for(size_t i = 0; i < m_hunterModels.size(); ++i) {
        delete m_hunterModels[i];
    }

    m_hunterModels.clear();

    m_hunterModels.push_back(new Player(m_mapSize, snake_settings::DEF_START_POS));

    for(int i = 0; i < mouses; ++i) {
        m_hunterModels.push_back(new MouseBotModel(m_mapSize, {stf::Random(time(0)).getNum(2, m_mapSize.x - 2),
                                                                stf::Random(time(0)).getNum(2, m_mapSize.y - 2)}));
    }

    for(int i = 0; i < snakes; ++i) {
        m_hunterModels.push_back(new SnakeBotModel(m_mapSize, {stf::Random(time(0)).getNum(2, m_mapSize.x - 2),
                                                               stf::Random(time(0)).getNum(2, m_mapSize.y - 2)}));
    }

    m_foodModel.reset();
}

void GameModel::killHunterHandler(HunterModel *hunterModel)
{
    m_foodModel.pasteFoodFromDeadSnake(hunterModel->hunter()->body());
    hunterModel->reset();
}
