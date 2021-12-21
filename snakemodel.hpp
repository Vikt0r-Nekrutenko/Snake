#ifndef SNAKEMODEL_HPP
#define SNAKEMODEL_HPP

#include "random.hpp"
#include "snake.hpp"

class SnakeModel
{
public:
    SnakeModel(const stf::Vec2d& mapSize, const stf::Vec2d& startPos = {10,10});

    void onUpdate(const float dt);
    void keyEvents(const int key);
    void aiControl(const stf::Vec2d& target);
    void reset();
    void collisionWithEatHandler();
    bool isCollideWithEat(const stf::Vec2d& pos) const;

    SnakeModel* collisionWithSnakeHandler(SnakeModel* snakeMod);

    inline void W() { m_snake.setVel({0,-1}); }
    inline void A() { m_snake.setVel({-1,0}); }
    inline void S() { m_snake.setVel({0,+1}); }
    inline void D() { m_snake.setVel({+1,0}); }

    inline uint16_t score()             const { return m_score;     }
    inline uint16_t lvl()               const { return m_lvl;       }
    inline const Snake &snake()         const { return m_snake;     }
    inline const stf::Vec2d &mapSize()  const { return m_mapSize;   }
    inline bool aiIsEnable()            const { return m_aiIsEnable;}

    inline void killSnake() { m_snake.setSnakeState(true); }
    inline void rebornSnake() { m_snake.setSnakeState(false); }
private:
    Snake m_snake;
    stf::Vec2d m_mapSize = {0,0};
    float m_time = 0.f;
    float m_lvlDuration = 0.05f;
    bool m_aiIsEnable = true;
    uint16_t m_score = 0u;
    uint16_t m_lvl   = 1u;
};


#endif // SNAKEMODEL_HPP
