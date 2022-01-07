#include "snakemodel.hpp"
#include <ctime>
#include "random.hpp"

SnakeModel::SnakeModel(const stf::Vec2d &mapSize, const stf::Vec2d &startPos)
    : HunterModel(mapSize)
{
    m_entity = new Snake(startPos);
}

void SnakeModel::reset()
{
    m_entity = new Snake({stf::Random(time(0)).getNum(2, m_mapSize.x-2),
                          stf::Random(time(0)).getNum(2, m_mapSize.y-2)});
    HunterModel::reset();
}

bool SnakeModel::isAteHerself() const
{
    return snake()->isAteHerself();
}
