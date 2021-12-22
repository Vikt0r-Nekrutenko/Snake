#ifndef SNAKEMODEL_HPP
#define SNAKEMODEL_HPP

#include "random.hpp"
#include "snake.hpp"

namespace snake_model_settings {
constexpr float MAX_DURATION  = 0.3f;
constexpr float MIN_DURATION  = 0.05f;
constexpr float DURATION_STEP = 0.025f;
constexpr int MAX_LENTH = 15;
constexpr int MAX_LEVEL = 20;
constexpr int LVLUP_STEP= 15;
}

class SnakeModel
{
public:
    SnakeModel(const stf::Vec2d& mapSize, const stf::Vec2d& startPos = {10,10});

    void onUpdate(const float dt);
    void keyEvents(const int key);
    void aiControl(const stf::Vec2d& target);
    void reset();
    void collisionWithEatHandler(uint8_t nutritionalValue);
    bool isCollideWithEat(const stf::Vec2d& pos) const;
    bool isAteHerself()                          const;

    SnakeModel* collisionWithSnakeHandler(SnakeModel* snakeMod);

    inline void W() { m_snake.setVel({0,-1}); }
    inline void A() { m_snake.setVel({-1,0}); }
    inline void S() { m_snake.setVel({0,+1}); }
    inline void D() { m_snake.setVel({+1,0}); }

    inline uint16_t score()             const { return m_score;     }
    inline uint16_t lvl()               const { return m_lvl;       }
    inline bool aiIsEnable()            const { return m_aiIsEnable;}
    inline const Snake &snake()         const { return m_snake;     }
    inline const stf::Vec2d &mapSize()              const { return m_mapSize;   }
    inline const stf::Vec2d &segmet(size_t nOfSeg)  const { return m_snake.body().at(nOfSeg); }

    inline void killSnake() { m_snake.setSnakeState(true); }
    inline void rebornSnake() { m_snake.setSnakeState(false); }
stf::Vec2d targ;
private:

    Snake       m_snake;
    stf::Vec2d  m_mapSize       = {0,0};
    float       m_duration      = 0.f;
    float       m_lvlDuration   = snake_model_settings::MAX_DURATION;
    bool        m_aiIsEnable    = true;
    uint16_t    m_score         = 0u;
    uint16_t    m_lvl           = 1u;
};


#endif // SNAKEMODEL_HPP
