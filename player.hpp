#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "snakebot.hpp"
#include "snake.hpp"

class Player : public SnakeBotModel
{
public:
    Player(const stf::Vec2d& mapSize, const stf::Vec2d& startPos = snake_settings::DEF_START_POS);

    inline int lifes() const { return m_lifes; }
    void keyEvents(const int key);
    void reset() override;

    bool onUpdate(const float dt) override;

private:
    int m_lifes = snake_model_settings::DEF_LIFES;
};

#endif // PLAYER_HPP
