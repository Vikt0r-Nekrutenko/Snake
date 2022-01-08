#include "player.hpp"

Player::Player(const stf::Vec2d &mapSize, const stf::Vec2d &startPos)
    : SnakeBotModel(mapSize, startPos)
{}

void Player::keyEvents(const int key)
{
    switch (key) {
    case 'w': W(); break;
    case 'a': A(); break;
    case 's': S(); break;
    case 'd': D(); break;
    }
}

void Player::reset()
{
    --m_lifes;
    if(m_lifes > 0) {
        SnakeBotModel::reset();
    }
}

bool Player::onUpdate(const float dt)
{
    if (dynamic_cast<Snake*>(m_entity)->isAteHerself())
        return false;
    return HunterModel::onUpdate(dt);
}
