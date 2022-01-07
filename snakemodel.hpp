#ifndef SNAKEMODEL_HPP
#define SNAKEMODEL_HPP

#include "huntermodel.hpp"
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

class SnakeModel : public HunterModel
{
public:
    SnakeModel(const stf::Vec2d& mapSize, const stf::Vec2d& startPos = snake_settings::DEF_START_POS);
    ~SnakeModel() = default;

    void reset() override;
    bool isAteHerself() const;
    inline const Snake* snake() const { return dynamic_cast<Snake *>(m_entity);     }
};

#endif // SNAKEMODEL_HPP
