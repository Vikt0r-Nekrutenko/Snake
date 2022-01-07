#ifndef SNAKEMODEL_HPP
#define SNAKEMODEL_HPP

#include "huntermodel.hpp"
#include "snake.hpp"


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
