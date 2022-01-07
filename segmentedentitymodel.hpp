#ifndef SEGMENTEDENTITYMODEL_HPP
#define SEGMENTEDENTITYMODEL_HPP

#include "segmentedentity.hpp"
#include "food.hpp"

class SegmentedEntityModel
{
public:
    SegmentedEntityModel(const stf::Vec2d& mapSize);
    virtual ~SegmentedEntityModel() = default;
    virtual bool onUpdate(const float dt) = 0;
    virtual void reset() = 0;

    virtual void collisionWithTargetHandler() = 0;
    virtual bool isCollideWithTarget() const;

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
    Food*       m_target        = nullptr;
    float       m_duration      = 0.f;
};

#endif // SEGMENTEDENTITYMODEL_HPP
