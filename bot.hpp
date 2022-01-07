#ifndef BOT_HPP
#define BOT_HPP

#include "snakemodel.hpp"

class Bot : public SnakeModel
{
public:
    Bot(const stf::Vec2d& mapSize, const stf::Vec2d& startPos = {10,10});
    bool onUpdate(const float dt) override;
};

#endif // BOT_HPP
