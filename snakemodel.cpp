#include "snakemodel.hpp"
#include <ctime>
#include "food.hpp"

SnakeModel::SnakeModel(const stf::Vec2d &mapSize, const stf::Vec2d &startPos)
    : m_snake(startPos),
      m_mapSize(mapSize)
{

}

void SnakeModel::onUpdate(const float dt)
{
    if(m_snake.isDead()) return;

    if(m_duration > m_lvlDuration)
    {
        m_snake.update();

        //            if(m_snake.isAteHerself())
        //                m_snake.killSnake();

        m_snake.wrapping(2, 1, m_mapSize.x-1, m_mapSize.y-1);
        m_duration = 0.f;
    }
    m_duration += dt;
}

void SnakeModel::keyEvents(const int key)
{
    switch (key) {
    case 'w': W(); break;
    case 'a': A(); break;
    case 's': S(); break;
    case 'd': D(); break;
    }
}

void SnakeModel::aiControl()
{
    if(targ == nullptr) return;
    if(m_snake.head().x > targ->pos().x) A();
    if(m_snake.head().x < targ->pos().x) D();
    if(m_snake.head().y > targ->pos().y) W();
    if(m_snake.head().y < targ->pos().y) S();
}

void SnakeModel::reset()
{
    m_snake = Snake({stf::Random(time(0)).getNum(2, m_mapSize.x-2),
                     stf::Random(time(0)).getNum(2, m_mapSize.y-2)});
    m_lvlDuration = snake_model_settings::MAX_DURATION;
    m_score = 0u;
    m_lvl   = 1u;
}

bool SnakeModel::isCollideWithEat() const
{
    if(targ == nullptr) return false;

    if(m_snake.head().diff(targ->pos()) < 1.f)
        return true;
    return false;
}

bool SnakeModel::isAteHerself() const
{
    return m_snake.isAteHerself();
}

void SnakeModel::collisionWithEatHandler(uint8_t nutritionalValue)
{
    using namespace snake_model_settings;
    if(m_snake.length() < MAX_LENTH) m_snake.feed();
    m_score += nutritionalValue;
    if(m_score != 1 && m_lvl < MAX_LEVEL && m_score % LVLUP_STEP == 0) {
        if(m_lvlDuration > MIN_DURATION) m_lvlDuration -= DURATION_STEP;
        ++m_lvl;
    }
}

SnakeModel *SnakeModel::collisionWithSnakeHandler(SnakeModel *snakeMod)
{
    if(m_snake.isDead() || snakeMod->snake().isDead()) return nullptr;

    for(size_t s1 = 0; s1 < m_snake.length(); ++s1) {
        for (size_t s2 = 0; s2 < snakeMod->m_snake.length(); ++s2) {
            if(m_snake.isSegmetOverlapped(s1, snakeMod->segmet(s2))) {
                if(m_score > snakeMod->score()) {
                    return snakeMod;
                } else {
                    return this;
                }
            }
        }
    }
    return nullptr;
}
