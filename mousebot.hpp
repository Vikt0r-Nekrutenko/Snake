#ifndef MOUSEBOT_HPP
#define MOUSEBOT_HPP

#include "bot.hpp"

class MouseBotModel : public BotModel {
public:
    MouseBotModel(const stf::Vec2d& mapSize, const stf::Vec2d& startPos = {10, 10});

    bool onUpdate(const float dt) override;

    void reset() override;

    bool isCollideWithTarget() const override;
};

#endif // MOUSEBOT_HPP
