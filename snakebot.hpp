#ifndef SNAKEBOT_HPP
#define SNAKEBOT_HPP

#include "bot.hpp"

namespace snake_model_settings {
constexpr float MAX_DURATION  = 0.3f;
constexpr float MIN_DURATION  = 0.05f;
constexpr float DURATION_STEP = 0.025f;
constexpr int MAX_LENTH = 15;
constexpr int MAX_LEVEL = 20;
constexpr int LVLUP_STEP= 15;
constexpr uint8_t DEF_LIFES = 3;
}

class SnakeBotModel : public BotModel {
public:
    SnakeBotModel(const stf::Vec2d& mapSize, const stf::Vec2d& startPos = {10, 10});
    ~SnakeBotModel() = default;

    void reset() override;
    bool onUpdate(const float dt) override;
};

#endif // SNAKEBOT_HPP
