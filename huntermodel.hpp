#ifndef HUNTERMODEL_HPP
#define HUNTERMODEL_HPP

#include "segmentedentitymodel.hpp"

namespace hunter_model_settings {
constexpr float MAX_DURATION  = 0.3f;
constexpr float MIN_DURATION  = 0.05f;
constexpr float DURATION_STEP = 0.025f;
constexpr int MAX_LENTH = 15;
constexpr int MAX_LEVEL = 20;
constexpr int LVLUP_STEP= 15;
constexpr uint8_t DEF_LIFES = 3;
}

class HunterModel : public SegmentedEntityModel
{
public:
    HunterModel(const stf::Vec2d& mapSize);
    virtual ~HunterModel() = default;
    bool onUpdate(const float dt) override;
    void reset() override;

    void collisionWithTargetHandler() override;
    SegmentedEntityModel* collisionWithEntityHandler(SegmentedEntityModel *entity) override;

    inline uint16_t lvl()       const { return m_lvl;       }
    inline uint16_t score()     const { return m_score;     }
    inline SegmentedEntity* hunter()     const { return m_entity;    }

protected:

    float       m_lvlDuration   = hunter_model_settings::MAX_DURATION;
    uint16_t    m_score         = 0u;
    uint16_t    m_lvl           = 1u;
};

#endif // HUNTERMODEL_HPP
