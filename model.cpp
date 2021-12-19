#include "model.hpp"

Model::Model(const stf::Vec2d &mapSize)
    : m_mapSize(mapSize)
{

}

Signal Model::onUpdate(const float dt)
{

    return Signal::none;
}
