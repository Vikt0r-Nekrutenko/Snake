#include "snakemodel.hpp"
#include <ctime>
#include "food.hpp"

SnakeModel::SnakeModel(const stf::Vec2d &mapSize, const stf::Vec2d &startPos, bool aiIsEnabled)
    : m_snake(startPos),
      m_mapSize(mapSize),
      m_aiIsEnabled(aiIsEnabled)
{

}

bool SnakeModel::onUpdate(const float dt)
{
    if(m_snake.isDead() || lifes() == 0) return false;

    if(m_duration > m_lvlDuration)
    {
        m_snake.update();

        m_snake.wrapping(2, 1, m_mapSize.x-1, m_mapSize.y-1);
        m_duration = 0.f;
    }
    m_duration += dt;
    return true;
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
    if(m_target == nullptr) return;
    if(m_snake.head().x > m_target->pos().x) A();
    if(m_snake.head().x < m_target->pos().x) D();
    if(m_snake.head().y > m_target->pos().y) W();
    if(m_snake.head().y < m_target->pos().y) S();
}

void SnakeModel::reset()
{
    m_snake = Snake({stf::Random(time(0)).getNum(2, m_mapSize.x-2),
                     stf::Random(time(0)).getNum(2, m_mapSize.y-2)});
    m_lvlDuration = snake_model_settings::MAX_DURATION;
    m_score = 0u;
    m_lvl   = 1u;
    --m_lifes;
}

bool SnakeModel::isCollideWithTarget() const
{
    if(m_target == nullptr) return false;

    if(m_snake.head().diff(m_target->pos()) < 1.f)
        return true;
    return false;
}

bool SnakeModel::isAteHerself() const
{
    return m_snake.isAteHerself();
}

void SnakeModel::collisionWithTargetHandler()
{
    using namespace snake_model_settings;
    m_snake.feed();
    m_score += m_target->nutritionalValue();
    if(m_score != 1 && m_lvl < MAX_LEVEL && m_snake.length() % LVLUP_STEP == 0) {
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
