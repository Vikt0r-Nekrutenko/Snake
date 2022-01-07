#include "snakebot.hpp"
#include "snake.hpp"
#include "random.hpp"
#include <ctime>

SnakeBotModel::SnakeBotModel(const stf::Vec2d &mapSize, const stf::Vec2d &startPos)
    : BotModel(mapSize, startPos)
{
    m_entity = new Snake(startPos);
}

void SnakeBotModel::reset()
{
    m_entity = new Snake({stf::Random(time(0)).getNum(2, m_mapSize.x-2),
                          stf::Random(time(0)).getNum(2, m_mapSize.y-2)});
    HunterModel::reset();
}

bool SnakeBotModel::isAteHerself() const
{
    return dynamic_cast<Snake*>(m_entity)->isAteHerself();
}
