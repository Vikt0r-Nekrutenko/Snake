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
constexpr uint8_t DEF_LIFES = 3;
}
class Food;

class SegmentedEntityModel
{
public:
    SegmentedEntityModel(const stf::Vec2d& mapSize);
    virtual ~SegmentedEntityModel() = default;
    virtual bool onUpdate(const float dt) = 0;
    virtual void reset() = 0;

    virtual void collisionWithTargetHandler() = 0;
    bool isCollideWithTarget() const;

    inline const Food* target() const { return m_target; }
    inline void setTarget(Food* food) { m_target = food; }

    virtual SegmentedEntityModel* collisionWithEntityHandler(SegmentedEntityModel* snakeMod) = 0;

    inline void W() { m_entity->setVel({0,-1}); }
    inline void A() { m_entity->setVel({-1,0}); }
    inline void S() { m_entity->setVel({0,+1}); }
    inline void D() { m_entity->setVel({+1,0}); }

    inline SegmentedEntity* operator()()                  { return m_entity; }
    inline const stf::Vec2d &mapSize()              const { return m_mapSize;   }
    inline const stf::Vec2d &segmet(size_t nOfSeg)  const { return m_entity->body().at(nOfSeg); }

protected:

    SegmentedEntity* m_entity = nullptr;
    stf::Vec2d  m_mapSize       = {0,0};
    Food*       m_target = nullptr;
    float       m_duration      = 0.f;
};

class SnakeModel : public SegmentedEntityModel
{
public:
    SnakeModel(const stf::Vec2d& mapSize, const stf::Vec2d& startPos = {10,10});
    virtual ~SnakeModel() = default;
    bool onUpdate(const float dt) override;
    void reset() override;

    bool isAteHerself() const;
    void collisionWithTargetHandler() override;
//    SegmentedEntityModel* collisionWithSnakeHandler(SegmentedEntityModel* snakeMod) override;
    SegmentedEntityModel* collisionWithEntityHandler(SegmentedEntityModel* snakeMod) override;

    inline uint16_t lvl()       const { return m_lvl;       }
    inline uint16_t score()     const { return m_score;     }
    inline const Snake* snake() const { return dynamic_cast<Snake *>(m_entity);     }

protected:

    float       m_lvlDuration   = snake_model_settings::MAX_DURATION;
    uint16_t    m_score         = 0u;
    uint16_t    m_lvl           = 1u;
};

class Player : public SnakeModel
{
public:
    Player(const stf::Vec2d& mapSize, const stf::Vec2d& startPos = {10,10});

    inline int lifes() const { return m_lifes; }
    void keyEvents(const int key);
    void reset() override;

private:
    int m_lifes = snake_model_settings::DEF_LIFES;
};

class Bot : public SnakeModel
{
public:
    Bot(const stf::Vec2d& mapSize, const stf::Vec2d& startPos = {10,10});
    bool onUpdate(const float dt) override;
};

#endif // SNAKEMODEL_HPP
