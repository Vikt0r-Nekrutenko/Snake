#ifndef SNAKEBOT_HPP
#define SNAKEBOT_HPP

#include "bot.hpp"

class SnakeBotModel : public BotModel {
public:
    SnakeBotModel(const stf::Vec2d& mapSize, const stf::Vec2d& startPos = {10, 10});
    ~SnakeBotModel() = default;

    void reset() override;
    bool isAteHerself() const;
};

#endif // SNAKEBOT_HPP
