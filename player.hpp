#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "snakemodel.hpp"

class Player : public SnakeModel
{
public:
    Player(const stf::Vec2d& mapSize, const stf::Vec2d& startPos = snake_settings::DEF_START_POS);

    inline int lifes() const { return m_lifes; }
    void keyEvents(const int key);
    void reset() override;

private:
    int m_lifes = snake_model_settings::DEF_LIFES;
};

#endif // PLAYER_HPP
